/* https://algospot.com/judge/problem/read/MEETINGROOM
 Problem) all of the teams should be assigned at the same meeting room,
 but their meeting duration must not be duplicated.
 
 test case) when N = 3, where N is the number of teams,
 Team 0's possible meeting time: 2 5 6 9     --> T0: (2,5), T1: (6,9)
 Team 1's possible meeting time: 1 3 8 10    --> T2: (1,3), T3: (8,10)
 Team 2's possible meeting time: 4 7 11 12   --> T4: (4,7), T5: (11,12)
 
 
 Solution)
 
 First, express the implication graph, in which there are requirements on values included the logical formula as like below.
 
        (T0 || T1) && (T2 || T3) && (T4 || T5) &&
        (!T0 || !T2) && (!T1 || !T3) && (!T1 || !T4) && (!T0 || !T4)
 
    - (Tx || Ty) means that at least one of both has to be assigned to the meeting room.
    - (!Tx || !Ty) means that both x and y must not be assigned together.
    - Also, (Tx || Ty) is described as !Tx => Ty. (!Tx || !Ty) is described as Tx => !Ty.
    - Notice that the arrows(=>) can be indicated in a graph.
 
        !T0 => T1, !T2 => T3, !T4 => T5, T0 => !T2, T1 => !T3, T1 => !T4, T0 => !T4
 
        same as

        T0 => !T2 => T3 => !T1 => T0
        T0 => !T4 => T5
        T1 => !T4 => T5
        T1 => !T3 => T2 => !T0 => T1
        !T5 => T4 => !T1
        !T5 => T4 => T0
 
        p.s: I suggest to draw as like above ^^..
 
 Second, group vertexes of above graph by SCCs.
 
    - A SCC includes the opposite of vertexes another SCC.
 
         SCC-0) T0 => !T2 => T3 => !T1 => T0
         SCC-1) T1 => !T3 => T2 => !T0 => T1
         SCC-2) !T4 => T5
         SCC-3) !T5 => T4

     - If one SCC is true, there is the other that becomes false.
 
 Finally, solve 2-SAT problem using topological sorting of SCC graph.
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// Adjacency List
vector<vector<int> > adj;
// The component number of each vertex, starting at 0
// Vertexs in the same SCC has the same component number.
vector<int> sccId;
// The discovery order of each vertex
vector<int> discovered;
// Stack to save the number of each vertex
stack<int> st;
int sccCounter, vertexCounter;

// Return the minimum discovery order of the vertex, which it can be reached
// by a back edge or cross edge in a subtree of the root, here.
// (ignore the vertexes already grouped by SCC.)
int scc(int here) { // DFS
    int ret = discovered[here]  = vertexCounter++;
    st.push(here);
    
    for (int i=0; i<adj[here].size(); i++) {
        int there = adj[here][i];
        // (here, there) = tree edge
        if (discovered[there] == -1) {
            ret = min(ret, scc(there));
        } else if (sccId[there] == -1) {
            // In case of the cross edge to `there` that can not be ignored,
            ret = min(ret, discovered[there]);
        }
    }
    
    // If it removes the edges going from here to ancestors,
    if (ret == discovered[here]) {
        // Group the vertexes of here's subtree by one component.
        while (true) {
            int t = st.top();
            st.pop();
            sccId[t] = sccCounter;
            if (t == here) break;
        }
        sccCounter++;
    }
    
    return ret;
}

// Tarjan's Algorithm
// O(|V| + |E|)
vector<int> tarjanSCC() {
    sccId = discovered = vector<int> (adj.size(), -1);
    sccCounter = vertexCounter = 0;
    
    for (int i=0; i<adj.size(); i++) {
        if (discovered[i] == -1)
            scc(i);
    }
    
    return sccId;
}

bool disjoint(const pair<int, int> &a, const pair<int, int> &b) {
    return a.second <= b.first || b.second <= a.first;
}

// Make an implication graph.
// Team i should use one of meetings[2*i] or meetings[2*i+1].
// meetings[i] = the pair, (start, end), of i-th team.
void makeGraph(const vector<pair<int, int> > &meetings) {
    int vars = meetings.size();
    // Graph contains two vertexes for each variable.
    adj.clear();
    adj.resize(vars * 2);
    for (int i=0; i<vars; i+=2) {
        int j = i + 1;
        adj[i * 2 + 1].push_back(j * 2); // ~i => j
        adj[j * 2 + 1].push_back(i * 2); // ~j => i
        adj[i * 2].push_back(j * 2+1); // i => ~j
        adj[j * 2].push_back(i * 2+1); // j => ~i
    }
    
    for (int i=0; i<vars; i++) {
        for (int j=0; j<i; j++) {
            // If duplicated
            if (!disjoint(meetings[i], meetings[j])) {
                // should not hold one of both i-th meeting and j-th meeting.
                adj[i * 2].push_back(j * 2 + 1); // i => ~j
                adj[j * 2].push_back(i * 2 + 1); // j => ~i
            }
        }
    }
}

// O(n^2), where n is the number of meeting rooms.
vector<int> solve2SAT() {
    int n = adj.size(); // the number of variables
    // Group vertexes of the implication graph by SCC.
    vector<int> label = tarjanSCC();
    
    // If two vertexes indicating one variable belong in the same SCC,
    // it is impossible to solve.
    for (int i=0; i<n; i+=2) {
        if (label[i] == label[i+1])
            return vector<int> ();
    }
    
    vector<int> value(n, -1);
    // From tarjan's algorithm, each number of SCCs is assigned
    // in reverse order of topological sorting.
    vector<pair<int, int> > order;
    for (int i=0; i<n; i++)
        order.emplace_back(-label[i], i);
    sort(order.begin(), order.end());
    
    // Assign a value at each vertex.
    for (int i=0; i<n; i++) {
        int vertex = order[i].second;
        int variable = vertex / 2;
        int isTrue = vertex % 2 == 0;
        if (value[variable] != -1) continue;
        // If ~A appears earlier than A, A is true.
        // If A appears earlier than ~A, A is false;
        value[variable] = !isTrue;
    }
    return value;
}

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int> > meetings;
    for (int i=0; i<n; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        meetings.emplace_back(a, b);
        meetings.emplace_back(c, d);
    }
    
    makeGraph(meetings);
    vector<int> ret = solve2SAT();
    if (ret.empty()) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << "POSSIBLE" << endl;
        for (int i=0; i<ret.size(); i++) {
            if (ret[i] == 1) {
                cout << meetings[i].first << " " << meetings[i].second << endl;
            }
        }
    }
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
