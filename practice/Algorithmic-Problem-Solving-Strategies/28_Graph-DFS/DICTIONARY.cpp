// https://algospot.com/judge/problem/read/DICTIONARY
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#define ALPHABETS 26
using namespace std;

vector<vector<int> > graph(ALPHABETS);
vector<int> visited;
vector<int> order;

void dfs(int here) {
    visited[here] = 1;
    for (int there=0; there<graph.size(); there++) {
        if (!visited[there] && graph[here][there]) {
            dfs(there);
        }
    }
    order.push_back(here);
}

vector<int> topologicalSort() {
    int m = graph.size();
    visited = vector<int>(m, 0);
    order.clear();
    
    for (int i=0; i<m; i++) {
        if (!visited[i])
            dfs(i);
    }
    reverse(order.begin(), order.end());
    for (int i=0; i<m; i++) {
        for (int j=i+1; j<m; j++) {
            if (graph[order[j]][order[i]]) {
                return vector<int>();
            }
        }
    }
    return order;
}


// 주어진 단어들로부터 알파벳간의 선후관계 그래프 생성
void makeGraph(const vector<string>& words) {
    graph = vector<vector<int> > (ALPHABETS, vector<int> (ALPHABETS, false));
    for (int j = 1; j < words.size(); ++j) {
        int i = j - 1, len = min(words[i].size(), words[j].size());
        
        // word[i]가 word[j] 앞에 오는 이유를 찾음
        for (int k = 0; k < len; ++k) {
            if (words[i][k] != words[j][k]) {
                int a = words[i][k] - 'a';
                int b = words[j][k] - 'a';
                
                graph[a][b] = true;
                break;
            }
        }
    }
}

void solve() {
    int n;
    cin >> n;
    vector<string> words(n);
    for (auto& w : words)
        cin >> w;
    makeGraph(words);
    auto orders = topologicalSort();
    if (orders.empty()) {
        cout << "INVALID HYPOTHESIS\n";
    }
    else {
        for (auto& o : orders)
            cout << static_cast<char>(o + 'a');
        cout << '\n';
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
