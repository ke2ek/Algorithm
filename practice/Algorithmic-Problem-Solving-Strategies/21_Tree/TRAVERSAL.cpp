// https://algospot.com/judge/problem/read/TRAVERSAL
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> slice(const vector<int> &v, int a, int b) {
	return vector<int> (v.begin() + a, v.begin() + b);
}

void printPostOrder(const vector<int> &preOrder, const vector<int> &inOrder) {
	const int N = preOrder.size();
	if (preOrder.empty()) return;
	const int root = preOrder[0];
	const int L = find(inOrder.begin(), inOrder.end(), preOrder[0]) - inOrder.begin();

	printPostOrder(slice(preOrder, 1, L+1), slice(inOrder, 0, L));
	printPostOrder(slice(preOrder, L+1, N), slice(inOrder, L+1, N));
	cout << root << " ";
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		int N;
		cin >> N;
		vector<int> preOrder(N), inOrder(N);
		for (int i=0; i<N; i++) cin >> preOrder[i];
		for (int i=0; i<N; i++) cin >> inOrder[i];
		printPostOrder(preOrder, inOrder);
		cout << endl;
	}
	return 0;
}
