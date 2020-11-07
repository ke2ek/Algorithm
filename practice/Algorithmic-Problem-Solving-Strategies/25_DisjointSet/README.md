# Disjoint Set

## Union-Find

- Union-Find is a data structure to handle mutual exclusive subsets that does not have common elements.
- Operation
    - **initialize**. Each element put into each subset. i.e. subset[i] = i
    - **union**. Combine each subset that A and B belong to, where A and B are elements.
    - **find**. Return the subset the specific element belongs to.

## Representation

- As an array
    - `belongsTo[i] = the number of set that i-th element belongs to`
    - find() operation can work in constant time.
    - But, notice that union() spend O(n) to visit all elements, where n is the number of elements.
    - We want to how to union fast rather than previous even though it might spend more time to find.
- As a tree
    - A tree contains elements including the same set.
    - i.e. each tree means a different set with each other.
    - We would look at whether two elements are included in the same set or not as comparing each root node of both trees the elements belong to.
        - for this, each node of a tree needs to have a pointer to its own parent,
        - whereas it doesn't have to contain pointers to its children.

    ``` c++
    struct NaiveDisjointSet {
        vector<int> parent; // Numbers of parent element.

        NaiveDisjointSet(int n): parent(n) {
            for (int i=0; i<n; i++) {
                parent[i] = i;
            }
        }

        // O(h), where h is the height of a tree.
        // return the number of root node in the tree `u` belongs to.
        int find(int u) const {
            if (u == parent[u]) return u;
            return find(parent[u]);
        }

        // union the tree `u` belongs to and the tree `v` belongs to.
        void merge(int u, int v) {
            u = find(u);
            v = find(v);
            if (u == v) return; // in case the same tree
            parent[u] = v;
        }
    };
    ```

- Optimization in a tree
    - Change each parent of the visited nodes to root node.
        - because find() always returns # of root node of the tree that the given element belongs to.
    - Pay attention to be an un-biased tree in one direction.
        - to solve it, merge the tree of the lower height as a subtree of the higher tree.
    
    ``` c++
    struct OptimizedDisjointSet {
        vector<int> parent, rank;
        
        OptimizedDisjointSet(int n): parent(n), rank(n, 1) {
            for (int i=0; i<n; i++) {
                parent[i] = i;
            }
        }

        // O(lg(n))
        // Note that path compression optimization have been applied.
        int find(int u) {
            if (u == parent[u]) return u;
            return parent[u] = find(parent[u]); // duplicated operation is removed.
        }

        void merge(int u, int v) {
            u = find(u);
            v = find(v);
            if (u == v) return;
            if (rank[u] > rank[v]) swap(u, v);
            // always rank[v] >= rank[u], where rank means the height of each tree.
            parent[u] = v;
            if (rank[u] == rank[v]) rank[v]++;
        }
    };
    ```

