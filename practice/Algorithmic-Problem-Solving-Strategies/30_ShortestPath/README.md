# Shortest Path Algorithm

## Basic

- [Shortest Path Problem](https://en.wikipedia.org/wiki/Shortest_path_problem) is to find out the length of the shortest path connecting given two vertices in a graph.
- In the case of the graph in which there is not weight, it is possible to discover using BFS.
- What is dealing with in here is some algorithm about the graph with `nonnegative weights`
- Notice that the shortest path algorithm provides not the list of vertices on the path but just `the length of the path`.
    - If you want to know which vertices in the path, we should add some pieces of the code for saving other information like vertices or edges while searching.
- **Importance of negative edges**
    - If there is a graph with negative weights, the length of the path after passing the edges must have gotten short. 
    - Also, if the graph contains the cycle consisting of negative edges, the length can diverge to the infinity of negative.
    - Thus, the shortest path problem does not define certainly in this case. It is just able to check the negative cycle.
- **Single-source shortest paths**.
    - Likewise BFS, this algorithm finds all the shortest path from the start to each vertex.
- **All-pairs shortest paths**.
    - This algorithm finds the shortest paths between every pair of vertices.
    - The result is the matrix of V by V, where V is the number of vertices.
    - Each element indicates the length of shortest path between two vertices.
- **Directed vs Undirected**
    - In this case, only directed graph is handled.
    - If you want to solve the problem of undirected graphs with these algorithms, you should divide the graph into two directed graphs that have one-directed edges.
    - Exception: undirected graphs with negative weights.


## [Dijkstra's Algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)

- For a given source node in the graph, the algorithm finds the shortest path between that node and every other.
- It inserts the pair, the number of each vertex and the shortest length, to the **priority queue**.
- Notice
    - The priority queue sorts elements by descending, so it will multiply the length by -1 and insert.
    - Unlike BFS, it **visits the close vertices first** not neighbors.

    ``` c++
    int V; // the number of vertices
    vector<pair<int, int> > adj[MAX_V]; // adjacency list
    
    vector<int> dijkstra(int src) {
        vector<int> dist(V, INF); // each shortest path from start to others.
        dist[src] = 0;
        priority_queue<pair<int, int> > pq;
        pq.push(make_pair(0, src)); // (length, vertex)
        while (!pq.empty()) {
            int cost = -pq.top().first;
            int here = pq.top().second;
            pq.pop();

            // Ignore the already passed vertex.
            if (dist[here] < cost) continue;

            // Visit all neighbors.
            for (int i=0; i<adj[here].size(); i++) {
                int there = adj[here][i];
                int nextDist = cost + adj[here][i].second;
                // If it finds shorter path,
                if (dist[there] > nextDist) {
                    dist[there] = nextDist;
                    pq.push(make_pair(-nextDist, there));
                }
            }
        }
        return dist;
    }
    ```

- Proof by contradiction: Assume that there is the vertex, _u_, in which does not solve the shortest path problem. Or, if there are two or more vertices like that, select the first visiting vertex.
    - We know that the vertex, _u_, is not the start because we always calculate the shortest path on the start vertex.
    - At the moment this algorithm visits _u_, we need to look at the graph into two ways: vertices that have already been visited and not.
    - The meaning of calculating wrongly the shortest path on _u_, is that there is the shorter path than that in our spanning tree.
    - If there is the vertex, _p_, in the shorter path from the start to _u_ and the vertex, _q_, in another path from the start to _u_ via _p_, the length of the shortest path from the start to _q_ is `dist[p] + w(p, q)`, where w(p, q) is the weight between _p_ and _q_.
    - At that time, since _p_ has already been visited, the shortest path to _q_, `dist[q]` would have been calculated, and _q_ would have been inserted to the priority queue. That way, priority queue would have included two vertices, _u_ and _q_.
    - Back to the assumption, the meaning that _u_ popped from the queue earlier than _q_ is that the path from the start to _u_ is shorter than the path from the start to _q_, such as `dist[u] <= dist[q]`. By the way, it contradicts that the path from the start to _u_ via _q_ is shorter than `dist[u]`.
    - Therefore, there can not be the shorter path than the spanning tree.
    - Exception: the graph with negative weights
- Time Complexity: `O(|E| * lg(|V|))`
    - The number of vertices added in the queue is at most O(|E|).
        - Notice that it is able to add each vertex two or more times.
    - It costs O(lg|E|) to add and remove an element in the queue.
    - Generally, the number of edges in a graph is smaller than |V| * |V|, so we can know that O(lg(|E|)) = O(lg(|V|)).
        - O(lg(|V| * |V|)) = O(2 * lg(|V|)) = O(lg(|V|))
- Another Implementation without priority_queue
    - Time Complexity: `O(|V| * |V| + |E|)`
    
    ``` C++
    vector<int> dijkstra2(int src) {
        vector<int> dist(V, INF);
        vector<bool> visited(V, false);
        dist[src] = 0;
        visited[src] = false;
        while (true) {
            int closest = INF, here;

            // Discover close vertices among
            // vertices that have already been visited.
            for (int i=0; i<V; i++) {
                if (dist[i] < closest && !visited[i]) {
                    here = i;
                    closest = dist[i];
                }
            }

            if (closest == INF) break;

            // Visit the closest vertex.
            visited[here] = true;
            for (int i=0; i<adj[here].size(); i++) {
                int there = adj[here][i].first;
                if (visited[there]) continue;
                int nextDist = dist[here] + adj[here][i].second;
                dist[there] = min(dist[there], nextDist);
            }
        }
        return dist;
    }
    ```

- Test Case

    ``` text
    First lines are V, M, where V is the number of vertices
    and M is the number of the edges.
    Next lines are source, destination vertex, and cost.
    
        7 9
        A B 5
        A C 1
        C D 2
        D B 1
        D E 5
        B G 3
        B F 3
        G F 2
        D F 3

    Visiting order in dijkstra('A'):
        A -> C -> D -> B -> B -> F -> G -> E

        Starting at A:
        To A, length = 0
        To B, length = 4
        To C, length = 1
        To D, length = 3
        To E, length = 8
        To F, length = 6
        To G, length = 7
    ```


## [Bellman-Ford Algorithm](https://en.wikipedia.org/wiki/Bellman–Ford_algorithm)

- This algorithm computes shortest paths from a single source vertex to all of the other vertices in a weighted digraph like Dijkstra's algorithm.
- It is slower than Dijkstra's algorithm for the same problem, but more versatile, as it is capable of handling graphs in which `some of the edge weights are negative numbers`.
- Also, we can know if the graph has cycles with negative weights.
- It decreases error repeatedly that is difference of the upper bound of the shortest path and the the actual length whenever it predicts the proper upper bound.
    - Finally, the array `upper[]` contains each length of the actual shortest path.
- How to work
    - Initialize `upper[s] = 0`, where _s_ is the start vertex, and `upper[v] = INF`, where _v_ is vertices other than _s_ in the graph. 
    - Approximate the path to the shortest path by relaxing along the edge (u, v), where _u_ and _v_ are the source vertex and the destination vertex.
        - **Relaxing** means that it updates upper[v]  if `upper[v] <= upper[u] + w(u, v)`.
        - Since the shortest path of _u_ and _v_, dist[u] and dist[v], satisfy the rule, `dist[v] <= dist[u] + w(u, v)`, finding the shortest path in weighted-graphp without cycles succeeds all the time regardless of negative-weights.
    - Repeat relaxing from every edges at most `V - 1` times, where V is the number of vertices.
    - If you just want to check the presence of cycle, you need to repeat relaxing V times at most.
        - If relaxing at V-th iterating fails, it means that the graph includes the cycle with negative weights.
        - Because the cycle with negative weights always contains the shortest path whenever it is relaxing.
    
    ``` c++
    int V;
    vector<pair<int, int> > adj[MAX_V];

    vector<int> bellmanFord(int src) {
        vector<int> upper(V, INF);
        upper[src] = 0;
        bool isRelaxing;
        // Visit v times.
        for (int iter = 0; iter < V; iter++) {
            isRelaxing = false;
            for (int here=0; here < V; here++) {
                for (int i = 0; i < adj[here].size(); i++) {
                    int there = adj[here][i].first;
                    int cost = adj[here][i].second;
                    if (upper[there] > upper[here] + cost) {
                        upper[there] = upper[here] + cost;
                        isRelaxing = true;
                    }
                }
            }
            // If it failed at every edges, we don't need to iterate V - 1 times.
            if (!isRelaxing) break;
        }

        // If it is relaxing at V-th iterating, return empty vector because of the cycle.
        if (isRelaxing) upper.clear();
        return upper;
    }
    ```

- Time Complexity: `O(|V|*|E|)`, where V is the # of vertices and E is the # of edges.
- Example: [TIMETRIP](./TIMETRIP.cpp)


## [Floyd-Warshall Algorithm](https://en.wikipedia.org/wiki/Floyd–Warshall_algorithm)

- It finds shortest paths in a weighted graph with positive or negative edge weights (but with no negative cycles).
- A single execution of the algorithm will find the lengths (summed weights) of shortest paths between **all pairs of vertices**.
- Although it does not return details of the paths themselves, it is possible to reconstruct the paths with simple modifications to the algorithm.
- Assume that `Ds(u, v)` is the shortest path from _u_ to _v_ via vertices of the set, _S_.
    - If the path does not pass the vertex, _x_, the path can be defined as `Ds-x`.
    - `Ds(u, v) = min(Ds-x(u, x) + Ds-x(x, v), Ds-x(u, v))`
    - **Ds-x(u, x) + Ds-x(x, v)** means that it passes the vertex _x_ that is included in the set, _S_.
    - Every edges in the shortest path should satisfy above expression.
- Simple Implementation with Dynamic Programming
    - Time/Space complexity: O(|V|^3).

    ``` c++
    // the number of the vertices
    int V;
    // adjacency list
    int adj[MAX_V][MAX_V];
    // C[k][u][v] = the length of the shortest path from u to v
    //              via 0-th ~ k-th vertices in the given set, S.
    int C[MAX_V][MAX_V][MAX_V];  
    void allPairShortestPath1() {
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (i != j)
                    C[0][i][j] = min(adj[i][j], adj[i][0] + adj[0][j]);
                else
                    C[0][i][j] = 0;

        for (int k = 0; k < V; k++)
            for (int u = 0; u < V; u++)
                for (int v = 0; v < V; v++)
                    C[k][u][v] = min(C[k-1][u][v], C[k-1][u][k] + C[k-1][k][v]);
    }
    // Notice that, in adjacency list, it need to set the largest value if there is not an edge.
    ```

- Advanced Implementation with Sliding Window in DP
    - It saves memory capacity much by using the (k-1)-th array only, C[k-1].
        - Just like C[k % 2] !! But we do not even need it.
    - Space complexity: O(|V|^2)

    ``` c++
    int V;
    int adj[MAX_V][MAX_V]; // adjacency list
    void floyd() {
        for (int i = 0; i < V; i++) adj[i][i] = 0;
        for (int k = 0; k < V; k++)
            for (int u = 0; u < V; u++)
                for (int v = 0; v < V; v++)
                    adj[u][v] = min(adj[u][v], adj[u][k] + adj[k][v]);
    }

    void optimizedFloyd() {
        for (int i = 0; i < V; i++) adj[i][i] = 0;
        for (int k = 0; k < V; k++) {
            for (int u = 0; u < V; u++) {
                if (adj[u][k] == INF) continue; // Save execution time about 20%.
                for (int v = 0; v < V; v++)
                    adj[u][v] = min(adj[u][v], adj[u][k] + adj[k][v]);
            }
        }
    }
    ```

- How to get the vertices in the shortest path.

    ``` c++
    int V;
    int adj[MAX_V][MAX_V];
    int via[MAX_V][MAX_V];

    void floyd2() {
        for (int i = 0; i < V; i++) adj[i][i] = 0;
        memset(via, -1, sizeof(via));
        for (int k = 0; k < V; k++) {
            for (int u = 0; u < V; u++) {
                if (adj[u][k] == INF) continue; // Save execution time about 20%.
                for (int v = 0; v < V; v++) {
                    int cost = adj[u][k] + adj[k][v];
                    if (adj[u][v] > cost) {
                        via[u][v] = k;
                        adj[u][v] = cost;
                    }
                }
            }
        }
    }

    // Calculate the shortest path from u to v.
    void reconstruct(int u, int v, vector<int>& path) {
        if (via[u][v] == -1) {
            path.push_back(u);
            if (u != v) path.push_back(v);
        } else {
            int k = via[u][v];
            reconstruct(u, k, path);
            path.pop_back(); // Protect duplicate of k
            reconstruct(k, v, path);
        }
    }
    ```

