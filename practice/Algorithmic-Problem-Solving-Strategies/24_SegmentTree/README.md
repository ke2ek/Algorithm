# Segment Tree

## Basic

- It is used to answer fastly questions about the specific range of an array.
	- for instance, finding a minimum value of the range.
- Segment Tree represents each range of given array as a node of a binary tree.
	- so, the root node always indicates the total range [0, n-1].
	- left and right subtree indicate each half.
	- leaf node means the range having the one size (only one element).


## Range Minimum Query

- Finding a minimum value of the specific range.
- Segment Tree usually becomes a fully binary tree.
	- In this case, it is better to represent to an array than a linked list, such as Heap.
	- The size of the array is defined by `2*n`, where n is the number of elements.
	- But, if _n_ is not the power of 2, _n_ should be the power of 2 larger than _n_. And then _n_ is multiplied by 2.
	- So, memory space is wasted a little bit.
	- Otherwise, just multiply n to 4. (`4*n`)
- The query operation returns the minimum value as following the intersection range of the current finding range and the wanted range.
	- `query(left, right, node, nodeLeft, nodeRight)`
		- [left, right] = the wanted range
		- [nodeLeft, nodeRight] = the current finding range
	- if the intersection is empty, then return infinity because two range is not overlapped.
	- if the intersection is [nodeLeft, nodeRight], then return the minimum value immediately because [left, right] includes the range.
	- Otherwise, call recursively to children(subtrees).

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

- Example: get the most frequency of an element in the specific range of sequence ordered by ascending.
	- (General) Case 1. found the most frequency in the left subtree.
	- (General) Case 2. found the most frequency in the right subtree.
	- (Exception) Case 3. found the most frequency in two subtrees. i.e. the frequent number is the same in both ranges.
		- if left=[1,2,2,2], right=[2,2,2,3], then returns the freq # of left + the freq # of right = 3 + 3 = 6
		- if left=[1,1,1,2,2], right=[2,2,3,3,3], then returns the freq # of 2 = 4 (is larger than each the freq # of two ranges)
	- In exception case, need to consider extra information for summing two answer.

	``` c++
	struct RangeResult {
		int size; // the size of the range
		int mostFrequent; // the most frequency of the range
		int leftNumber, leftFreq;
		int rightNumber, rightFreq;
	}

	RangeResult merge(const RangeResult& a, const RangeResult& b) {
		RangeResult ret;
		ret.size = a.size + b.size;
		ret.leftNumber = a.leftNumber;
		ret.leftFreq = a.leftFreq;

		if (a.size == a.leftFreq && a.leftNumber == b.leftNumber)
			ret.leftFreq += b.leftFreq;

		ret.rightNumber = b.rightNumber;
		ret.rightFreq = b.rightFreq;

		if (b.size == b.rightFreq && a.rightNumber == b.rightNumber)
			ret.rightFreq += a.rightFreq;

		ret.mostFrequent = max(a.mostFrequent, b.mostFrequent);

		if (a.rightNumber == b.leftNumber)
			ret.mostFrequent = max(ret.mostFrequent, a.rightFreq + b.leftFreq);

		return ret;
	}
	```


## [Fenwick Tree or Binary Indexed Tree](https://en.wikipedia.org/wiki/Fenwick_tree)

- It is used to calculate **range sum** fastly using **partial sum**.
- Also, it saves memory space than the Segment Tree.
	- In the Segment Tree, each parent node requires both children to calculate the sum of their own range.
	- But, in a Fenwick Tree, the sum of range [i, j] can be calculated by subtracting psum[i-1] from psum[j], where _psum[i]_ is the partial sum from 0 to i.
	- It means to need only one subtree to calculate the sum of its own range.
- Since the subtrees differ by two times each, it is easy and fast to find the upper or lower section by expressing the index of a range in binary numbers.
- Example
	- Notice that the range to be added can be found by subtracting the last 1 bit (LSB) of each binary number.
	- For this, the index of the Fenwick Tree starts from 1.

	``` text
	psum[7] = tree[7] + tree[6] + tree[4]

	by Binary Expression,

		psum[111] = tree[111] + tree[110] + tree[100]
	```

- Time Complexity: O(lg(n))

	``` c++
	struct FenwickTree {
		vector<int> tree;
		
		FenwickTree(int n) : tree(n+1) {}
		
		// return the partial sum of [0, pos]
		int psum(int pos) {
			++pos; // the index starts at 1
			int ret = 0;
			while (pos > 0) {
				ret += tree[pos];
				// flipping the last up-bit (1) for the next range
				pos &= (pos - 1);
			}
			return ret;
		}

		// for update, a new value is added or subtracted at the desired position
		void add(int pos, int val) {
			++pos;
			while (pos < tree.size()) {
				tree[pos] += val;
				pos += (pos & -pos);
			}
		}
	};
	```

- The Fenwick Tree is used to obtain the range sum if a given array is frequently changed.
