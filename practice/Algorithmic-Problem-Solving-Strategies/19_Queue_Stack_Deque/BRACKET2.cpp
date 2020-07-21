// https://algospot.com/judge/problem/read/BRACKETS2
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

bool solve() {
	string str;
	cin >> str;
	stack<char> s;
	for (char ch: str) {
		if (ch == '(' || ch == '[' || ch == '{') {
			s.push(ch);
		} else {
			if (s.empty()) return false;
			if (ch == ')' && s.top() == '(') s.pop();
			else if (ch == '}' && s.top() == '{') s.pop();
			else if (ch == ']' && s.top() == '[') s.pop();
			else return false;
		}
	}
	return s.empty();
}

// Answer
bool wellMatched(const string& formula) {
	const string opening("({["), closing(")}]");
	stack<char> openStack;
	for (int i=0; i<formula.size(); i++) {
		if (opening.find(formula[i]) != -1) openStack.push(formula[i]);
		else {
			if (openStack.empty()) return false;
			if (opening.find(openStack.top()) != closing.find(formula[i])) return false;
			openStack.pop();
		}
	}
	return openStack.empty();
}

int main() {
	int T;
	cin >> T;
	while(T--) {
		string formula;
		cin >> formula;
		if (wellMatched(formula)) cout << "YES" << endl;
		else cout << "NO" << endl;
		// if (solve()) cout << "YES" << endl;
		// else cout << "NO" << endl;
	}
	return 0;
}
