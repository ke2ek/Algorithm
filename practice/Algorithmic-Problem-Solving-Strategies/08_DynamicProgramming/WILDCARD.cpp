// https://algospot.com/judge/problem/read/WILDCARD
#include <iostream>
#include <cstring>
#include <string>
#include <set>
#define MAX_N 101
using namespace std;

// cache[i][j] = 1 if pattern[0..i] and input[0..j] are matched, otherwise 0, (default = -1).
int cache[101][101];
string pattern, input;

// O(n^3)
bool match(int i, int j) {
    int &ret = cache[i][j];
    if (ret != -1) return ret;
    while (i < pattern.size() and j < input.size() and
           (pattern[i] == '?' or pattern[i] == input[j]))
    { i++; j++; }
    if (i == pattern.size()) return ret = (j == input.size());
    if (pattern[i] == '*')
        for (int next = j; next <= input.size(); next++)
            if (match(i+1, next))
                return ret = true;
    return ret = false;
}

// O(n^2), Use Cache Actively!
bool matchOptimized(int i, int j) {
    int &ret = cache[i][j];
    if (ret != -1) return ret;
    if (i < pattern.size() and j < input.size() and
        (pattern[i] == '?' or pattern[i] == input[j]))
        return ret = matchOptimized(i+1, j+1);
    if (i == pattern.size()) return ret = (j == input.size());
    if (pattern[i] == '*')
        if (matchOptimized(i+1, j) or (j < input.size() and matchOptimized(i, j+1)))
            return ret = true;
    return ret = false;
}

void solve() {
    int N;
    multiset<string> ret;
    cin >> pattern >> N;
    while (N--) {
        cin >> input;
        memset(cache, -1, sizeof(cache));
        if (matchOptimized(0, 0))
            ret.insert(input);
    }
    for (auto &s : ret) cout << s << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
