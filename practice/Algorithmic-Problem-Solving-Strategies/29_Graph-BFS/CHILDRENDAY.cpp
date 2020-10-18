/* https://algospot.com/judge/problem/read/CHILDRENDAY
 Cond. (C >= n + m) && (C % n == m) && C consists of numbers in d.
 
 Find out the proper C matched in condition 2. from condition 3.
 To make the problem simpler, except (C >= n + m).
 
 We can easily calculate the remainder of C
 by adding x to the back of C and dividing n.
    --> (C % n) * 10 + x) % n = (C * 10 + x) % n,
 
 Graph modeling
    - Each (C % n) (=raminder) becomes a vertex. So, graph has n vertexes.
    - Each edge has the number, x, where x satisfies the following conditions.
        - (V1 * 10 + x) % n = V2,
        - where V1 is the current state (= vertex = remainder of C),
        - where V2 is the next state.
    - Searching finishes at the vertex that has the number m.
    - Notice that there can be two or more shortest paths.
        - It is solved by ordering alphabetically the number (=x) of edges.
        - If we visit from the edge that has the smallest number to other edges,
        we can discover the shortest path edges of which have the smallest order alphabetically.
    - In case of m == 0, we can find the shortest path from 0 to 0.
        - It is a cycle, but our graph does not have cycles.
        - It is solved by dividing each vertex into two.
        - One is smaller than n and the other is equal or larger than n.
        - i.e. the graph can have two or more state components.
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// If the current vertex is `here`,
// return the vertex when following the `edge`.
int append(int here, int edge, int mod) {
    int there = here * 10 + edge;
    if (there >= mod) return mod + there % mod;
    return there % mod;
}

// C % n == m && minimum C consisting of numbers in digits.
string gifts(string digits, int n, int m) {
    // Order the number of edges by ascending.
    sort(digits.begin(), digits.end());
    // parent[i] = the parent of i-th vertex in BFS spanning tree.
    vector<int> parent(2*n, -1);
    // choice[i] = the number of the edge from parent[i] to i-th vertex.
    vector<int> choice(2*n, -1);
    queue<int> q;
    // Add white vertex 0.
    parent[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int here = q.front();
        q.pop();
        for (int i=0; i<digits.size(); i++) {
            int there = append(here, digits[i] - '0', n);
            if (parent[there] == -1) {
                parent[there] = here;
                choice[there] = digits[i] - '0';
                q.push(there);
            }
        }
    }
    
    // Failed if it did not reach to m.
    if (parent[n + m] == -1) return "IMPOSSIBLE";
    // Calculate C by following the ancestors.
    string ret;
    int here = n + m;
    while (parent[here] != here) {
        ret += char('0' + choice[here]);
        here = parent[here];
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

void solve() {
    string d;
    int n, m;
    cin >> d >> n >> m;
    cout << gifts(d, n, m) << endl; // O(2 * n * |d|)
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
