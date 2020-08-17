// https://algospot.com/judge/submission/detail/683274
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#define toIndex(ch) ch - 'a'
using namespace std;

const int ALPHABETS = 26;

class TrieNode {
public:
    TrieNode* children[ALPHABETS];
    int terminal; // the number of terminated string (if none, -1)
    int first; // the first added word's number
    TrieNode* fail; // failure link
    vector<int> output; // output list
    
    int no;
    TrieNode* next[ALPHABETS];
    
    TrieNode(): terminal(-1), first(-1), fail(0) {
        memset(children, 0, sizeof(children));
        memset(next, 0, sizeof(next));
    }
    
    ~TrieNode() {
        output.clear();
        for (int i=0; i<ALPHABETS; i++)
            delete children[i];
    }
    
    /*
     * key: a suffix of the given string
     * id: the number of the given string
     */
    void insert(const char* key, int id) {
        if (first == -1) first = id;
        if (*key == 0) {
            terminal = id;
        } else {
            int chr = toIndex(*key);
            if (children[chr] == 0) {
                children[chr] = new TrieNode();
            }
            children[chr]->insert(key + 1, id);
        }
    }
};


// Calculate failure link and output list.
void computeFailFunc(TrieNode* root) {
    queue<TrieNode*> q;
    root->fail = root;
    q.push(root);
    while (!q.empty()) {
        TrieNode* here = q.front();
        q.pop();
        // visite children
        for (int edge=0; edge<ALPHABETS; edge++) {
            TrieNode* child = here->children[edge];
            if (!child) continue;
            // all nodes in level 1 has root as failure link.
            if (here == root) {
                child->fail = root;
            } else {
                TrieNode* t = here->fail;
                // follow failure link of parent.
                while (t != root && t->children[edge] == 0)
                    t = t->fail;
                if (t->children[edge]) t = t->children[edge];
                child->fail = t;
            }
            child->output = child->fail->output;
            // if there is a needle in this state, add the number of a needle.
            if (child->terminal != -1)
                child->output.push_back(child->terminal);
            q.push(child);
        }
    }
}


// preprocessing
void computeTransition(TrieNode* here, int& nodeCounter) {
    here->no = nodeCounter++;
    for (int chr=0; chr<ALPHABETS; chr++) {
        TrieNode* next = here;
        while (next != next->fail && next->children[chr] == 0)
            next = next->fail;
        if (next->children[chr]) next = next->children[chr];
        here->next[chr] = next;
        if (here->children[chr])
            computeTransition(here->children[chr], nodeCounter);
    }
}


const int MOD = 10007;
int cache[101][1001];

// return the number of strings excluded in IDS
// when the current state is `state` and the `length` letters should be made.
int count(int length, TrieNode* state) {
    // base case: if there is a pattern
    if (state->output.size()) return 0;
    // base case: if all characters are looked at
    if (length == 0) return 1;
    int &ret = cache[length][state->no];
    if (ret != -1) return ret;
    ret = 0;
    for (int letter=0; letter<ALPHABETS; letter++) {
        ret += count(length-1, state->next[letter]);
        ret %= MOD;
    }
    return ret;
}


void solve() {
    int n, m;
    cin >> n >> m;
    
    vector<string> input(m);
    for (int i=0; i<m; i++)
        cin >> input[i];
    sort(input.begin(), input.end());
    
    TrieNode* trie = new TrieNode();
    for (int i=0; i<m; i++)
        trie->insert(input[i].c_str(), i);
    
    computeFailFunc(trie);
    int nodeCounter = 0;
    computeTransition(trie, nodeCounter);
    memset(cache, -1, sizeof(cache));
    cout << count(n, trie) << endl;
}


int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
