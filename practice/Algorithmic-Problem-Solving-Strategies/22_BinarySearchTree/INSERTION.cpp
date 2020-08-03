// https://algospot.com/judge/problem/read/INSERTION
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

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


// Find the k-th node.
Node* kth(Node* root, int k) {
    int leftSize = 0; // First, calculate the size of left subtree.
    if (root->left != 0) leftSize = root->left->size;
    if (k <= leftSize) return kth(root->left, k);
    if (k == leftSize + 1) return root;
    return kth(root->right, k - leftSize - 1);
}


int N;
int shifted[50000]; // shifted[i] = how many times move A[i]
int A[50000];

void solve() {
    cin >> N;
    for (int i=0; i<N; i++)
        cin >> shifted[i];
    
    Node* candidates = 0;
    for (int i=0; i<N; i++)
        candidates = insert(candidates, new Node(i+1));
    
    for (int i=N-1; i>=0; i--) {
        int larger = shifted[i];
        Node* k = kth(candidates, i + 1 - larger);
        A[i] = k->key;
        candidates = erase(candidates, k->key);
    }
    
    for (int i=0; i<N; i++)
        cout << A[i] << " ";
    cout << endl;
}


int main() {
    srand(time(0));
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
