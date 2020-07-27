# String

## Find a needle in a haystack

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
			- Start to compare at the index `begin + matched - the length of the suffix == begin + matched - pi[matched - 1]`.
			- It means to did discover the suffix, which has the maximum length, in the string N[...matched-1].
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
						// Notice that comparison does not start at 0 in the substring N[...matched-1].
						matched = pi[matched - 1];
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
		
	- Proof of Concept: [poc.cpp](./poc.cpp)


## Circular Shift

- ver KMP Algorithm Application.
- shifts(original, target) = return how many shifts does it require to change from _original_ to _target_.
	- for left-shift, call shifts(original, target).
	- for right-shift, call shifts(target, original).

	``` c++
	int shifts(const string &original, const string &target) {
		return kmpSearch(original + original, target)[0];
	}
	```


## [Suffix Array](https://en.wikipedia.org/wiki/Suffix_array)

- A sorted array of all suffixes of a string.
- Algorithm
	1. Get beginning indexes of all suffixes in a string S.
		- Let's call `i` the index. i.e. S[i...] is the i-th suffix.
	2. Arrange the suffixes in alphabetical order.
	3. Save the order of indexes after sorting.
		- i.e. A[j] = the beginning position of the j-th suffix after sorting
- It is used to search for a substring by taking advantage of the string N is the prefix of a substring, a suffix of the string H, if N is included in H.
- Naive method generating the suffix array.
	- Given a string like "aaa...aaa", the time complexity is O(n^2 * lg(n)) in case n is the length of given string.
	
	``` c++
	// Given i, j are the beginning position of two suffixes,
	// Compare i with j.
	struct SuffixComparator {
		const string& s;
		SuffixComparator(const string& s) : s(s) {}
		bool operator () (int i, int j) {
			// Save the cost to generate temporary objects.
			return strcmp(s.c_str() + i, s.c_str() + j) < 0;
		}
	};

	// Generate the Suffix Array.
	vector<int> getSuffixArrayNavie(const string& s) {
		vector<int> perm; // the beginning positions of each suffix
		for (int i = 0; i < s.size(); i++) perm.push_back(i);
		// Sort by alphabetical order
		sort(perm.begin(), perm.end(), SuffixComparator(s));
		return perm;
	}
	```

- [Manber-Myers Algorithm](https://www.geeksforgeeks.org/suffix-array-set-1-introduction/)
	- Naive algorithm spend time a lot. Also, the more efficient algorithm is so hard to implement during the given time in a programming competition.
	- Notice that Manber-Myers Algorithm is more simple and efficient than.
	- The idea is to consider about **how many letters to sort the suffixes**.
		- First, sort by suffixes based on the only first letter.
		- Second, sort by suffixes based on two letters.
		- Next, keep sorting by multiplying 2 to the number of letters to compare.
	- By using order information of the suffixes gotten from the previous sorting, comparison time is O(1).
	- That's why this works faster than the naive method although it require to sort many times.
	- After generating the suffix array,
		- Group by the first _t_ letters of suffixes.
		- group[i] = the number of group that S[i...] belongs to
		- Visit the suffixes from the front, and assign group numbers to each suffix.
		
	``` c++
	// Given group number based on the first t letters of each suffix,
	// compare given two suffixes by the first 2*t letters.
	// group[] includes a zero-length suffix.
	struct Comparator {
		const vector<int> &group;
		int t;
		Comparator(const vector<int> &_group, int _t): group(_group), t(_t) {
			group = _group;
			t = _t;
		}
		bool operator() (int a, int b) {
			// if the first t letters are different,
			if (group[a] != group[b]) return group[a] < group[b];
			// if not, then compare the first t letters of S[a+t...] and S[b+t...].
			return group[a+t] < group[b+t];
		}
	};
	```

	- Note that it does not check whether it is out of range of an array in case of group[a+t] and group[b+t]. 
		- Comparing the first t letters means that two suffixes are always longer than t.
	
	``` c++
	vector<int> getSuffixArray(const string &s) {
		int n = s.size();
		int t = 1;
		vector<int> group(n+1);
		for (int i = 0; i < n; i++) group[i] = s[i];
		group[n] = -1;
		vector<int> perm(n);
		for (int i = 0; i < n; i++) perm[i] = i; // suffix array
		while (t < n) {
			// group[] have been operated based on the first t letters.
			// Sort `perm` again based on the first 2*t letters.
			Comparator compareUsing2T(group, t);
			sort(perm.begin(), perm.end(), compareUsing2T);
			t *= 2;
			if (t >= n) break;
			// Group by the first 2*t letters.
			vector<int> newGroup(n+1);
			newGroup[n] = -1;
			newGroup[perm[0]] = 0;
			for (int i = 1; i < n; i++) {
				if (compareUsing2T(perm[i-1], perm[i]))
					newGroup[perm[i]] = newGroup[perm[i-1]] + 1;
				else
					newGroup[perm[i]] = newGroup[perm[i-1]];
			}
			group = newGroup
		}
		return perm;
	}
	```

	- Example: Circular String
		- Given a circular string connected the beginning and end can be read clockwise and N is the length of the string, the number of methods to read is N.
		- What is the string most front by alphabetical order?
		- Notice that the string which is made of repeating the original string 2 times includes all strings from N methods.

		``` c++
		// O(n * (lg(n))^2)
		string minShift(const string &s) {
			string s2 = s + s;
			vector<int> a = getSuffixArray(s2);
			for (int i = 0; i < a.size(); i++) {
				if (a[i] <= s.size())
					return s2.substr(a[i], s.size());
			}
			return "__oops__";
		}
		```

	- Example: Count the number of different substrings
		- Notice that all substrings of S are corresponding to prefixes of all suffixes in S.
		
		``` c++
		// Calculate the length of common prefix of bothn S[i...] and S[j...].
		int commonPrefix(const string &s, int i, int j) {
			int k = 0;
			while (i < s.size() && j < s.size() && s[i] == s[j]) {
				i++; j++; k++;
			}
			return k;
		}

		// Count all different substrings of S.
		int countSubstrings(const string &s) {
			vector<int> a = getSuffixArray(s);
			int ret = 0;
			int n = s.size();
			for (int i = 0; i < a.size(); i++) {
				int cp = 0;
				if (i > 0) cp = commonPrefix(s, a[i-1], a[i]);
				ret += n - a[i] - cp;
			}
			return ret;
		}
		```

