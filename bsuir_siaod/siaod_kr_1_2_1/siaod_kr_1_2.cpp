#include <iostream>
#include <queue>

// ���� ������
struct Node
{
    int value;
    Node* left;
    Node* right;

    bool isBinded = false;

    Node(int value) : value(value), left(nullptr), right(nullptr) {}
};

class Tree {
public:
    Node* root;

    // ���������� ����� � �������
    void ToQueue(Node* node, std::queue<Node*>* node_queue)
    {
        if (node == nullptr)
            return;
        if (node->left != nullptr)
            ToQueue(node->left, node_queue);
        node_queue->push(node);
        if (node->right != nullptr)
            ToQueue(node->right, node_queue);
    }

    
    // ������������ ������� ����� ����� ������ ��� ������� ��������������� ������
    void BindingOfLeaves(Node* node, std::queue<Node*>* tree_queue) {
        if (!node) return;

        if (node->left) BindingOfLeaves(node->left, tree_queue);

        tree_queue->pop();

        if (node->right != nullptr)
            BindingOfLeaves(node->right, tree_queue);

        else
        {
            if (tree_queue->size() != 0)
                node->right = tree_queue->front();
            node->isBinded = true;
        }
    }

    // �������� ������
    void FirmwareTree(Node* node) {
        std::queue<Node*> tree_queue;

        ToQueue(node, &tree_queue);

        BindingOfLeaves(node, &tree_queue);
    }


    // �������� �� ������ ���������� �������� �� ����� �����
    Node* WalkToLastLeftNode(Node* node)
    {
        while (node && node->left)
            node = node->left;
        return node;
    }

    // ������������ ����� ������� ������
    void WalkTree(Node* node)
    {
        if (!node) return;

        Node* left = WalkToLastLeftNode(node);

        while (left)
        {
            std::cout << " " << left->value << "" << std::endl;

            if (left->isBinded == true)
                left = left->right;
            else
                left = WalkToLastLeftNode(left->right);
        }
    }
};
    


int main()
{
    Tree tree;
    tree.root = new Node(121);
    tree.root->left = new Node(64);
    tree.root->right = new Node(48);
    tree.root->right->left = new Node(32);
    tree.root->right->right = new Node(0);

    tree.FirmwareTree(tree.root);
    std::cout << "Symetric tree walk: " << std::endl;
    tree.WalkTree(tree.root);
}
