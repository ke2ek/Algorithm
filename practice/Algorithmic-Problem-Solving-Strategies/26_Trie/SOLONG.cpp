// https://algospot.com/judge/problem/read/SOLONG
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#define toIndex(x) x - 'A'
using namespace std;

const int ALPHABETS = 26;

class TrieNode {
public:
    TrieNode* children[ALPHABETS];
    int terminal; // the number of terminated string (if none, -1)
    int first; // the first added word's number
    
    TrieNode(): terminal(-1), first(-1) {
        memset(children, 0, sizeof(children));
    }
    
    ~TrieNode() {
        for (int i=0; i<ALPHABETS; i++)
            delete children[i];
    }
    
    void insert(const char* key, int id) {
        if (first == -1) first = id;
        if (*key == 0) {
            terminal = id;
        } else {
            int next = toIndex(*key);
            if (children[next] == 0) {
                children[next] = new TrieNode();
            }
            children[next]->insert(key + 1, id);
        }
    }
    
    TrieNode* find(const char* key) {
        if (*key == 0) return this;
        int next = toIndex(*key);
        if (children[next] == 0) return 0;
        return children[next]->find(key + 1);
    }
    
    // return how many times we type to enter the string `key`, number `id`
    int type(const char* key, int id) {
        if (*key == 0) return 0;
        // if the recommended string is the current string (number `id`), return 1 (tab key)
        if (first == id) return 1;
        int next = toIndex(*key); // type the next character
        return 1 + children[next]->type(key + 1, id);
    }
};

// return how many times we type to enter the given word
int countKeys(TrieNode* trie, const char* word) {
    TrieNode* node = trie->find(word);
    if (node == 0 || node->terminal == -1)
        return strlen(word);
    return trie->type(word, node->terminal);
}

TrieNode* readInput(int words) {
    vector<pair<int, string> > input;
    for (int i=0; i<words; i++) {
        char buf[11];
        int freq;
        scanf("%s %d", buf, &freq);
        input.emplace_back(-freq, buf);
    }
    
    sort(input.begin(), input.end());
    
    // the higher the word is in front, the higher the priority.
    // the index of an array is used as the number of each string.
    TrieNode* trie = new TrieNode();
    for (int i=0; i<input.size(); i++) {
        trie->insert(input[i].second.c_str(), i);
    }
    trie->first = -1;
    return trie;
}


void solve() {
    int n, m;
    scanf("%d %d", &n, &m);
    TrieNode* trie = readInput(n);
    
    int ret = 0;
    for (int i=0; i<m; i++) {
        char word[11];
        scanf("%s", word);
        ret += countKeys(trie, word) + 1;
    }
    printf("%d\n", ret - 1);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
