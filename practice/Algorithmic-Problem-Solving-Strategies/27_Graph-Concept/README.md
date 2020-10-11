# What is Graph

## Intro

- Graph describes the connection between material things or abstract concepts in the real world.
- For example, network connecting cities, relationships, link connections of websites, and so on.
- The difference with the tree is that the graph does not have the limitation about connection such as parent-children. So, the graph is used more comprehensively than the tree.


## Definition

- **Vertex**. a component of the graph a.k.a Node.
- **Edge**. connect to each node.
- Notice that edges' order and vertexes' location are not important in graph. It means that although the same linking structure has different shape, they are the same graph.
- **Kind of**.
	- `Directed Graph` the end of edge has an arrow, which means that it is not possible to move to the opposite of an arrow.
	- `Undirected Graph` it does not have arrows.
	- `Weighted Graph` each edge includes weight, which means that it needs to cost as the weight when moving.
	- `Multi Graph` there are two or more edges between two vertexes.
	- `Simple Graph` there is only one edge between two vetexs.
	- `Bipartite Graph` there are edges in the vetexs belonging to each other group, where a group doest not have vertexes connected to each other.
	- `Directed Ascyclic Graph (DAG)` there is not a path that starts at one point and returns to itself. (directed and no-cycle)
- Some graph include two or more property. i.e. Directed Weighted Graph, DAG, etc
- **Path**. the set of edges.
	- Usually, we describe an as numbers of connected two vertexes, such as (1, 3).
	- So, we express the path as `path = { (1, 2), (2, 3), (3, 4), (4, 5) }`
		- If the # of vertexes is 5, all vertexes are connected! :)
		- 1 -> 2 -> 3 -> 4 -> 5
	- Generally, `simple path` means that each vertex is passed only one time.

	
## Notation

- **Adjacency List**. indicates as an 2D array, in which the index means the number of each source vertex and each array of the index contains the number of each destination vertex.
	- It can save the capacity in memory. However, it takes more time when finding out the connectivity of two vertexes.
	- Capacity in memory = |V| * |E|, where V is the number of vertexes and E is the number of edges.

	
	``` c++
	vector<list<int> > adjacent;
	// or
	vector<vector<int> > adjacent;
	```

	- If a graph has a few additional property like weight, express a structure.
	
	``` c++
	struct Edge {
		int vertex; // Number of the destination vertex.
		int weight; // weight
	};

	vector<list<Edge> > adjacent;
	```

- **Adjacency Matrix**. also indicates as an 2D array, but it has all connection information about all the vertexes. In this matrix, each element means the connection status between two vertexes.
	- It can save the operation time. However, it spends more space in memory.
	- Capacity in memory = |V| * |V|, where V is the number of vertexes.
	
	``` c++
	vector<vector<bool> > adjacent;

	// If vertex i, j are connected, adjacent[i][j] = true and O(1).
	// In weighted-graph, each element means the weight.
	// Or, it may be -1 if two vertex are not connected.
	```

- Notice that the space capacity of two methods is the same if |E| is equal to |V|.
- We call the graph `Sparse Graph` if the number of edges, |E|, is much smaller than the number of vertexes, |V|.
	- Opposite meaning: `Dense Graph`
- Tip.
	- Sparse Graph -> Adjacency List
	- Dense Graph -> Adjacency Matrix
