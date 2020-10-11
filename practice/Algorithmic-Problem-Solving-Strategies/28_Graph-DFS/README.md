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
- Example: Check the connectivity of two vertexes.
	- After calling `dfs(Source)`, check `visited[Source][Destination]`.
- Example: Count the connected subsets.
	- If a graph consists of several components, where a component means the set of vertexes connected, such as a graph, each component is indicated like s1 = {a, b, f, g}, s2 = {c, d, e, h}.
	- i.e. no one of the elements in the subset(s1) is connected to one of those in the subset(s2).
	- It is solved by counting the number of calling `dfs(i)`.
- Example: Dependency in Graph
	- It is solved by [Topological Sorting](https://en.wikipedia.org/wiki/Topological_sorting)
		- Whenever dfs(i) finishes, save the number of the current vertex.
		- After calling dfsAll(), reverse the order of the saved numbers. It will be the topological-sorted result.
	- It is expressed as a DAG. (no-cycle)
	- [DICTIONARY](./DICTIONARY.cpp)


## [Euler Circuit](https://jlmartin.ku.edu/~jlmartin/courses/math105-F11/Lectures/chapter5-part2.pdf)

- Use every edge of a graph `exactly once`.
- The source vertex is the same as the destination vertex.
- Each vertex in an euler circuit has even edges if the graph is undirected.
	- i.e. if one of vertexes has odd edges, the graph can not have an euler circuit.
- If the graph has two or more components(subsets), a component can be an euler circuit, but not the graph.
- Time complexity = O(|V| * |E|)

	``` c++
	vector<vector<int> > adj; // Adjacency list

	// If there is an undirected graph, return an euler circuit.
	// Get the euler circuit by reversing the returned.
	void getEulerCircuit(int here, vector<int> &circuit) {
		for (int there = 0; there < adj.size(); there++) {
			while (adj[here][there] > 0) {
				adj[here][there]--; // Remove the passed edge.
				adj[there][here]--;
				getEulerCircuit(there, circuit);
			}
		}
		circuit.push_back(here);
	}
	```

- _Euler Path_ starts and ends at different vertexes. Likewise, the path uses every edge of a graph exactly once.
- If you want to find out the euler path, add the edge from destination to source to be able to become the euler circuit, and then call `getEulerCircuit()`.
- In case of the **directed graph**, refer to [WORDCHAIN](./WORDCHAIN.cpp)
	- To be an euler circuit in a directed graph, the number of in-comming edges is the same as the number of out-going edges in each vertex.
	- To be an euler path in a directed graph,
		- Source vertex: the # of in-comming edges + 1 == the # of out-going edges
		- Destination vertex: the # of in-comming edges == the # of out-going edges + 1
		- Other vertex: the # of in-comming edges == the # of out-going edges
	- i.e. if the difference of in-degree and out-degree at any vertex is not -1, 1, or 0, the euler circuit or path can not exist in the graph.


## Kind of Edge

- Be able to find out what structure the graph has by tracking the edges on DFS.
- **DFS Spanning Tree**. the set of edges traced by the search function.
	- For example, if starting at any vetex, the root of this tree becomes the vertex. Also, although there are some edges from the children of the vertex to the vertex, they are not included in the tree.
	- According to starting at which vertex, the shape of the tree is different.
- How to classify an edge in a directed graph.
	- **tree edge**. the edges included in the tree.
	- **forward edge**. the edges, going from ancestors to offspring, excluded in the tree.
		- It means that some two vertexes have several edges.
	- **back edge**. the edges, going from offspring to ancestors, excluded in the tree.
	- **cross edge**. the edges between vertexes that are not related to ancestors and offspring.
- How to classify an edge in an undirected graph.
	- There is only **tree edge** in the graph.
- PoC of Topological Sorting with edges
	- Remind: topological sorting works by reversing the vertexes saved whenever dfs() ends.
	- Assume that if `dfs(u)` ends earlier than `dfs(v)`, the edge, (u, v), can not exist.
		- i.e. `dfs(v)` called `dfs(u)`.
	- Proof.
		- If (u, v) is a tree edge, it means that `dfs(u)` called `dfs(v)`. But `dfs(u)` can not end earlier because it should finish after `dfs(v)` ends.
		- If (u, v) is a forward edge, it means that u is an ancestor of v, so `dfs(u)` can not end earlier because it should finish after `dfs(v)` ends.
		- If (u, v) is a back edge, it means that v is an ancestor of u, so there is (v, u). This contradicts the assumption that the graph is DAG.
		- If (u, v) is a cross edge, it means that u was visited after calling `dfs(v)`, so it contradicts that `dfs(v)` called `dfs(u)` because u should be visited before calling dfs(v).
- How to check the existence or absence of the cycle in a directed graph with edges.
	- The presence of the cycle is consistent with the presence of the back edge.
- Re: How to classify an edge in a directed graph.

	``` c++
	// Adjacency list
	vector<vector<int> > adj;
	// discovered[i] = visiting order of i-th vertex (default = -1)
	vector<int> discovered;
	// finished[i] = 1 if dfs(i) ended. otherwise 0
	vector<int> finished;
	// The number of the discovered vertexes
	int counter;

	void dfs2(int here) {
		discovered[here] = counter++;

		for (int i=0; i<adj[here].size(); i++) {
			int there = adj[here][i];
			cout << "(" << here << ", " << there << ") is a ";

			// If it did not visit there,
			if (discovered[there] == -1) {
				cout << "tree edge" << endl;
				dfs2(there);
			} else if (discovered[here] < discovered[there]) {
				// If there is discovered later than here, there is offspring of here.
				cout << "forward edge" << endl;
			} else if (finished[there] == 0) {
				// If dfs2(there) did not end still, there is an ancestor of here.
				cout << "back edge" << endl;
			} else { // Otherwise
				cout << "cross edge" << endl;
			}
		}
		finished[here] = 1;
	}
	```


## Finding Cut Vertex

- **Cut Vertex** in an undirected graph means the vertexes dividing the graph into two components when they are removed.
- Simple Solution: check the number of components whenever each vertex is removed.
- Advanced Solution: using DFS spanning tree.
	- Assume that the vertex, _u_, has several offspring. Then, if all of them have back edges to _u_, _u_ is not a cut vertex.
	- In this case, _u_ should have two or more offspring.
	
	``` c++
	// Adjacency list
	vector<vector<int> > adj;
	// discovered[i] = visiting order of i-th vertex (default = -1)
	vector<int> discovered;
	// isCutVertex[i] = true if it is a cut vertex, otherwise false (=default)
	vector<bool> isCutVertex;
	int counter = 0;
	
	// Find out the cut vertex of subtrees of here.
	// isRoot=true when calling first.
	// Return the discovery order of the earliest found vertex
	// in the subtree that can be reached by the back edge.
	int findCutVertex(int here, bool isRoot) {
		discovered[here] = counter++;
		int ret = discovered[here];

		// If it is the root, count the number of subtrees.
		int children = 0;
		for (int i=0; i<adj[here].size(); i++) {
			int there = adj[here][i];
			if (discovered[there] == -1) {
				children++;
				// Get the number of the highest vertex in a subtree.
				int subtree = findCutVertex(there, false);
				// here is a cut vertex if the highest vertex of its subtree is lower than here.
				if (!isRoot && subtree >= discovered[here])
					isCutVertex[here] = true;
				ret = min(ret, subtree);
			} else {
				ret	= min(ret, discovered[there])
			}
		}
		
		if (isRoot) isCutVertex[here] = (children >=  2);
		return ret;
	}
	```


## Finding the Bridge

- Bridge is the edge dividing the graph into two or more components when the edge is removed.
- It is a tree edge.
- Assume that the vertex, _u_, has some subtrees and the vertex, _v_, is the offspring of _u_.
	- If the edge, (u, v), is the bridge of the graph, there should not be a back edge from _v_ to _u_. 
- Check if there is _u_ in ancestors of _v_.
	- What is the minimum discovery order of where we can reach by the back edges of _v_?


## Separate [Strongly Connected Components](https://en.wikipedia.org/wiki/Strongly_connected_component)

- In a directed graph, two vertexes are included in SCC if they have bi-directed edges.
- DAG is made by gathering edges connecting to each SCC.
- **condensation**. group the vertexes of the original graph by SCC, and create a new graph containing SCCs as vertexes.
- Vertexes included in the same cycle belong to the same SCC.
- For example, if a graph representing the city's road network of one-way roads is divided into two or more SCCs, it means that there are times when you cannot go from one point to another.
- [Tarjan's SCC algorithm](https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm)
	- 
