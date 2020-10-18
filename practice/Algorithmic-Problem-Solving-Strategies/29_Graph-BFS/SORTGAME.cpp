/* https://algospot.com/judge/problem/read/SORTGAME
 Even though the numbers are different, the answers to arrays of the same relative size are always the same.
 For example, the two arrays {30, 40, 10, 20} and {3, 4, 1, 2} have the same relative size of the numbers,
 so the minimum number of operations required is equal to 2.
 
 Since the state space of this problem is a two-way graph, the shortest path from the the start vertex
 to the target vertex is the same as the shortest path from the target vertex to the start vertex.
 In other words, the number of operations required to sort an array equals the number of operations
 required to change the sorted array to the original array.
 */
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

// key: sequence, value: distance
map<vector<int>, int> dist;
void precalc(int n) {
    vector<int> perm(n);
    for (int i=0; i<n; i++) perm[i] = i;
    queue<vector<int> > q;
    q.push(perm);
    dist[perm] = 0;
    while (!q.empty()) {
        vector<int> here = q.front();
        q.pop();
        int cost = dist[here];
		// Visiting next vertexes
        for (int i=0; i<n; i++) {
            for (int j=i+2; j<=n; j++) {
                reverse(here.begin() + i, here.begin() + j);
                if (dist.count(here) == 0) {
                    dist[here] = cost + 1;
                    q.push(here);
                }
                reverse(here.begin() + i, here.begin() + j);
            }
        }
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> seq(n);
    for (int i=0; i<n; i++)
        cin >> seq[i];
    
    precalc(n);
    vector<int> fixed(n); // fixed[i] = # of numbers smaller than seq[i]
    for (int i=0; i<n; i++) {
        int smaller = 0;
        for (int j=0; j<n; j++)
            if (seq[j] < seq[i])
                smaller++;
        fixed[i] = smaller;
    }
    cout << dist[fixed] << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
