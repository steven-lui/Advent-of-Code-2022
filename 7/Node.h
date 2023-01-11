#include <string>
#include <vector>
#include <queue>
using namespace std;

struct Node
{
    int size;
    string name;
    Node *parent;
    vector<Node *> children;
};

Node *getNewNode(int size, string name, Node *parent)
{
    Node *newNode = new Node();
    newNode->size = size;
    newNode->name = name;
    newNode->parent = parent;
    return newNode;
}

void addChild(Node *node, int size, string name, Node *parent)
{
    Node *newNode = getNewNode(size, name, parent);
    node->children.push_back(newNode);
}

Node *findNode(Node *node, const string &name)
{
    if (node == NULL)
        return NULL;

    if (node->name == name)
        return node;

    for (size_t i = 0; i < node->children.size(); i++)
    {
        Node *target = findNode(node->children.at(i), name);
        if (target != NULL)
            return target;
    }

    return NULL;
}

int sumNodes(Node *root)
{
    int sum = 0;

    if (root == nullptr)
        return 0;

    // Creating a queue and pushing the root
    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        int n = q.size();

        // If this node has children
        while (n > 0)
        {

            // Dequeue an item from queue and
            // add it to variable "sum"
            Node *p = q.front();
            q.pop();
            sum += p->size;

            // Enqueue all children of the dequeued item
            for (int i = 0; i < p->children.size(); i++)
                q.push(p->children.at(i));
            n--;
        }
    }
    return sum;
}

struct less_than_size
{
    inline bool operator()(Node *one, Node *two)
    {
        return (sumNodes(one) < sumNodes(two));
    }
};