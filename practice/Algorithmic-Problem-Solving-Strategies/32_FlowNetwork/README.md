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
