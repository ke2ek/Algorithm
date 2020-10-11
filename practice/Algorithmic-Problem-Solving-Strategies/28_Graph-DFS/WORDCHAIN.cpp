// https://algospot.com/judge/problem/read/WORDCHAIN
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define toIdx(x) x - 'a'
#define ALPHABETS 26
using namespace std;

int n;
// adj[i][j] = the number of edges from i to j.
vector<vector<int> > adj;
// graph[i][j] = the list of words starting from i and ending to j.
vector<string> graph[ALPHABETS][ALPHABETS];
// indegree[i] = the number of words starting from i.
vector<int> indegree;
// outdegree[i] = the number of words ends to j.
vector<int> outdegree;


void makeGraph(const vector<string> &words) {
    // Initialize.
    for (int i=0; i<ALPHABETS; i++)
        for (int j=0; j<ALPHABETS; j++)
            graph[i][j].clear();
    
    adj = vector<vector<int> > (ALPHABETS, vector<int> (ALPHABETS, 0));
    indegree = outdegree = vector<int> (ALPHABETS, 0);
    
    // Make graph.
    // Notice that we should add the edge, (b, a), to find the euler path beginning at a and finishing at b.
    for (int i=0; i<words.size(); i++) {
        int a = toIdx(words[i][0]);
        int b = toIdx(words[i][words[i].size()-1]);
        graph[a][b].push_back(words[i]);
        adj[a][b]++;
        outdegree[a]++;
        indegree[b]++;
    }
}

void getEulerCircuit(int here, vector<int> &circuit) {
    for (int there=0; there<adj.size(); there++) {
        while(adj[here][there] > 0) {
            // This is a directed graph, so remove one direction.
            adj[here][there]--;
            getEulerCircuit(there, circuit);
        }
    }
    circuit.push_back(here);
}

vector<int> getEulerPathOrCircuit() {
    vector<int> circuit;
    
    // In case of existing the start,
    for (int i=0; i<ALPHABETS; i++) {
        if (outdegree[i] == indegree[i]+1) {
            getEulerCircuit(i, circuit);
            return circuit;
        }
    }
    
    // In case of having a cycle (=euler circuit),
    for (int i=0; i<ALPHABETS; i++) {
        // Just start at any vertex.
        if (outdegree[i]) {
            getEulerCircuit(i, circuit);
            return circuit;
        }
    }
    
    // If failed,
    return circuit;
}

// Verify if it has the euler circuit or path.
bool checkEuler() {
    int plus1 = 0; // The number of candidate start points.
    int minus1 = 0; // The number of candidate end points.
    for (int i=0; i<ALPHABETS; i++) {
        int delta = outdegree[i] - indegree[i];
        // The degree of all vertics should be -1, 1, or 0.
        if (delta < -1 || 1 < delta) return false;
        if (delta == 1) plus1++;
        if (delta == -1) minus1++;
    }
    
    // Start and end point should be only each one and should not be.
    return (plus1 == 1 && minus1 == 1) || (plus1 == 0 && minus1 == 0);
}

// O(n * A), where n is the number of words and A is the number of alphabets(=26)
// time-complexity is dominated by getEulerCircuit()
void solve() {
    cin >> n;
    vector<string> words(n);
    for (int i=0; i<n; i++) cin >> words[i];
    makeGraph(words);
    
    if (!checkEuler()) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        vector<int> circuit = getEulerPathOrCircuit();
        // If it can not visit all the edges, the graph has two more components.
        if (circuit.size() != words.size() + 1) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            reverse(circuit.begin(), circuit.end());
            for (int i=1; i<circuit.size(); i++) {
                int a = circuit[i-1], b = circuit[i];
                if (i > 1) cout << " ";
                cout << graph[a][b].back();
                graph[a][b].pop_back();
            }
            cout << endl;
        }
    }
}

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        solve();
    }
    return 0;
}
