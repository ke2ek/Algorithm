// https://algospot.com/judge/problem/read/MEASURETIME#
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

// Using Treap (a.k.a. Binary Search Tree)
struct Node {
    int key;
    int priority;
    int size;
    Node *left, *right;
    
    Node(const int& _key)
    : key(_key), priority(rand() % 100), size(1), left(0), right(0) {}
    
    void setLeft(Node *newLeft) {
        left = newLeft;
        calcSize();
    }
    
    void setRight(Node *newRight) {
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

NodePair split(Node* root, int key) {
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
    if (root ==0) return node;
    if (root->priority < node->priority) {
        NodePair splitted = split(root, node->key);
        node->setLeft(splitted.first);
        node->setRight(splitted.second);
        return node;
    } else if (root->key > node->key) {
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

Node* erase(Node* root, int key) {
    if (root == 0) return root;
    if (root->key == key) {
        Node* ret = merge(root->left, root->right);
        root->left = 0;
        root->right = 0;
        delete root;
        return ret;
    }
    
    if (root->key > key) {
        root->setLeft(erase(root->left, key));
    } else {
        root->setRight(erase(root->right, key));
    }
    return root;
}

// Count the number of nodes to have a key less than X.
int countLessThan(Node* root, int key) {
    if (root == 0) return 0;
    if (root->key >= key) {
        return countLessThan(root->left, key);
    }
    int ls = (root->left ? root->left->size : 0);
    return ls + 1 + countLessThan(root->right, key);
}

void deleteTree(Node* node) {
    if (node == 0) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// O(N * lg(N))
long long countMoves2(const vector<int> &A) {
    Node* root = 0;
    long long ret = 0;
    for (int i=0; i<A.size(); i++) {
        ret += i - countLessThan(root, A[i] + 1);
        root = insert(root, new Node(A[i]));
    }
    deleteTree(root);
    return ret;
}

void solve() {
    int n;
    scanf("%d", &n);
    vector<int> A(n);
    for (int i=0; i<n; i++) scanf("%d", &A[i]);
    printf("%lld\n", countMoves2(A)); // Using Treap
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
