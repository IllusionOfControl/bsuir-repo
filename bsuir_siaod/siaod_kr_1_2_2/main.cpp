#include <iostream>


class Node
{
public:
    int key;
    Node* leftNode;
    Node* rightNode;
    int height;
};

int max(int a, int b)
{
    return (a > b) ? a : b;
}


int calculateHeight(Node* n)
{
    if (n == NULL)
        return 0;
    return n->height;
}


Node* newNode(int key)
{
    Node* node = new Node();
    node->key = key;
    node->leftNode = NULL;
    node->rightNode = NULL;
    node->height = 1;

    return(node);
}


Node* rightRotate(Node* y)
{
    Node* x = y->leftNode;
    Node* T2 = x->rightNode;

    x->rightNode = y;
    y->leftNode = T2;

    // racalculated height
    y->height = max(calculateHeight(y->leftNode),
        calculateHeight(y->rightNode)) + 1;
    x->height = max(calculateHeight(x->leftNode),
        calculateHeight(x->rightNode)) + 1;

    // return new root
    return x;
}


Node* leftRotate(Node* x)
{
    Node* y = x->rightNode;
    Node* T2 = y->leftNode;

    
    y->leftNode = x;
    x->rightNode = T2;

    // racalculated height
    x->height = max(calculateHeight(x->leftNode),
        calculateHeight(x->rightNode)) + 1;
    y->height = max(calculateHeight(y->leftNode),
        calculateHeight(y->rightNode)) + 1;

    // return new root
    return y;
}


int getBalance(Node* N)
{
    if (N == NULL)
        return 0;
    return calculateHeight(N->leftNode) - calculateHeight(N->rightNode);
}


Node* insertNode(Node* node, int key)
{
    if (!node)
        return(newNode(key));

    if (key < node->key)
        node->leftNode = insertNode(node->leftNode, key);
    else if (key > node->key)
        node->rightNode = insertNode(node->rightNode, key);
    else
        return node;

    node->height = 1 + max(calculateHeight(node->leftNode),
        calculateHeight(node->rightNode));

    int balance = getBalance(node);

    if (balance > 1 && key < node->leftNode->key)
        return rightRotate(node);

    if (balance < -1 && key > node->rightNode->key)
        return leftRotate(node);

    if (balance > 1 && key > node->leftNode->key)
    {
        node->leftNode = leftRotate(node->leftNode);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->rightNode->key)
    {
        node->rightNode = rightRotate(node->rightNode);
        return leftRotate(node);
    }

    return node;
}


Node* findNode(struct Node* root, int value) {
    if (root == NULL) return NULL;

    if (value < root->key)
        return findNode(root->leftNode, value);
    else if (value > root->key)
        return findNode(root->rightNode, value);
    return root;
}


void preorderTraverse(Node* root)
{
    if (root != NULL)
    {
        std::cout << root->key << " ";
        preorderTraverse(root->leftNode);
        preorderTraverse(root->rightNode);
    }
}


int main()
{
    Node* root = NULL;

    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 20);
    root = insertNode(root, 14);
    root = insertNode(root, 10);
    root = insertNode(root, 18);
    root = insertNode(root, 99);
    root = insertNode(root, 40);
    root = insertNode(root, 50);
    root = insertNode(root, 25);
    root = insertNode(root, 66);
    root = insertNode(root, 78);
    root = insertNode(root, 45);
    root = insertNode(root, 86);

    std::cout << "Preorder traversal of the "
        "constructed AVL tree is \n";
    preorderTraverse(root);    
    std::cout << "Search 99 element\n"
    "Node: " << findNode(root, 99)->key << "\t| Height: " << findNode(root, 99)->height;

    return 0;
}
