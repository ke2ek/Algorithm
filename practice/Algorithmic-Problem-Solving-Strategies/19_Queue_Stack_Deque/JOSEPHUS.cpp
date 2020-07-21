// https://algospot.com/judge/problem/read/JOSEPHUS
#include <iostream>
#include <queue>
using namespace std;

void solve(int n, int k) {
	queue<int> q;
	for (int i=1; i<=n; i++) q.push(i);
	while(q.size() > 2) {
		q.pop();
		for (int i=1; i<k; i++) {
			int x = q.front();
			q.pop();
			q.push(x);
		}
	}
	int a = q.front();
	int b = q.back();
	if (a < b) cout << a << " " << b << endl;
	else cout << b << " " << a << endl;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		int n, k;
		cin >> n >> k;
		solve(n, k);
	}
	return 0;
}
