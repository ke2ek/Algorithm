// https://algospot.com/judge/submission/recent/
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

const int MAX_DISCS = 12;
int c[1 << (MAX_DISCS * 2)];

// Each state are indicated as `integer` type,
// in which each 2-bits means that which pillar the disk hangs on.
// Notice that # of pillar of each disk are expressed as only 2-bits.

int get(int state, int index) {
    return (state >> (index * 2)) & 3;
}

// index = # of disk
// value = # of pillar
int set(int state, int index, int value) {
    return (state & ~(3 << (index * 2))) | (value << (index * 2));
}

// Slow Solution: BFS
// Return the minimum movements.
int bfs(int discs, int begin, int end) {
    if (begin == end) return 0;
    queue<int> q;
    memset(c, -1, sizeof(c));
    q.push(begin);
    c[begin] = 0;
    while (!q.empty()) {
        int here = q.front();
        q.pop();
        // Calculate the number of discs at the top of each column.
        int top[4] = { -1, -1, -1, -1 };
        for (int i=discs-1; i>=0; i--)
            top[get(here, i)] = i;
        // Move the disc from i to j.
        for (int i=0; i<4; i++) {
            if (top[i] == -1) continue;
            for (int j=0; j<4; j++) {
                if (i != j && (top[j] == -1 || top[j] > top[i])) {
                    int there = set(here, top[i], j);
                    if (c[there] != -1) continue;
                    c[there] = c[here] + 1;
                    if (there == end) return c[there];
                    q.push(there);
                }
            }
        }
    }
    return -1;
}

int sgn(int x) {
    if (!x) return 0;
    return x > 0 ? 1 : -1;
}

int incr(int x) {
    if (x < 0) return x - 1;
    return x + 1;
}

// Bidirectional Search
int bidir(int discs, int begin, int end) {
    if (begin == end) return 0;
    queue<int> q;
    memset(c, 0, sizeof(c));
    
    q.push(begin); c[begin] = 1;
    q.push(end); c[end] = -1;
    while (!q.empty()) {
        int here = q.front();
        q.pop();
        int top[4] = { -1, -1, -1, -1 };
        for (int i=discs-1; i>=0; i--)
            top[get(here, i)] = i;
        for (int i=0; i<4; i++) {
            if (top[i] == -1) continue;
            for (int j=0; j<4; j++) {
                if (i != j && (top[j] == -1 || top[j] > top[i])) {
                    int there = set(here, top[i], j);
                    if (c[there] == 0) {
                        c[there] = incr(c[here]);
                        q.push(there);
                    } else if (sgn(c[there]) != sgn(c[here])) {
                        return abs(c[there]) + abs(c[here]) - 1;
                    }
                }
            }
        }
    }
    return -1;
}

void solve() {
    int a, b;
    cin >> a;
    int begin = 0, end = 0;
    for (int i=0; i<4; i++) {
        cin >> b;
        for (int j=0; j<b; j++) {
            int x;
            cin >> x;
            begin = set(begin, x-1, i);
        }
    }
    for (int i=0; i<a; i++)
        end = set(end, i, 3);
    
    // cout << bfs(a, begin, end) << endl;
    cout << bidir(a, begin, end) << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
