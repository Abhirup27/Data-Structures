#include<BinaryTree.hpp>
#include<queue>
#include <string>
#include <cmath>
#include <iomanip>

BinaryTree::BinaryTree(int32_t num) :currNode(0){
	node* newNode = new node{ num, nullptr, nullptr };
	root = newNode;
	enqueue(root);

}

BinaryTree::BinaryTree() :currNode(0) {
	
	root = nullptr;
	//queue->ptr = *root;
}

bool BinaryTree::enqueue(node* newnode)
{
	if (queue == nullptr || (front == nullptr && back == nullptr))
	{
		queue_node* newEle = new queue_node{ .ptr = newnode, .next = nullptr };
		queue = newEle;
		front = newEle;
		back = newEle;

		return true;
	}
	else
	{
		queue_node* newEle = new queue_node{ .ptr = newnode, .next = nullptr };
		if (front == back)
		{
			back = newEle;
			back->next = front;
			queue = back;
			return true;
		}
		else
		{
			queue = newEle;
			queue->next = back;
			back = queue;
			return true;
		}
	}

	return false;
}

BinaryTree::node* BinaryTree::dequeue()
{
	queue_node* to_return = front;

	if (front == back)
	{
		queue = front = back = nullptr;
		
	}
	else
	{

		while (queue->next != front)
		{
			queue = queue->next;
		}
		queue->next = nullptr;
		front = queue;
		queue = back;
	}

	return to_return->ptr;


}

bool BinaryTree::is_queue_empty()
{
	if (queue == nullptr || (front == nullptr))
	{
		return true;
	}
	else {
		return false;
	}
}

bool BinaryTree::createTreeNode(int32_t l, int32_t r)
{
	currNode++;
	BinaryTree::node* TNode = dequeue();
	int32_t val_l{ l }, val_r{r};

	std::cout << "Enter the " << currNode << "th node's left child's value, Enter 0 to not create left child :" << l <<std::endl;
	//std::cin >> val_l;
	if (val_l != 0)
	{
		BinaryTree::node* node = new BinaryTree::node{ .data = val_l, .left = nullptr, .right = nullptr };
		TNode->left = node;
		enqueue(node);

	}
	std::cout << "Enter the " << currNode << "th node's right child's value, Enter 0 to not create right child :"<<r<<std::endl;
	//std::cin >> val_r;
	if (val_r != 0)
	{
		BinaryTree::node* node = new BinaryTree::node{ .data = val_r, .left = nullptr, .right = nullptr };
		TNode->right = node;
		enqueue(node);
	}
	if (val_r == 0)
		currNode++;
	if (val_l == 0)
		currNode++;
	return true;

}
void BinaryTree::printLevelOrder() {
	if (root == nullptr) {
		std::cout << "Tree is empty\n";
		return;
	}

	
	std::queue<node*> q;
	q.push(root);

	int level = 0;
	while (!q.empty()) {
		int levelSize = q.size();
		std::cout << "Level " << level << ": ";

		
		for (int i = 0; i < levelSize; i++) {
			node* current = q.front();
			q.pop();

			std::cout << current->data << " ";

			if (current->left != nullptr)
				q.push(current->left);
			if (current->right != nullptr)
				q.push(current->right);
		}
		std::cout << "\n";
		level++;
	}
}

void BinaryTree::printInorder() {
	if (root == nullptr) {
		std::cout << "Tree is empty\n";
		return;
	}
	std::cout << "Inorder traversal: ";
	printInorderRecursive(root);
	std::cout << "\n";
}

void BinaryTree::printInorderRecursive(node* current) {
	if (current == nullptr) return;

	printInorderRecursive(current->left);
	std::cout << current->data << " ";
	printInorderRecursive(current->right);
}

void BinaryTree::printTreeVisual() {
	if (root == nullptr) {
		std::cout << "Tree is empty\n";
		return;
	}
	printTreeRecursive(root, "", false);
}


void BinaryTree::printTreeRecursive(node* root, std::string prefix, bool isLeft) {

	if (root == nullptr) {
		return;
	}

	std::cout << prefix;
	std::cout << (isLeft ? "|-- " : "+-- ");
	std::cout << root->data << std::endl;

	// Enter the next tree level - left and right branch
	printTreeRecursive(root->left, prefix + (isLeft ? "|   " : "    "), true);
	printTreeRecursive(root->right, prefix + (isLeft ? "|   " : "    "), false);

}
int main(int argc, const char* argv[])
{
	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " <number1> <number2> ...\n For e.g. : " << argv[0] << " " << "2 3 4 6 7 8 \n" << "Visual representation of the tree:\n+-- 2\n    |-- 3\n    |   |-- 6\n    |   +-- 7\n    +-- 4\n        |-- 8";
		return 1;
	}
	size_t i = 2;
	BinaryTree t1 = BinaryTree(std::stoi(argv[1]));

	while (t1.is_queue_empty() == false)
	{
		if(i< argc)
		{
			if(i+1 <argc)
			{

				t1.createTreeNode(std::stoi(argv[i]), std::stoi(argv[i + 1]));
				i += 2;
			}
			else
			{
				t1.createTreeNode(std::stoi(argv[i]), 0);
				i += 1;
			}

		}
		else
		{
			t1.createTreeNode(0,0);
		}

	}
	std::cout << "\nPrinting tree level by level:\n";
	t1.printLevelOrder();

	std::cout << "\nPrinting tree in inorder:\n";
	t1.printInorder();

	std::cout << "\nVisual representation of the tree:\n\n";
	t1.printTreeVisual();

	return 0;
}