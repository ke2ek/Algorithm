# Breadth-First Search

## Basic

- [Breadth-first search (BFS)](https://en.wikipedia.org/wiki/Breadth-first_search) is an algorithm for traversing or searching tree or graph data structures. It starts at the tree root (or some arbitrary node of a graph, sometimes referred to as a 'search key'[1]), and explores all of the neighbor nodes at the present depth prior to moving on to the nodes at the next depth level.

	``` c++
	vector<vector<int> > adj; // Adjacency List
	
	vector<int> bfs(int start) {
		vector<bool> discovered(adj.size(), false);
		queue<int> q; // vertexes to visit next
		vector<int> order; // visiting order of vertexes
		
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
	- There are vertexes of second status in the Queue.
- Likewise DFS, **BFS Spanning tree** contains edges used to discover new vertexes.
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
	//				in case of root, parent[root] = root.
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
