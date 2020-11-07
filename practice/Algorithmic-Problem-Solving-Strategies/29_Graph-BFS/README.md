# Breadth-First Search

## Basic

- [Breadth-first search (BFS)](https://en.wikipedia.org/wiki/Breadth-first_search) is an algorithm for traversing or searching tree or graph data structures. It starts at the tree root (or some arbitrary node of a graph, sometimes referred to as a 'search key'[1]), and explores all of the neighbor nodes at the present depth prior to moving on to the nodes at the next depth level.

    ``` c++
    vector<vector<int> > adj; // Adjacency List
    
    vector<int> bfs(int start) {
        vector<bool> discovered(adj.size(), false);
        queue<int> q; // vertices to visit next
        vector<int> order; // visiting order of vertices
        
        discovered[start] = true;
        q.push(start);
        while (!q.empty()) {
            int here = q.front();
            q.pop();
            order.push_back(here);
            // Traversing
            for (int i = 0; i < adj[here].size(); i++) {
                int there = adj[here][i];
                if (!discovered[there]) {
                    q.push(there);
                    discovered[there] = true;
                }
            }
        }
        return order;
    }
    ```

- Notice that `discovered[i]` is different from `visited[i]`.
    - In BFS, each vertex has three status.
        - undiscovered status
        - discovered but not visited status
        - already visited status
    - There are vertices of second status in the Queue.
- Likewise DFS, **BFS Spanning tree** contains edges used to discover new vertices.
- Time complexity depends on the linking structure. 
    - In the adjacency list, O(|V| + |E|)
    - In the adjacency matrix, O(|V| * |V|)
- Unlike DFS, BFS is used only to solve _the shortest path problem_.
    - We can find out the shortest path from start vertex to others using BFS spanning tree.
- PoC of finding out the shortest path
    - Assume that BFS discovered the edge, (u, v), and the vertex, _v_, was inserted in the queue for the first time. Then, the shortest path from start to _v_, `distance[v]`, is equal to `distance[u] + 1`.
    - Proof.
        - `distance[v]` can not be longer than `distance[u] + 1` because the `distance[v]` have to be `distance[u] + 1` by adding the edge, (u, v), to the shortest path from start to _u_.
        - `distance[v]` can not be shorter than `distance[u] + 1` because if the shortest path from start to _v_ were shorter than `distance[u] + 1`, the vertex, _v_, should have been visited before visiting _u_. Thus, the first discovery of it from the edge, (u, v), contradicts our assumption.
    
    ``` c++
    // Calculate BFS Spanning tree and the shortest path.
    // distance[i] = the shortest path from start to i
    // parent[i] = the number of i-th vertex's parent in the spanning tree
    //                in case of root, parent[root] = root.
    void bfs2(int start, vector<int> &distance, vector<int> &parent) {
        distance = vector<int> (adj.size(), -1);
        parent = vector<int> (adj.size(), -1);
        queue<int> q;
        distance[start] = 0;
        parent[start] = start;
        q.push(start);
        while (!q.empty()) {
            int here = q.front();
            q.pop();
            for (int i=0; i<adj[here].size(); i++) {
                int there = adj[here][i];
                if (distance[there] == -1) {
                    q.push(there);
                    distance[there] = distance[here] + 1;
                    parent[there] = here;
                }
            }
        }
    }

    // Calculate the shortest path from v to start.
    vector<int> shortestPath(int v, const vector<int> &parent) {
        vector<int> path(1, v);
        while (parent[v] != v) {
            v = parent[v];
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        // path.length() = the length of the shortest path
        return path;
    }
    ```

## The Shortest Path Strategy

- BFS can not always solve the shortest path problem.
- There are two methods, **Bidirectional Search** and **Iteratively Deepening Search**.
- Example: 15-puzzle
    - One tile is empty.
    - We can move one tile to the east, west, north, and south.
    - It is the puzzle that matches 15 number tiles in the square(=4 x 4) by ascending order.
        - How many movements does it need?
    - Calculate the minimum movements.
    - To solve it,
        - Express each state of the game board(=puzzle) to a vertex. a.k.a **State Space**.
        - The state space has 16! vertices.
        - Connect two vertices when one movement changes from one state to other state.
        - Each vertex has at most 4 neighbors.
    
- **15-puzzle**. Simple solution: BFS
    - The time complexity should be calculated differently because the BFS finishes as soon as the answer is found without exploring the entire state space.
    - In practice, the overall time complexity is proportional to the number of vertices that BFS visits.
    - The most direct influence on the number of vertices that BFS visits is the shortest path, _d_, from the start vertex to the target vertex.
    - Another factor is branching factor, _b_, which indicates how many times vertices increase each time the length of the path longs once.
    - In this case, the number of vertices increase 4 times theoretically because there are at most 4 neighbors.
    - Therefore, this solution is so much slow because its time complexity is O(b^d).

    ``` c++
    // The state of the game board
    class State {
        // Return the list of adjacent states.
        vector<State> getAdjacent() const;
        // Operation to put State in map.
        bool operator < (const State& rhs) const;
        // Operation to compare with the finish state.
        bool operator == (const State& rhs) const;
    };
    
    // Check when visiting
    typedef map<State, int> StateMap;

    // Return the shortest path from start to finish.
    int bfs(State start, State finish) {
        if (start == finish) return 0; // Exception

        // Save the shortest paths to each vertex
        StateMap c;

        // Save visiting states forward.
        queue<State> q;
        q.push(start);
        while (!q.empty()) {
            State here = q.front();
            q.pop();
            int cost = c[here];
            vector<State> adjacent = here.getAdjacent();
            for (int i=0; i<adjacent.size(); i++) {
                if (c.count(adjacent[i]) == 0) {
                    if (adjacent[i] == finish) return cost + 1;
                    c[adjacent[i]] = cost + 1;
                    q.push(adjacent[i]);
                }
            }
        }
        return -1;
    }
    ```
        
- **15-puzzle**. Advanced Solution: [Bidirectional Search](https://en.wikipedia.org/wiki/Bidirectional_search)
    - It runs two simultaneous searches: one forward from the initial state, and one backward from the goal, stopping when the two meet.
    - In 15-puzzle, when d = 20, it costs b^10 + b ^10, whereas BFS takes about b^20.
    - Its time complexity is `O(b^(d/2))`.
    - However, it is not useful in the case of finding easily only one of two directions, or the case that there are a lot of backward directions of each vertex, so the branching factor is so much larger.
    
    ``` c++
    class State; // Same as above.

    // Return the sign of x.
    int sgn(int x) {
        if (!x) return 0;
        return x > 0 ? 1 : -1;
    }

    // Increase abs(x).
    int incr(int x) {
        if (x < 0) return x - 1;
        return x + 1;
    }

    // Return the shortest path from start to finish.
    int bidirectional(State start, State finish) {
        if (start == finish) return 0;
        map<State, int> c;
        queue<State> q;
        // forward direction = positive sign
        // backward direction = negative sign
        q.push(start); c[start] = 1;
        q.push(finish); c[finish] = -1;
        while (!q.empty()) {
            State here = q.front();
            q.pop();
            vector<State> adjacent = here.getAdjacent();
            for (int i=0; i<adjacent.size(); i++) {
                map<State, int>::iterator it = c.find(adjacent[i]);
                if (it == c.end()) {
                    c[adjacent[i]] = incr(c[here]);
                    q.push(adjacent[i]);
                } else if (sgn(it->second) != sgn(c[here])) {
                    // If it meet in the middle of the graph,
                    // except for the duplicated edge and return.
                    return abs(it->second) + abs(c[here]) - 1;
                }
            }
        }
        return -1;
    }
    ```

- **15-puzzle**. Advanced Solution: [Iteratively Deepening Search (IDS)](https://en.wikipedia.org/wiki/Iterative_deepening_depth-first_search)
    - In IDS, a **depth-limited** version of depth-first search is run repeatedly with increasing depth limits until the goal is found.
    - If the number of vertices in a graph increases exponentially, we need to use Depth-First Search because DFS does not have to save the list of vertices to visit so it can save much memory space. 
    - Its time complexity is `O(b^d)`.
    - When the shortest path to target state is _d_ and branching factor is _b_, the number of visits is defined as `(d+1) * b^0 + d * b^1 + (d-1) * b^2 + ... + 2 * b^(d-1) + 1 * b^d`.
    - Desc: The first start vertex (like root) is visited (d + 1) times. And then, there are _b_ vertices and the each vertex is visited d times.
    - Its space complexity is `O(d)`, and it is more efficient than Bidirectional Search.

    ``` c++
    class State;
    int best;
    
    void dfs(State here, const State& finish, int steps) {
        // pruning of branches
        if (steps >= best) return;
        // base case
        if (here == finish) {
            best = steps;
            return;
        }
        vector<State> adjacent = here.getAdjacent();
        for (int i=0; i<adjacent.size(); i++) {
            dfs(adjacent[i], finish, steps + 1);
        }
    }

    int ids(State start, State finish, int growthStep) {
        for (int limit = 4; ; limit += growthSteps) {
            best = limit + 1;
            dfs(start, finish, 0);
            if (best <= limit) return best;
        }
        return -1;
    }
    ```

- How to select the proper search method
    - First, if you want to find out the shortest path in a state space, consider `Breadth-First Search` because BFS is intuitive and has a simple implementation.
        - But, you need to check if there is a depth-limit or much larger memory usage.
    - Second, if the maximum depth for search is fixed and there is little time and memory space for BFS, consider `Bidirectional Search`.
        - In this case, it has to be able to easily move to backward direction.
    - Third, if two types of search use much memory or take a slower time, we need to optimize with `Iterative Deepening Search`.
- Tip. implementation of `State` object
    - `State` object should be able to work several operations efficiently. For example, the equivalent of two states, getting adjacent states of the current state, and so on.
    - `State` object needs to take up smaller memory space. Especially, in the case of Breadth-First Search or Bidirectional Search.
        - Make use of `Bitmask` to save memory!
