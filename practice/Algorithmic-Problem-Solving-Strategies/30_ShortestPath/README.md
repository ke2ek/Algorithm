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
