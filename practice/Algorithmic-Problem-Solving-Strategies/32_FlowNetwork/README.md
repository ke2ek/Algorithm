# Flow Network

## Basic

- In graph theory, a [flow network](https://en.wikipedia.org/wiki/Flow_network) (also known as a transportation network) is a directed graph where each edge has a **`capacity`** and each edge receives a **`flow`**.
-  The amount of flow on an edge cannot exceed the capacity of the edge.
-  Often in operations research, a directed graph is called a network, the vertices are called nodes and the edges are called arcs.
-  A flow must satisfy the restriction that the amount of flow into a node equals the amount of flow out of it, unless it is a **`source`**, which has only outgoing flow, or **`sink`**, which has only incoming flow.
-  A network can be used to model traffic in a computer network, circulation with demands, fluids in pipes, currents in an electrical circuit, or anything similar in which something travels through a network of nodes.
- The capacity of a path is defined as the minimum of the capacity at edges of the path because a flow must pass the edge with minimum capacity in the path.
  - Thus, most of cases, the flow from a source is divided and sent.
- Network Flow Problem is to `find the maximum amount of flow` to pass from the source to the sink.
- Property
  - **Capacity Constraint**. `flow(u, v) <= capacity(u, v)`, where flow(u, v) is the flow of the edge from _u_ to _v_, and capacity(u, v) is the capacity of the edge.
  - **Skew Symmetry**. `flow(u, v) = -flow(v, u)`, which means the opposite flow has the negative weight.
  - **Conserving**. `sum(flow(u, i)) = 0` when i ∈ V, where V is the set of vertices. It means the amount of flow into the vertex has to be the same as the amount of flow out of the vertex. _But, except a source and a sink._


## [Ford–Fulkerson Algorithm](https://en.wikipedia.org/wiki/Ford–Fulkerson_algorithm)

- It is a `greedy algorithm` that computes the maximum flow in a flow network. 
- It is sometimes called a "method" instead of an "algorithm" as **the approach to finding augmenting paths in a residual graph is not fully specified** or it is specified in several implementations with different running times.
- The idea behind the algorithm is as follows: as long as there is a path from the source (start node) to the sink (end node), with available capacity on all edges in the path, we send flow along one of the paths. Then we find another path, and so on. A path with available capacity is called an `augmenting path`.
- **Residual Capacity**. the difference of the capacity and the flow in an edge. `r(u, v) = c(u, v) - f(u, v)`.
- The maximum flow through an augmenting path is decided as **the minimum of residual capacities in the path.**

    ``` c++
    const int INF = 987654321;
    int V;
    int capacity[MAX_V][MAX_V];
    int flow[MAX_V][MAX_V];

    // Return the total flow after calculating flow[][].
    int networkFlow(int source, int sink) {
        memset(flow, 0, sizeof(flow));
        int toalFlow = 0;
        while (1) {
            // Find augmenting path using BFS.
            vector<int> parent(MAX_V, -1); // opposite vertex
            queue<int> q;
            parent[source] = source;
            q.push(source);
            while (!q.empty() && parent[sink] == -1) {
                int u = q.front();
                q.pop();
                for (int v = 0; v < V; v++) {
                    int residual = capacity[u][v] - flow[u][v];
                    if (residual > 0 && parent[v] == -1) {
                        q.push(v);
                        parent[v] = u;
                    }
                }
            }

            // Exit if there is not any augmenting path.
            if (parent[sink] == -1) break;

            // Decide the flow through the augmenting path.
            int amount = INF;
            for (int node = sink; node != source; node = parent[node]) {
                int residual = capacity[parent[node]][node] - flow[parent[node]][node];
                amount = min(amount, residual);
            }

            // Let flow through the augmenting path.
            for (int node = sink; node != source; node = parent[node]) {
                flow[parent[node]][node] += amount;
                flow[node][parent[node]] -= amount;
            }
            
            totalFlow += amount;
        }

        return totalFlow;
    }
    ```

- Proof of Concept: [Min-cut Max-flow Theorem](https://en.wikipedia.org/wiki/Max-flow_min-cut_theorem).
  - `Cut in Flow Netowrk` is to divide the given graph into two sets in which consist of _S_ that includes the source and _T_ that includes the sink.
  - Usually, the capacity of the _Cut S, T_ is the sum of capacities from _S_ to _T_, and the flow of the _Cut S, T_ is the sum of flows from _S_ to _T_.
  - The maximum amount of flow passing from the source to the sink is equal to the total weight of the edges in a minimum cut.
  - i.e. the smallest total weight of the edges which if removed would disconnect the source from the sink.
  - The capacity and flow of all Cut S, T satisfy the following properties.
    - The flow of a Cut is equal to the total flow from the source to the sink because all flows in network pass out of the source into the sink. The all flows from _T_ to _S_ are calculated with negatives, so several round trips are accumulated only once.
    - The flow of a Cut S, T is equal to or smaller than its capacity because each flow on all the edges is not greater than its own capacity.
  - Min-cut problem is to find a cut with the minimum capacity in the given netowrk.
  - Min-cut problem is closely connected with Max-flow.
    - Assume that there is a Cut S', T' which has its capacity same as its flow. 
    - If there is the cut with capacity smaller  than it of Cut S', T', it contradicts that the flow is not greater than the capacity because it means that its flow is greater than its capacity. 
    - Also, if there are other methods to let flow more, it contradicts as like above because its flow is greater than its capacity. 
    - Therefore, the Cut S', T' is the minimum cut and its flow from the source to the sink becomes the maximum flow.
- Time Complexity: `min(O(|E| * f), O(|V| * |E|^2))`, where f is the maximum flow.


## Maximum Bipartite Matching

- In the mathematical discipline of graph theory, a [matching](https://en.wikipedia.org/wiki/Matching_(graph_theory)) or independent edge set in an undirected graph is `a set of edges without common vertices`. Finding a matching in a bipartite graph can be treated as a network flow problem.
- Generally, solving the matching problem on all graphs is SO MUCH complex.
  - [Edmond's matching algorithm](https://en.wikipedia.org/wiki/Blossom_algorithm)
- However, it is easy to find **the maximum matching** in a bipartite graph using a flow network.
- How to convert a bipartite graph to a flow network
  - Assume that there are two groups, A and B, in the given graph.
  - Put the source in front of A and the sink behind B.
  - Connect edges from the source to each vertex in A, from each vertex in B to the sink.
  - Set all the capacities in the network to 1.
  - After calculating the maximum of total flow, find edges with the actual flow.
- Time Complexity: `O(|V| * |E|)`, where V is the number of vertices and E is the number of edges.
  - In this case, the maximum of total flow can not be greater than the # of vertices.
  
  ``` c++
  int n, m; // Number of vertices (of groups, A and B)
  bool adj[MAX_N][MAX_M]; // adj[i][j] = true if i and j were connected.
  vector<int> aMatch, bMatch; // the opposite vertex from each vertex.
  vector<bool> visited;

  // Return true if there is an augmenting path
  // from the vertex, a, in group A
  // to the unmatching vertices in group B.
  bool dfs(int a) {
      if (visited[a]) return false;
      visited[a] = true;
      for (int b = 0; b < m; b++) {
          if (adj[a][b]) {
              // If b has matching already,
              // find an augmenting path, starting from bMatch[b].
              if (bMatch[b] == -1 || dfs(bMatch[b])) {
                  // Match two vertices.
                  aMatch[a] = b;
                  bMatch[b] = a;
                  return true;
              }
          }
      }
      return false;
  }

  // Return the size of matching after calculating aMatch[] and bMatch[].
  // O (|V| * |E|)
  int bipartiteMatch() {
      aMatch = vector<int> (n, -1);
      bMatch = vector<int> (m, -1);
      int size = 0;
      for (int start = 0; start < n; start++) {
          visited = vector<bool> (n, false);
          // Find an augmenting path from the start using DFS.
          if (dfs(start)) ++size;
      }
      return size;
  }
  ```


## Filling a [grid graph](https://en.wikipedia.org/wiki/Lattice_graph) with some rectangles.

- All grid graphs are bipartite, which is easily verified by the fact that one can color the vertices in a checkerboard fashion.
- Example: fill the given chessboard fully using two-rooms rectangles.
    - All the rooms need to be divided into two sets, `a white room set` and `a black room set.`
    - One room becomes one node and one connection between a white room and a black room becomes one edge in a flow network.
    - To fill fully in the given board, find the maximum matching including all the vertices.
    
    ``` c++
    const int dx[4] = { 1, -1, 0, 0 };
    const int dy[4] = { 0, 0, 1, -1 };
    
    // Return true if (y, x) is in the range.
    bool inRange(int y, int x);

    int H, W; // height and width of a rectangle
    vector<string> board; // chessboard

    bool fillBoard() {
        vector<vector<int> > vertexIds(H, vector<int> (W, -1));
        
        // Count the number of vertices by visiting rooms.
        n = m = 0;
        for (int y = 0; y < H; y++)
            for (int x = 0; x < W; x++)
                if (board[y][x] != '#')
                    vertexIds[y][x] = ((y + x) % 2 == 0) ? n++ : m++;
        
        // Fill adj[][].
        memset(adj, 0, sizeof(adj));
        // Check adjacency rooms.
        for (int y1 = 0; y1 < H; y1++) {
            for (int x1 = 0; x1 < W; x1++) {
                if ((y1 + x1) % 2 == 0 && board[y1][x1] != '#') {
                    for (int k = 0; k < 4; k++) {
                        int y2 = y1 + dy[k];
                        int x2 = x1 + dx[k];
                        // If there is an empty room, connect.
                        if (inRange(y2, x2) && board[y2][x2] != '#')
                            adj[vertexIds[y1][x1]][vertexIds[y2][x2]] = 1;
                    }
                }
            }
        }
        
        // the matching size should be the half of empty rooms.
        return bipartiteMatch() * 2 == (n + m);
    }
    ```
