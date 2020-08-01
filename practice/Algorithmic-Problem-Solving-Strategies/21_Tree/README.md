# Tree

## Basic

- **Node**. component of a tree
	- Parent, Child, Sibling
	- Ancestor, Descendant
	- Root, Leaf
- Property
	- **Depth of node**. the number of edges from root to the node
	- **Height of tree**. the depth of the deepest node
	- **Subtree**. consisting of descendants of the node, where the node is root in a subtree
		- it's recursive so functions handling a tree are implemented recursively.
- Representation as Structure or Object
	- the following shows the basic structure, which does not have any constraint.

	``` c++
	struct TreeNode {
		string label; // data to save
		TreeNode* parent; // the pointer referring to own parent
		vector<TreeNode*> children; // the pointers referring to own children
	}
	```

	- constrains
		- binary search tree
		- heap
		- mutual exclusive set structure

## Traversal
	
- Time Complexity: **O(n)**
	- where n is the number of nodes in a tree
	- the following functions are called respectively for each node in a tree.
	
	``` c++
	// Print all nodes of a tree
	void printLabels(TreeNode* root) {
		cout << root->label << endl;
		for (int i = 0; i < root->children.size(); i++) {
			printLabels(root->children[i]);
		}
	}

	// Return the height of a tree.
	int height(TreeNode* root) {
		int h = 0;
		for (int i = 0; i < root->children.size(); i++) {
			h = max(h, height(root->children[i]) + 1);
		}
		return h;
	}
	```

