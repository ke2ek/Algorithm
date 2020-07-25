# String

## Search substring: Find a needle in a haystack

- ex) Assume that two strings, H="hogwarts" and N="gwart".
	- String H (haystack) has N (needle) as substring.
	- The position which N starts at in H is 2. i.e. H[2...]="gwarts"

- To solve it, we can try to find a needle at each character of a haystack.
	- Given the length of the string haystack, |H|, and the length of the string needle, |N|,
	- Time complexity is O(|H| * |N|).

	``` c++
	vector<int> naiveSearch(const string &H, const string &N) {
		vector<int> ret;
		for (int begin = 0; begin + N.size() <= H.size(); begin++) {
			bool matched = true;
			for (int i = 0; i < N.size(); i++) {
				if (H[begin + i] != N[i]) {
					matched = false;
					break;
				}
			}
			if (matched) ret.push_back(begin);
		}
		return ret;
	}
	```

- [Knuth-Morris-Pratt Algorithm](https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/)
	- Notice that we do not need to compare each character of the string H.
		- Using partial-match-table!
	- How to find the next beginning position to compare.
		- begin = the current index of H to start to compare with N
		- matched = the number of matched characters
		- N[...matched-1] means the matched prefix of N when compared with H.
			- Let's call it sub-prefix.
		- Assume that two characters are different at `begin + matched`.
		- If there is a suffix same as the sub-prefix of N in the substring H[begin...begin+matched-1],
			- Start to compare at the index `begin + matched - the length of the suffix`.
		- Based on this idea, define pi[i] as the maximum length of a string which is both a prefix and a suffix.
			- Let's call pi[] partial-match-table.

		``` c++
		// O(|H|)
		vector<int> kmpSearch(const string &H, const string &N) {
			int n = H.size(), m = N.size();
			vector<int> ret;
			vector<int> pi = getPartialMatch(N);
			int begin = 0, matched = 0;
			while (begin <= n - m) {
				if (matched < m && H[begin + matched] == N[matched]) {
					++matched;
					if (matched == m) ret.push_back(begin);
				} else {
					if (matched == 0) ++begin;
					else {
						// N[...matched-1] is the same as the suffix of a substring of H.
						begin += matched - pi[matched - 1];
						matched = pi[matched-1];
					}
				}
			}
			return ret;
		}
		```

		- `getPartialMatch()` can be implemented by calculating pi[i] for all prefixes at the same time.
		
		``` c++
		// O(|N|^2)
		// Calculate pi[i] using partial-match appearing whenever comparing oneself in N.
		vector<int> getPartialMatch(const string &N) {
			int m = N.size();
			vector<int> pi(m, 0);
			for (int begin = 1; begin < m; begin++) {
				for (int i = 0; i + begin < m; i++) {
					if (N[begin + i] != N[i]) break;
					pi[begin + i] = max(pi[begin + i], i+1);
				}
			}
			return pi;
		}
		```

		- Notice that `getPartialMatch()` can be written with KMP algorithm, too.
			- In this case, whenever _begin_ change, the previous pi[] is used.
				- because pi[matched - 1] has been calculated.
			- Do not need to call max().

		``` c++
		// O(|N|)
		vector<int> getPartialMatch(const string &N) {
			int m = N.size();
			vector<int> pi(m, 0);
			int begin = 1, matched = 0; // if begin == 0, find itself. (except!)
			while (begin + matched < m) {
				if (N[begin + matched] == N[matched]) {
					++matched;
					pi[begin + matched - 1] = matched; // Update pi[i] whenever matched increments.
				} else {
					if (matched == 0) ++begin;
					else {
						begin += matched - pi[matched - 1];
						matched = pi[matched - 1];
					}
				}
			}
			return pi;
		}
		```
		
