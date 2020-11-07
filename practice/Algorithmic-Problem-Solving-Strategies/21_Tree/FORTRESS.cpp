// https://algospot.com/judge/problem/read/FORTRESS
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode {
    vector<TreeNode*> children;
};

int n, y[100], x[100], radius[100];

int sqr(int x) {
    return x * x;
}

// distance of a and b
int sqrdist(int a, int b) {
    return sqr(y[a] - y[b]) + sqr(x[a] - x[b]);
}

// check if a castle wall `a` has `b`
bool encloses(int a, int b) {
    return radius[a] > radius[b] &&
                 sqrdist(a, b) < sqr(radius[a] - radius[b]);
}

// check if a parent node is direct parent of a child
// in a castle tree
bool isChild(int parent, int child) {
    if (!encloses(parent, child)) return false;
    for (int i = 0; i < n; i++) {
        // check if there is a castle wall between parent and child
        if (i != parent && i != child &&
                encloses(parent, i) && encloses(i, child))
            return false;
    }
    return true;
}

TreeNode* getTree(int root) {
    TreeNode *ret = new TreeNode();
    for (int ch = 0; ch < n; ch++) {
        if (isChild(root, ch))
            ret->children.push_back(getTree(ch));
    }
    return ret;
}

// the longest path of leaf-leaf nodes found so far
int longest;

// return height of current tree
int height(TreeNode* root) {
    vector<int> heights;
    for (int i=0; i<root->children.size(); i++) {
        heights.push_back(height(root->children[i]));
    }

    if (heights.empty()) return 0;
    sort(heights.begin(), heights.end());
    if (heights.size() >= 2) {
        // consider the path when root is top-level node
        longest = max(longest, 2 + heights[heights.size()-2]
                                 + heights[heights.size()-1]);
    }

    // height of current tree = height of a subtree + 1
    return heights.back() + 1;
}

int solve(TreeNode* root) {
    longest = 0;
    int h = height(root);
    return max(longest, h);
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i=0; i<n; i++) {
            cin >> x[i] >> y[i] >> radius[i];
        }
        TreeNode* root = getTree(0);
        cout << solve(root) << endl;
    }
    return 0;
}
