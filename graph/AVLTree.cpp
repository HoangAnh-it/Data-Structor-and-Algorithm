#include <iostream>
#include <algorithm>

using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
    int height;
    Node(int data)
    {
        this->data = data;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

int getHeight(Node *node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}

int getBalance(Node *node)
{
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

class AVLTree
{
public:
    Node *insert(Node *node, int data)
    {
        if (node == nullptr)
            return new Node(data);
        else if (node->data > data)
            node->left = insert(node->left, data);
        else if (node->data < data)
            node->right = insert(node->right, data);
        else
            return node;

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

        int balance = getBalance(node);

        if (balance > 1 && data < node->left->data)
        {
            return rightRotate(node);
        }

        if (balance > 1 && data > node->left->data)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && data > node->right->data)
        {
            return leftRotate(node);
        }

        if (balance < -1 && data < node->right->data)
        {
            node->right = rightRotate(node->left);
            return leftRotate(node);
        }
        return node;
    }
};

void preOrder(Node *root)
{
    if (root != nullptr)
    {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main()
{
    AVLTree avl;
    Node *root = nullptr;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int data;
        cin >> data;
        root = avl.insert(root, data);
    }

    preOrder(root);
    return 0;
}