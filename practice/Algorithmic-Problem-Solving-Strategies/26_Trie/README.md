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

