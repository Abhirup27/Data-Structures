#include <iostream>

class BinaryTree {
    uint32_t currNode;
    struct node {
        int32_t data;
        node* left;
        node* right;
    };
    struct queue_node
    {
        node* ptr;
        queue_node* next;
    };
    void printInorderRecursive(node* current);
    void printTreeRecursive(node* root, std::string prefix = "", bool isLeft = false);
public:
    queue_node* front{nullptr};
    queue_node* back{nullptr};
    queue_node* queue{nullptr};
    node* root{ nullptr };
    explicit BinaryTree(int32_t num);
    BinaryTree();

    bool enqueue(node*);
    node* dequeue();

    bool is_queue_empty();

    bool createTreeNode(int32_t l, int32_t r);
    void printLevelOrder(); // Print tree level by level
    void printInorder(); // Print tree in inorder traversal
    void printTreeVisual();
};