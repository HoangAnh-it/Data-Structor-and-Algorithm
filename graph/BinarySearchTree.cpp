#include <iostream>
#include <queue>

using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
    Node() {}
    Node(int data)
    {
        this->data = data;
        left = nullptr;
        right = nullptr;
    }
};

Node *minNode(Node *parent, Node *child)
{
    if (child == nullptr)
        return nullptr;
    while (child && child->left != nullptr)
    {
        parent = child;
        child = child->left;
    }
    parent->left = nullptr;
    return child;
}

class BinarySearchTree
{
public:
    void insert(Node *&root, int data)
    {
        if (root == nullptr)
            root = new Node(data);
        else
        {
            if (root->data > data)
                insert(root->left, data);
            else
                insert(root->right, data);
        }
    }

    void deleteNode(Node *&root, int data)
    {
        if (root == nullptr)
            return;
        else if (root->data > data)
            deleteNode(root->left, data);
        else if (root->data < data)
            deleteNode(root->right, data);
        else
        {
            if (root->left == nullptr && root->right == nullptr)
                root = nullptr;
            else if (root->left == nullptr)
            {
                Node *temp = root;
                root = root->right;
                delete temp;
                temp = nullptr;
            }
            else if (root->right == nullptr)
            {
                Node *temp = root;
                root = root->left;
                delete temp;
                temp = nullptr;
            }
            else
            {
                Node *min = minNode(root, root->right);
                root->data = min->data;
                delete min;
                min = nullptr;
            }
        }
    }
};
void printLevelOrder(Node *root)
{
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();
        cout << temp->data << " ";
        if (temp->left != nullptr)
            q.push(temp->left);
        if (temp->right != nullptr)
            q.push(temp->right);
    }
    cout << endl;
}

int main()
{
    BinarySearchTree bst;
    Node *root = nullptr;
    bst.insert(root, 2);
    bst.insert(root, 1);
    bst.insert(root, 10);
    bst.insert(root, 6);
    bst.insert(root, 3);
    bst.insert(root, 8);
    bst.insert(root, 7);
    bst.insert(root, 13);
    bst.insert(root, 20);

    bst.insert(root, 14);
    bst.insert(root, 0);
    bst.insert(root, 35);
    printLevelOrder(root);

    bst.deleteNode(root, 6);
    bst.deleteNode(root, 13);
    bst.deleteNode(root, 35);
    printLevelOrder(root);
    return 0;
}