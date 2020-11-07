# Binary Search Tree

## Basic

- Each node has two children at most.
- Left subtree contains only nodes with values lesser than it of parent node.
- Right subtree contains only nodes with values greater than it of parent node.
- There must be no duplicate nodes.
- Time Complexity of search is the same as binary search.
- But, time complexity of insertion and deletion in Binary Search Tree is so faster than binary search with sorted array.
    - Given a sorted array, a binary search must move all elements being behind the inserted/deleted element.

    ``` c++
    struct node {
        int key;
        struct node *left, *right;
    };
    ```

## Search

- Time Complexity: O(lgN)

    ``` c++
    // C function to search a given key in a given BST
    struct node* search(struct node* root, int key)
    {
        // Base Cases: root is null or key is present at root
        if (root == NULL || root->key == key)
           return root;

        // Key is greater than root's key
        if (root->key < key)
           return search(root->right, key);

        // Key is smaller than root's key
        return search(root->left, key);
    }
    ```

## Insertion

- Time Complexity: O(lgN)
- A new node is always inserted at leaf.

    ``` c++
    struct node* insert(struct node* root, int key)
    {
        if (root == 0) {
            root = (struct node*) malloc(sizeof(struct node));
            root->key = key;
            root->left = 0;
            root->right = 0;
            return root;
        }

        if (root->key > key) {
            root->left = insert(root->left, key);
        } else if (root->key < key) {
            root->right = insert(root->right, key);
        }
        return root;
    }
    ```

## Deletion

- To keep properties of binary search tree, there are the following rules..
    - if a leaf node is deleted, just remove.
    - if node to be deleted has only one child, the child node becomes the node, and then remove the node.
    - if node to be deleted has two children, the remove the node after finding inorder successor node and moving it to the node.
    
    ``` c++
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
    ```

## Balanced Binary Search Tree

- We have been handling an unbalanced tree so far. The disadvantage is to spend O(n) to insert/delete/search when entered the ordered keys, where n is the number of nodes in a tree.
- It keeps nodes fairly regardless of the order of input. It seems like a flat tree because it is not biased one way.
- height of a tree is always O(lgN)
- [Red-Black Tree](https://en.wikipedia.org/wiki/Red–black_tree)
- [Treap](http://www.secmem.org/blog/2019/07/22/Treap/)
    - Randomized Binary Search Tree
    - The order of each node is determined arbitrarily. (not order when added)
    - So, no matter which node is added or removed, the expected of the height of a tree is constant.
    - To keep these properties, assign a priority to each node.
        - Parent has always higher priority than children.
        - (Binary Search Tree's Condition) Left subtree has always lower priority than root node.
        - (Binary Search Tree's Condition) Right subtree has always higher priority than root node.
        - (Heap's condition) The priority of all nodes is greater or equal than their children.
    
    ``` c++
    typedef int KeyType;

    struct Node {
        KeyType key;
        int priority;
        int size;
        Node *left, *right;

        Node(const KeyType& _key)
        : key(_key), priority(rand() % 100), size(1), left(0), right(0) {}

        void setLeft(Node* newLeft) {
            left = newLeft;
            calcSize();
        }

        void setRight(Node* newRight) {
            right = newRight;
            calcSize();
        }

        void calcSize() {
            size = 1;
            if (left) size += left->size;
            if (right) size += right->size;
        }
    };
    ```
    
    - It is different from BST that comparing the priority is required to insert a node.
        - Notice that a tree should split its own subtree to insert a new node at no-leaf.

    ``` c++
    typedef pair<Node*, Node*> NodePair;

    NodePair split(Node* root, KeyType key) {
        if (root == 0) return NodePair(0, 0);
        if (root->key < key) {
            NodePair rs = split(root->right, key);
            root->setRight(rs.first);
            return NodePair(root, rs.second);
        }

        NodePair ls = split(root->left, key);
        root->setLeft(ls.second);
        return NodePair(ls.first, root);
    }

    Node* insert(Node* root, Node* node) {
        if (root == 0) return node;
        if (root->priority < node->priority) {
            NodePair splitted = split(root, node->key);
            node->setLeft(splitted.first);
            node->setRight(splitted.second);
            return node;
        } else if (node->key < root->key) {
            root->setLeft(insert(root->left, node));
        } else {
            root->setRight(insert(root->right, node));
        }
        return root;
    }
    ```

    - It is similar to BST except merging is performed with the priority if a node to be erased has children.
    
    ``` c++
    Node* merge(Node* a, Node* b) {
        if (a == 0) return b;
        if (b == 0) return a;
        if (a->priority < b->priority) {
            b->setLeft(merge(a, b->left));
            return b;
        }
        a->setRight(merge(a->right, b));
        return a;
    }

    Node* erase(Node* root, KeyType key) {
        if (root == 0) return root;
        if (root->key == key) {
            Node* ret = merge(root->left, root->right);
            root->left = 0;
            root->right = 0;
            delete root;
            return ret;
        }
        if (key < root->key) {
            root->setLeft(erase(root->left, key));
        } else {
            root->setRight(erase(root->right, key));
        }
        return root;
    }
    ```

    - Also, there are finding the k-th node or counting the number of nodes to have a key less than X.
    - Find the k-th node.
        - k <= l : k-th node belongs to left subtree
        - k = l+1 : current root is k-th node
        - k > l+1 : k-th node belongs to right subtree, in which k-th becomes the (k-l-1)-th node.
    
    ``` c++
    Node* kth(Node* root, int k) {
        int leftSize = 0; // First, calculate the size of left subtree.
        if (root->left != 0) leftSize = root->left->size;
        if (k <= leftSize) return kth(root->left, k);
        if (k == leftSize + 1) return root;
        return kth(root->right, k - leftSize - 1);
    }
    ```

    - Count the number of nodes to have a key less than X.
    
    ``` c++
    int countLessThan(Node* root, KeyType key) {
        if (root == 0) return 0;
        if (root->key >= key) {
            return countLessThan(root->left, key);
        }
        int ls = (root->left ? root->left->size : 0);
        return ls + 1 + countLessThan(root->right, key);
    }
    ```

