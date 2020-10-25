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
	- Notice that priority queue sorts elements by descending, so it will multiply the length by -1 and insert.

	``` c++
	int V; // the number of vertices
	vector<pair<int, int> > adj[MAX_V]; // adjacency list
	
	vector<int> dijkstra(int src) {
		vector<int> dist(V, INF); // each shortest path from start to others.
		dist[src] = 0;
		priority_queue<pair<int, int> > pq;
		pq.push(make_pair(0, src)); // (length, vertex)
		while (!q.empty()) {
			int cost = -pq.top().first;
			int here = pq.top().second;

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
