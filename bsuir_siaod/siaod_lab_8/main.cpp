#include <iostream>


struct Node {
    int value;
    struct Node* left;
    struct Node* right;
};


struct Node* NewNode(int value) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->value = value;
    temp->left = temp->right = NULL;
    return temp;
}

// симетричный обход
void InorderTraverse(struct Node* root) {
    if (root != NULL) {
        InorderTraverse(root->left);
        std::cout << root->value << " -> ";
        InorderTraverse(root->right);
    }
}


// прямой обход
void PreorderTraverse(struct Node* root) {
    if (root != NULL) {
        std::cout << root->value << " -> ";
        PreorderTraverse(root->left);
        PreorderTraverse(root->right);
    }
}

// обратный обход
void PostorderTraverse(struct Node* root) {
    if (root != NULL) {
        PostorderTraverse(root->left);
        PostorderTraverse(root->right);
        std::cout << root->value << " -> ";
    }
}


// добавление в бинарное дерево
struct Node* InsertToBST(struct Node* node, int value) {
    if (node == NULL) return NewNode(value);

    if (value < node->value)
        node->left = InsertToBST(node->left, value);
    else
        node->right = InsertToBST(node->right, value);

    return node;
}


// нахождение меньшего значения
struct Node* MinValueNode(struct Node* node) {
    struct Node* current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}


// удаление ветви
struct Node* DeleteFromBST(struct Node* root, int value) {
    if (root == NULL) return root;

    if (value < root->value)
        root->left = DeleteFromBST(root->left, value);
    else if (value > root->value)
        root->right = DeleteFromBST(root->right, value);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = MinValueNode(root->right);

        root->value = temp->value;

        root->right = DeleteFromBST(root->right, temp->value);
    }
    return root;
}


// проверка на содержание
bool Contains(struct Node* root, int value) {
    if (root == NULL) return false;

    if (value < root->value)
        return Contains(root->left, value);
    else if (value > root->value)
        return Contains(root->right, value);
    return true;
}


int main() {
    struct Node* root = NULL;
    root = InsertToBST(root, 8);
    root = InsertToBST(root, 3);
    root = InsertToBST(root, 1);
    root = InsertToBST(root, 6);
    root = InsertToBST(root, 7);
    root = InsertToBST(root, 10);
    root = InsertToBST(root, 14);
    root = InsertToBST(root, 4);
    root = InsertToBST(root, 24);
    root = InsertToBST(root, 15);
    root = InsertToBST(root, 5);

    std::cout << "Inorder traversal: ";
    InorderTraverse(root);
    std::cout << std::endl;

    std::cout << "Is contains 6?: " << std::boolalpha << Contains(root, 6) << std::endl;

    std::cout << "Deleting 6" << std::endl;
    root = DeleteFromBST(root, 6);
    
    std::cout << "Is contains 6?: " << std::boolalpha << Contains(root, 6) << std::endl;

    std::cout << "Inorder traversal: ";
    InorderTraverse(root);
    std::cout << "\nPreorder traversal: ";
    PreorderTraverse(root);
    std::cout << "\nPostorder traversal: ";
    PostorderTraverse(root);
}