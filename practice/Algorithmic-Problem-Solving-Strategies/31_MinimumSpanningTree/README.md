# Minimum Spanning Tree

## Basic

- [Spanning Tree](https://en.wikipedia.org/wiki/Spanning_tree) of an undirected graph G is a subgraph that is a tree which includes all of the vertices of G, with a minimum possible number of edges.
    - There can be several spanning trees in a graph.
    - Spanning Tree does not have any cycle.
    - # of edges in a spanning tree is (# of vertices - 1).
- [Minimum Spanning Tree, MST](https://en.wikipedia.org/wiki/Minimum_spanning_tree), is a spanning tree whose sum of edge weights is as small as possible.
    - MST problem is finding the most inexpensive graph in an edge-weighted undirected graph.


## [Kruskal's algorithm](https://en.wikipedia.org/wiki/Kruskal%27s_algorithm)

- It is a `greedy algorithm` in graph theory as in each step it **adds the next lowest-weight edge** that will not form a cycle to the minimum Spanning Tree.
    - First, sort every edges by weight ascending.
    - Second, add sorted edges one by one to the current MST, where an edge to be added should not form any cycle.
    - Third, keep adding edges until there are all vertices in the MST. 
- How to know if a new edge forms a cycle.
    - [Disjoint Set](https://en.wikipedia.org/wiki/Disjoint-set_data_structure)
    - If two vertices of an edge to be added are already included in the same set, abandon the edge.
    - But, if two vertices are included in each different set, merge two sets.
- Time Complexity: `O(|E| * lg(|E|))`, where E is the number of edges in the given graph.

    ``` c++
    struct DisjointSet {
        vector<int> parent, rank;

        DisjointSet(int n) : parent(n), rank(n, 1) {
            for (int i = 0; i < n; i++)
                parent[i] = i;
        }

        int find(int u) {
            if (parent[u] == u) return u;
            return parent[u] = find(parent[u]); // except duplicate operation
        }

        void merge(int u, int v) {
            u = find(u);
            v = find(v);
            if (u == v) return;
            if (rank[u] > rank[v]) swap(u, v);
            // always rank[u] <= rank[v], where rank means the height of each tree.
            parent[u] = v;
            if (rank[u] == rank[v]) rank[v]++;
        }
    };

    // the number of vertices
    int V;
    // adj[i] = (connected vertex number, edge weight))
    vector<pair<int, int> > adj[MAX_V];
    const int MAX_V = 100;

    // Insert edges of the MST to `selected`.
    // Return the sum of weights in the MST.
    int kruskal(vector<pair<int, int> >& selected) {
        int ret = 0;
        selected.clear();
        // First, sort every edges by weight ascending.
        vector<pair<int, pair<int, int> > > edges;
        for (int u = 0; u < V; u++) {
            for (int i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i].first, cost = adj[u][i].second;
                edges.push_back(make_pair(cost, make_pair(u, v)));
            }
        }
        sort(edges.begin(), edges.end());
        // Calculate MST.
        DisjointSet sets(V);
        for (int i = 0; i < edges.size(); i++) {
            int cost = edges[i].first;
            int u = edges[i].second.first;
            int v = edges[i].second.second;
            // If two vertices are in the same set, ignore.
            if (sets.find(u) == sets.find(v))
                continue;
            // If two vertices are in different set, merge.
            sets.merge(u, v);
            selected.push_back(make_pair(u, v));
            ret += cost;
        }
        return ret;
    }
    ```

## [Prim's algorithm](https://en.wikipedia.org/wiki/Prim%27s_algorithm)

- It operates by building this tree one vertex at a time, from an arbitrary starting vertex, at each step **adding the cheapest possible connection** from the tree to another vertex. 
- Likewise, it is a `greedy algorithm` that finds a minimum spanning tree for a weighted undirected graph.
- How to choose the vertex that will be added next.
    - `minWeight[]` saves the minimum weights of edges connecting the current MST with other vertices.
    - It updates `minWeight[]` by visiting the adjacency edges from a new vertex whenever it adds the vertex to the MST.
- Time Complexity: `O(|V|^2 + |E|)`

    ``` c++
    const int MAX_V = 100;
    const int INF = 987654321;
    
    // the number of vertices
    int V;
    // adj[i] = (connected vertex number, edge weight)
    vector<pair<int, int> > adj[MAX_V];

    // Insert edges of the MST to `selected`.
    // Return the sum of weights in the MST.
    int prim(vector<pair<int, int> >& selected) {
        selected.clear();
        // added[i] = true if i-th vertex is added.
        vector<bool> added(V, false);
        // minWeight[i] = the minimum weight among adjacency edges of i-th vertex.
        vector<int> minWeight(V, INF);
        // parent[i] = the opposite vertex of the edge matching minWeight[i].
        vector<int> parent(V, -1);
        // the sum of weights
        int ret = 0;
        // Add 0-th vertex.
        minWeight[0] = parent[0] = 0;
        for (int iter = 0; iter < V; iter++) {
            // Find the next vertex which should not be included in the current MST.
            int next = -1;
            for (int v = 0; v < V; v++)
                if (!added[v] && (next == -1 || minWeight[next] > minWeight[v]))
                    next = v;
            // Add (parent[next], next) to the MST if the edge is not included.
            if (parent[next] != next)
                selected.push_back(make_pair(parent[next], next));
            ret += minWeight[next];
            added[next] = true;
            // Update minWeight and visit adjacency edges of next.
            for (int i = 0; i < adj[next].size(); i++) {
                int v = adj[next][i].first;
                int weight = adj[next][i].second;
                // Choose the edge with the minimum weight.
                if (!added[v] && minWeight[v] > weight) {
                    parent[v] = next;
                    minWeight[v] = weight;
                }
            }
        }
        return ret;
    }
    ```

