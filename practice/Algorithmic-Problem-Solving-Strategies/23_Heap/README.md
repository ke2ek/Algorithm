# Heap

## Basic

- The height of a tree keeps to be constant using the following rules.
- All levels except the last level should have nodes fully, where the level means a set of nodes having same depth.
- The last level should have nodes located by left-to-right.
- A parent node should always have a key greater than the keys of children.
- In an array, the position of a tree is defined by:
    - The left node of the node corresponding to A[i] is located at A[2 * i + 1].
    - The right node of the node corresponding to A[i] is located at A[2 * i + 2].
    - The parent node of node corresponding to A[i] is located at A[(i - 1) / 2].

    ``` c++
    vector<int> heap;
    ```

- With these properties, the Heap is implemented easier than the Binary Search Tree because it does not need to have pointers to refer to something.


## Insertion

- To follow the shape rule of the Heap, which should have a constant height, a new node is inserted at the end of an array.
- Next, if the parent node has a key lesser than the new node, exchange two nodes.
- And then keep going on the next parent node.

    ``` c++
    void push_heap(vector<int> &heap, int key) {
        heap.push_back(key);
        int idx = heap.size() - 1; // the current position of a new node
        while (idx > 0 && heap[(idx-1)/2] < heap[idx]) {
            swap(heap[idx], heap[(idx-1)/2]);
            idx = (idx - 1) / 2;
        }
    }
    ```


## Pop the maximum node: Remove the root node

- To follow the shape rule of the Heap, the last node is deleted.
- Next, from a root node to leaf nodes, if a parent node has a key lesser than keys of children, exchange the parent node with the greater one of children
- And then keep going on the next children node.

    ``` c++
    // Remove the root node
    void pop_heap(vector<int> &heap) {
        heap[0] = heap.back();
        heap.pop_back();
        int here = 0;
        while (1) {
            int left = here * 2 + 1;
            int right = here * 2 + 2;
            if (left >= heap.size()) break; // in case a leaf node
            int next = here;
            if (heap[next] < heap[left])
                next = left;
            if (right < heap.size() && heap[next] < heap[right])
                next = right;
            if (next == here) break;
            swap(heap[here], heap[next]);
            here = next;
        }
    }
    ```

