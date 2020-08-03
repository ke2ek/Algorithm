#include <iostream>
#include <stdlib.h>
using namespace std;

struct node {
	int key;
	struct node* left;
	struct node* right;
};

struct node* insertNode(struct node* root, int key)
{
	if (root == 0) {
		root = (struct node*) malloc(sizeof(struct node));
		root->key = key;
		root->left = 0;
		root->right = 0;
		return root;
	}

	if (root->key > key) {
		root->left = insertNode(root->left, key);
	} else if (root->key < key) {
		root->right = insertNode(root->right, key);
	}

	return root;
}

struct node* search(struct node* root, int key)
{
	if (root == 0 || root->key == key) {
		return root;
	} else if (root->key > key) {
		return search(root->left, key);
	}
	return search(root->right, key);
}

struct node* getSuccessor(struct node* node)
{
	struct node* current = node; 
	
	/* loop down to find the leftmost leaf */
	while (current && current->left != 0)
		current = current->left;

	return current;
}

struct node* deleteNode(struct node* root, int key)
{
	if (root == 0) return root;
	if (root->key > key) {
		root->left = deleteNode(root->left, key);
	} else if (root->key < key) {
		root->right = deleteNode(root->right, key);
	} else {
		
		if (root->left == 0 && root->right == 0) {
			free(root);
			return 0;
		}
		
		// node with only one child
		if (root->left == 0) {
			struct node* temp = root->right;
			free(root);
			return temp;
		}
		
		if (root->right == 0) {
			struct node* temp = root->left;
			free(root);
			return temp;
		}

		// node with two children:
		// Get the inorder successor
		// (smallest in the right subtree) 
		struct node* successor = getSuccessor(root->right);
		
		// Copy the inorder successor's content to this node 
		root->key = successor->key;
		
		// Delete the inorder successor 
		root->right = deleteNode(root->right, successor->key);
	}
	return root;
}

void print(struct node* root, int indent) {
	if (root == 0) return;
	for (int i=0; i<indent; i++) cout << "	 ";
	cout << root->key << endl;
	print(root->left, indent+1);
	print(root->right, indent+1);
}

int main() {
	int keys[] = {59, 9, 40, 96, 56, 43, 17, 30, 10, 96};
	struct node* root = 0;
	for (int i=0; i<10; i++) {
		root = insertNode(root, keys[i]);
	}

	for (int i=0; i<5; i++) {
		struct node* found = search(root, keys[i]);
		if (found != 0) {
			cout << "Found = " << found->key << endl;
		}
	}
	cout << endl;
	
	cout << "Before:" << endl;
	print(root, 0);
	deleteNode(root, 10);
	cout << "After deleteing 10:" << endl;
	print(root, 0);
	deleteNode(root, 56);
	cout << "After deleteing 56:" << endl;
	print(root, 0);
	deleteNode(root, 40);
	cout << "After deleteing 40:" << endl;
	print(root, 0);

	return 0;
}
