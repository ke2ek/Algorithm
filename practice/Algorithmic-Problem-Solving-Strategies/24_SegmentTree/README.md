# Segment Tree

## Basic

- In computer science, a [segment tree](https://en.wikipedia.org/wiki/Segment_tree), also known as a statistic tree, is a `tree data structure` used for storing information about **intervals**, or segments.
- It allows querying which of the stored segments contain a given point.
- It is used to answer fastly questions about the specific range in an 1-D array.
    - for instance, finding the minimum value in the given range.
- It represents each range of the given array as one node in a binary tree.
    - so, the root node always indicates the total range [0, n-1].
    - left and right subtree indicate the half of the range.
    - leaf node means the range having the one size (including only one element).


## Range Minimum Query

- Finding the minimum value of the specific range.
- A segment tree is usually a fully binary tree.
    - In this case, it is better to represent to an array than a linked list, such as Heap.
    - The size of the array is defined by `2*n`, where _n_ is the number of elements.
    - But, if _n_ is not the power of 2, we should change _n_ to the power of 2 larger than _n_. And then _n_ is multiplied by 2. So, memory space can be wasted a little bit.
    - Otherwise, just multiply n to 4. (`4*n`)
- The query operation finds the minimum value by using the intersection of the current range and the required range.
    - `query(left, right, node, nodeLeft, nodeRight)`
        - [left, right] = the required range
        - [nodeLeft, nodeRight] = the current range
    - If the intersection is empty, then return infinity because two range is not overlapped.
    - If the intersection is [nodeLeft, nodeRight], then return the minimum value immediately because it means that the range was included in [left, right].
    - Otherwise, call recursively after dividing the current range into half.

    ``` c++
    const int INT_MAX = numeric_limits<int>::max();

    struct RMQ {
        int n;
        vector<int> rangeMin; // the minimum value of each range.

        RMQ(const vector<int>& array) {
            n = array.size();
            rangeMin.resize(4*n);
            init(array, 0, n-1, 1);
        }

        // O(n)
        int init(const vector<int>& array, int left, int right, int node) {
            if (left == right)
                return rangeMin[node] = array[left];
            int mid = (left + right) / 2;
            int leftMin = init(array, left, mid, node * 2);
            int rightMin = init(array, mid + 1, right, node * 2 + 1);
            return rangeMin[node] = min(leftMin, rightMin);
        }

        // O(lg(n))
        int query(int left, int right, int node, int nodeLeft, int nodeRight) {
            if (right < nodeLeft || nodeRight < left)
                return INT_MAX;
            if (left <= nodeLeft && nodeRight <= right)
                return rangeMin[node];
            int mid = (nodeLeft + nodeRight) / 2;
            return min(query(left, right, node * 2, nodeLeft, mid),
                   query(left, right, node * 2 + 1, mid + 1, nodeRight));
        }

        // O(lg(n))
        // Update a tree if array[index] is changed to newValue.
        int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
            if (index < nodeLeft || nodeRight < index)
                return rangeMin[node];
            if (nodeLeft == nodeRight)
                return rangeMin[node] = newValue;
            int mid = (nodeLeft + nodeRight) / 2;
            return rangeMin[node] = min(
                update(index, newValue, node * 2, nodeLeft, mid),
                update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
        }

        // External Interface
        int query(int left, int right) {
            return query(left, right, 1, 0, n - 1);
        }

        int update(int index, int newValue) {
            return update(index, newValue, 1, 0, n - 1);
        }
    };
    ```

- Example: get the most frequency of the given element in the specific range of the ascending ordered sequence.
    - (General) Case 1. there is the most frequency in the left subtree.
    - (General) Case 2. there is the most frequency in the right subtree.
    - (Exception) Case 3. there is the most frequency in both subtrees. i.e. the most frequent numbers in both ranges are the same.
        - When left=[1,2,2,2], right=[2,2,2,3], the freq # of left + the freq # of right = 3 + 3 = 6.
        - When left=[1,1,1,2,2], right=[2,2,3,3,3], the freq # of 2 in both ranges = 2 + 2 = 4, which is larger than the most frequency[=3] of each range.
    - In exception case, notice the additional information when accumulating two answer.
      - The right-most number, 2, in the left sub-range is the same as the left-most number, 2, in the right sub-range.
      - So, it is able to calculate the most frequency by comparing the size and most-frequency of each range.

    ``` c++
    struct RangeResult {
        int size; // the size of the range
        int mostFrequent; // the most frequency of the range
        int leftNumber, leftFreq; // left-most number, its frequency
        int rightNumber, rightFreq; // right-most number, its frequency
    }

    RangeResult merge(const RangeResult& a, const RangeResult& b) {
        RangeResult ret;
        ret.size = a.size + b.size;
        ret.leftNumber = a.leftNumber;
        ret.leftFreq = a.leftFreq;

        // ex) a=[1,1,1,1], b=[1,2,2,2] -> merge
        if (a.size == a.leftFreq && a.leftNumber == b.leftNumber)
            ret.leftFreq += b.leftFreq;

        ret.rightNumber = b.rightNumber;
        ret.rightFreq = b.rightFreq;

        // ex) a=[1,2,2,2], b=[2,2,2,2] -> merge
        if (b.size == b.rightFreq && a.rightNumber == b.rightNumber)
            ret.rightFreq += a.rightFreq;

        ret.mostFrequent = max(a.mostFrequent, b.mostFrequent);

        // exception case
        if (a.rightNumber == b.leftNumber)
            ret.mostFrequent = max(ret.mostFrequent, a.rightFreq + b.leftFreq);

        return ret;
    }
    ```


## [Fenwick Tree or Binary Indexed Tree](https://en.wikipedia.org/wiki/Fenwick_tree)

- It is used to calculate **range sum** fastly using **partial sum**.
- Also, it saves memory space than a segment tree.
    - In a segment tree, each parent node needs both children to calculate the sum of its own range.
    - But, in the Fenwick Tree, the sum of range [i, j] can be calculated by subtracting `psum[i-1]` from `psum[j]`, where `psum[i]` is the partial sum from 0 to i.
    - It means to need **only one subtree** to calculate the sum in a fenwick tree.

- Reference: https://cp-algorithms.com/data_structures/fenwick.html

    ![fenwick](https://raw.githubusercontent.com/e-maxx-eng/e-maxx-eng/master/img/binary_indexed_tree.png)

- Since the size difference between each node and its subtree is twice, each index in a fenwick tree can be represented as a **binary number** so that it is easier to find the lower or upper section.
- Example: given an 1-D array, A, `tree[i]` is the sum of the range in which there is right-most number, `A[i]`.
    - In this case, the index of a fenwick tree starts at 1.

    ``` text
    [A]

    | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |

    [Fenwick Tree]

    |-----------------------------8-|
    |-------------4-|
    |-----2-|       |-----6-|
    |-1-|   |-3-|   |-5-|   |-7-|   |

    The binary number of 8 is 1000.
    The binary number of 4 is 100.
    The binary number of 2 is 10.
    The binary number of 1 is 1.
    
    The range-length of 8 is 2^3 = 8
        because of the number of zero in the binary is 3 (8->1000).
    The range-length of 7 is 2^0 = 1.
        because of the number of zero in the binary is 0 (7->111).
    The range-length of 6 is 2^1 = 2.
        because of the number of zero in the binary is 1 (6->110).
    The range-length of 4 is 2^2 = 4.
        because of the number of zero in the binary is 2 (4->100).
    ```

    - We could easily get the length and the index of sub-range with the binary number.
    - Notice that the range to be added can be found by subtracting the last 1 bit (LSB) of each binary number.

    ``` text
    psum[7] = tree[7] + tree[6] + tree[4]

    by Binary Expression,

        psum[111] = tree[111] + tree[110] + tree[100]
    ```

- Time Complexity: `O(lg(n))`

    ``` c++
    struct FenwickTree {
        vector<int> tree;
        
        FenwickTree(int n) : tree(n+1) {}
        
        // Return the partial sum of [0, pos].
        int psum(int pos) {
            ++pos; // 1-indexed.
            int ret = 0;
            while (pos > 0) {
                ret += tree[pos];
                // Flip the last up-bit (1) to get the next range.
                pos &= (pos - 1);
            }
            return ret;
        }

        // Update if a new value is added or subtracted at the given position
        void add(int pos, int val) {
            ++pos;
            while (pos < tree.size()) {
                tree[pos] += val;
                pos += (pos & -pos);
            }
        }
    };
    ```

- The Fenwick Tree is used to obtain the **range sum** if the given array is frequently changed.
