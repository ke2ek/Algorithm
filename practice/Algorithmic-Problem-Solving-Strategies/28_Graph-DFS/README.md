# Depth-First Search

## Basic

- [Depth-first search (DFS)](https://en.wikipedia.org/wiki/Depth-first_search) is an algorithm for traversing or searching tree or graph data structures. The algorithm starts at the root node (selecting some arbitrary node as the root node in the case of a graph) and explores as far as possible along each branch before backtracking.

	``` c++
	vector<vector<int> > adj; // Adjacency List
	vector<bool> visited;

	void dfs(int here) {
		cout << "DFS visits " << here << endl;
		visited[here] = true;
		// Traversing 
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i];
			if (!visited[there])
				dfs(there);
		}
	}

	void dfsAll() {
		visited = vector<bool> (adj.size(), false);
		for (int i = 0; i < adj.size(); i++)
			if (!visited[i])
				dfs(i);
	}

	// Notice that we need to call dfsAll() if it is not guaranteed that all vertex is connected.
	```

- Time complexity depends on the linking structure. 
	- In the adjacency list, O(|V| + |E|)
	- In the adjacency matrix, O(|V| * |V|)


## Example

- Check the connectivity of two vertexes.
	- After calling `dfs(Source)`, check `visited[Source][Destination]`.
- Count the connected subsets.
	- If a graph consists of several components, where a component means the set of vertexes connected, such as a graph, each component is indicated like s1 = {a, b, f, g}, s2 = {c, d, e, h}.
	- i.e. no one of the elements in the subset(s1) is connected to one of those in the subset(s2).
	- It is solved by counting the number of calling `dfs(i)`.
- Dependency in Graph
	- It is solved by [Topological Sorting](https://en.wikipedia.org/wiki/Topological_sorting)
		- Whenever dfs(i) finishes, save the number of the current vertex.
		- After calling dfsAll(), reverse the order of the saved numbers. It will be the topological-sorted result.
	- It is expressed as a DAG. (no-cycle)
