#include <iostream>
#include <set>
#include <float.h>
#include <cmath>
#include <functional>
#include <stack>

using namespace std;

#define ROW 9
#define COL 10

struct Point
{
    int x, y;
    int parentX, parentY;
    double g, h, f;
    bool visited;
    Point()
    {
        parentX = -1;
        parentY = -1;
        g = h = f = FLT_MAX;
        visited = false;
    }
};

bool isValid(int x, int y)
{
    return 0 <= x && x < COL && 0 <= y && y < ROW;
}

bool isBlock(int myMap[ROW][COL], int x, int y)
{
    return myMap[y][x] == 0;
}

bool isDestination(int x, int y, Point dest)
{
    return x == dest.x && y == dest.y;
}

double distance(int x, int y, int newX, int newY)
{
    return sqrt(pow(x - newX, 2) + pow(y - newY, 2));
}

void traceBack(Point points[ROW][COL], Point dest)
{
    stack<pair<int, int>> s;
    s.push(make_pair(dest.x, dest.y));

    int x = dest.parentX;
    int y = dest.parentY;

    while (x != -1 && y != -1)
    {
        int tempX = x;
        int tempY = y;
        s.push(make_pair(x, y));
        x = points[tempY][tempX].parentX;
        y = points[tempY][tempX].parentY;
    }

    cout << "STACK SIZE: " << s.size() << endl;

    while (s.empty() == false)
    {
        cout << "{" << s.top().first << "," << s.top().second << "}, ";
        s.pop();
    }

    cout << endl;
}

bool analyze(int oldX, int oldY, int newX, int newY, int myMap[ROW][COL], Point points[ROW][COL], set<Point, function<bool(Point, Point)>> &openList, Point dest)
{
    if (!isValid(newX, newY))
        return false;
    if (isBlock(myMap, newX, newY))
        return false;

    if (points[newY][newX].visited == true)
        return false;

    double newH, newG, newF;
    newG = points[oldY][oldX].g + distance(oldX, oldY, newX, newY);
    newH = distance(newX, newY, dest.x, dest.y);
    newF = newG + newH;

    if (isDestination(newX, newY, dest))
    {
        cout << "trace back: => ";
        points[newY][newX].parentX = oldX;
        points[newY][newX].parentY = oldY;
        traceBack(points, points[newY][newX]);
        return true;
    }

    if (points[newY][newX].f == FLT_MAX || newF < points[newY][newX].f)
    {
        points[newY][newX].g = newG;
        points[newY][newX].h = newH;
        points[newY][newX].f = newF;
        points[newY][newX].parentX = oldX;
        points[newY][newX].parentY = oldY;

        openList.insert(points[newY][newX]);
    }

    return false;
}

void aStarSearch(int myMap[ROW][COL], Point src, Point dest)
{
    if (!isValid(src.x, src.y) || !isValid(dest.x, dest.y))
        return;

    if (isBlock(myMap, src.x, src.y) || isBlock(myMap, dest.x, dest.y))
        return;

    if (isDestination(src.x, src.y, dest))
    {
        cout << "Already in destination " << endl;
        return;
    }

    Point points[ROW][COL];
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            points[i][j].x = j;
            points[i][j].y = i;
        }
    }

    points[src.y][src.x].f = 0;
    points[src.y][src.x].g = 0;
    points[src.y][src.x].h = 0;

    set<Point, function<bool(Point, Point)>> openList([](Point a, Point b)
                                                      { return a.f <= b.f; });

    openList.insert(points[src.y][src.x]);

    while (openList.empty() == false)
    {

        Point cur = *openList.begin();
        openList.erase(openList.begin());

        int oldX = cur.x;
        int oldY = cur.y;
        int oldG = cur.g;
        int oldH = cur.h;
        int oldF = cur.f;
        points[oldY][oldX].visited = true;

        int newX;
        int newY;

        //N
        newX = oldX;
        newY = oldY - 1;
        if (analyze(oldX, oldY, newX, newY, myMap, points, openList, dest))
            return;

        //S
        newX = oldX;
        newY = oldY + 1;
        if (analyze(oldX, oldY, newX, newY, myMap, points, openList, dest))
            return;

        //E
        newX = oldX + 1;
        newY = oldY;
        if (analyze(oldX, oldY, newX, newY, myMap, points, openList, dest))
            return;

        //W
        newX = oldX - 1;
        newY = oldY;
        if (analyze(oldX, oldY, newX, newY, myMap, points, openList, dest))
            return;

        //N-E
        newX = oldX + 1;
        newY = oldY - 1;
        if (analyze(oldX, oldY, newX, newY, myMap, points, openList, dest))
            return;

        //N-W
        newX = oldX - 1;
        newY = oldY - 1;
        if (analyze(oldX, oldY, newX, newY, myMap, points, openList, dest))
            return;

        //S-E
        newX = oldX + 1;
        newY = oldY + 1;
        if (analyze(oldX, oldY, newX, newY, myMap, points, openList, dest))
            return;

        //S-W
        newX = oldX - 1;
        newY = oldY + 1;
        if (analyze(oldX, oldY, newX, newY, myMap, points, openList, dest))
            return;
    }
}

int main()
{
    int grid[ROW][COL] = {{1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
                          {1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
                          {1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
                          {0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
                          {1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
                          {1, 0, 1, 1, 1, 1, 0, 1, 0, 0},
                          {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                          {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
                          {1, 1, 1, 0, 0, 0, 1, 0, 0, 1}};

    Point src;
    src.x = 8;
    src.y = 0;

    Point dest;
    dest.x = 0;
    dest.y = 0;

    aStarSearch(grid, src, dest);
    return 0;
}