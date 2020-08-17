# Trie

## Basic

- Trie is a data structure representing a set of a string.
- It is a string-specialized tree.
- It can find the given string in a set by taking O(M) only, where M is the length of the string.
- The tree is composed of nodes corresponding to a prefix of each string of the set.
- Example: S = {"BE", "BET", "BUS", "TEA", "TEN"}
	- root is always empty string.
	- `<"...">` means an element of a set, so is marked as terminal node.

	``` text
		   None
		/	 \
	      "B"	  "T"
	    /	\	   |
	"BU"	<"BE">	  "TE"
	  |	  |	   |    \
	<"BUS"> <"BET"> <"TEA"> <"TEN">
	```

- Each node has pointers of children and a bool variable, terminal.
	- Notice that the size of the pointer array is 26, the number of alphabets.
	- That's why we don't have to define a string in each node.
	- We can get a string using the path from root node to destination node.
	
	``` c++
	const int ALPHABETS = 26;
	int toIndex(char ch) {
		return ch - 'A';
	}

	struct TrieNode {
		TrieNode* children[ALPHABETS];
		bool terminal;

		TrieNode(): terminal(false) {
			memset(children, 0, sizeof(children));
		}

		~TrieNode() {
			for (int i=0; i<ALPHABETS; i++) {
				if (children[i])
					delete children[i];
			}
		}

		void insert(const char* key) {
			if (*key == 0) {
				terminal = true;
			} else {
				int next = toIndex(*key);
				if (children[next] == 0) {
					children[next] = new TrieNode();
				}
				children[next]->insert(key + 1);
			}
		}

		TrieNode* find(const char* key) {
			if (*key == 0) return this;
			int next = toIndex(*key);
			if (children[next] == 0) return 0;
			return children[next]->find(key + 1);
		}
	};
	```

- It is usually used to complete a input string automatically.
- But, the disadvantage of the Trie is to waste memory space a lot.
	- thus, recommend to implement in case of small input.
	

## Suffix Trie

- Instead of putting a set of strings in the Trie, all the suffix of one string S is inserted.
- Notice that all substring of a string is a prefix of some suffix.
- Since the Suffix Trie includes all the prefixes of the saved string, it has nodes matched to all substring of the string.
- To solve still wasting memory, there is the Suffix Tree that it sums up nodes having only one child.


## [Aho-Corasick](https://www.geeksforgeeks.org/aho-corasick-algorithm-pattern-searching/)

- Multi-String Search Algorithm using Trie
	- It is useful for searching many strings in a long length document.
	- a.k.a Optimized KMP
- Example:
	- haystack = "CACACHEFCACHY"
	- needles = {"CACHE", "HE", "CHEF", "ACHY"}
- In KMP algorithm
	- There are several lengths of a substring, in which a prefix and a suffix are the same, at the Partial Match Table.
	- If we should find a lot of needles in a haystack, we would visit the haystack as much as the number of needles.
	- For instance, we can go to the state "CACH" if the next letter in the state "CAC" is "H", but we should go back to the state "C" and compare if not.
- In Aho-Corasick
	- Implemented with Trie, it can find all needles as visiting a haystack only one time.
	- In case not matched two characters, the location to go back is defined by failure function not partial match table.
	- i.e. if two different needles have the same state and are not matched at the next letter, failure function does not always go back to the first.

	```
	failure(s) = the path to the longest string which is a suffix of s.
	```

- Calculation in failure function
	- **failure link**. as the value failure function returns, the pointer of the node to try again.
	- **output list**. needles discovered when arrived in each node. It can avoid working at duplicate strings using each string array.
		- Example: suppose that there are some needles, "ABC", "B", "BC". If the current node is the state "AB", we will have a needle "B". If we go to the state "ABC", we should have needles, "ABC" and "BC" not all needles.

	``` c++
	class TrieNode {
	public:
	    TrieNode* children[ALPHABETS];
	    int terminal; // the number of terminated string (if none, -1)
	    int first; // the first added word's number
	    TrieNode* fail; // failure link
	    vector<int> output; // output list

	    TrieNode(): terminal(-1), first(-1), fail(0) {
	        memset(children, 0, sizeof(children));
	    }

	    ~TrieNode() {
	        output.clear();
	        for (int i=0; i<ALPHABETS; i++)
	            delete children[i];
	    }

	    /*
	     * key: a suffix of the given string
	     * id: the number of the given string
	     */
	    void insert(const char* key, int id) {
	        if (first == -1) first = id;
	        if (*key == 0) {
	            terminal = id;
	        } else {
	            int chr = toIndex(*key);
	            if (children[chr] == 0) {
	                children[chr] = new TrieNode();
	            }
	            children[chr]->insert(key + 1, id);
	        }
	    }

	    // ...
	};


	// Calculate failure link and output list.
	void computeFailFunc(TrieNode* root) {
	    queue<TrieNode*> q;
	    root->fail = root;
	    q.push(root);
	    while (!q.empty()) {
	        TrieNode* here = q.front();
	        q.pop();
	        // visite children
	        for (int edge=0; edge<ALPHABETS; edge++) {
	            TrieNode* child = here->children[edge];
	            if (!child) continue;
	            // all nodes in level 1 has root as failure link.
	            if (here == root) {
	                child->fail = root;
	            } else {
	                TrieNode* t = here->fail;
	                // follow failure link of parent.
	                while (t != root && t->children[edge] == 0)
	                    t = t->fail;
	                if (t->children[edge]) t = t->children[edge];
	                child->fail = t;
	            }
	            child->output = child->fail->output;
	            // if there is a needle in this state, add the number of a needle.
	            if (child->terminal != -1)
	                child->output.push_back(child->terminal);
	            q.push(child);
	        }
	    }
	}


	// find all patterns in a `trie`.
	// save a pair (last letter, pattern number) whenever a pattern appears in `s`.
	// O(N + M + P) where N is the length of a haystack,
	//              where M is the sum of each needle's length,
	//              where P is the number of needles.
	vector<pair<int, int> > ahoCorasick(const string &s, TrieNode* root) {
	    vector<pair<int, int> > ret;
	    TrieNode* state = root;
	    for (int i=0; i<s.size(); i++) {
	        int chr = toIndex(s[i]);
	        while (state != root && state->children[chr] == 0)
	            state = state->fail;
	        if (state->children[chr]) state = state->children[chr];
	        for (int j=0; j<state->output.size(); j++)
	            ret.emplace_back(i, state->output[j]);
	    }
	    return ret;
	}
	```

- Example: failure links of both "CAC" and "CACH"
	- The suffixes of two needles(nodes), "AC" and "ACH", are the child nodes and simultaneously failure links respectively.
	- Let's say that a string A followed by a letter x is the parent-child relationship on the trice. (A <--> Ax) If the failure link in `Ax` does not go to the root, the last letter of the substring that follows the failure link will be always x. If one of the suffixes of A is B, one of the substrings encountered along the failure link of Ax will be `Bx`. Therefore, it is easy to see that `Bx` is the failure link of `Ax` by checking if the node "A" has an offspring with a failure link, `Bx`.
	- back to the example, suppose that there are the nodes "CACH" and "CACHE". Assuming that there is no edge to "E" in the node "ACH", which is the failure link of "CACH", we are not able to find the failure link of "CACHE" by this rule.
	- But, there is a way to follow the failure link of "ACH" one more time. If you reach the root node, the string would not exist in the haystack. Otherwise, Following this failure link, you will visit the suffixes of "CACH" from the longest. In this process, if there is an edge to "E" in "CH", we can get the node "CHE".
	- Using these rules, all nodes can take each failure link.
- Notice that, with BFS, we can miss a failure link of parents in the process to visit the nodes to follow failure links. To solve it, we would work from the nodes with substrings shorter than the current node when failed. If we take failure links from the nodes of the lower depth, each node can have the required failure link.

