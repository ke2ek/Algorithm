// https://algospot.com/judge/problem/read/JOSEPHUS
#include <iostream>
#include <list>

using namespace std;

void mySolution() {
	int T;
	cin >> T;
	while (T--) {
		int N, K;
		cin >> N >> K;
		list<int> l;
		for (int i=2; i<=N; i++) l.push_back(i);

		list<int>::iterator it = l.begin();
		for (N--; N>2; N--) {
			for (int i=1; i<K; i++) {
				if (it == l.end()) it = l.begin();
				it++;
			}
			if (it == l.end()) it = l.begin();
			list<int>::iterator deleted = it++;
			l.erase(deleted);
		}
		cout << l.front() << l.back() << endl;
		l.clear();
	}
}

// Answer
void josephus(int n, int k) {
	list<int> survivors;
	for (int i=1; i<=n; i++) survivors.push_back(i);
	list<int>::iterator kill = survivors.begin();
	while(n > 2) {
		kill = survivors.erase(kill); // erase() returns the next node of the removed.
		if (kill == survivors.end()) kill = survivors.begin();
		--n;
		for (int i=0; i<k-1; i++) {
			++kill;
			if (kill == survivors.end()) kill = survivors.begin();
		}
	}
	cout << survivors.front() << " " << survivors.back() << endl;
}

int main() {
	// mySolution();
	int T;
	cin >> T;
	while(T--) {
		int n, k;
		cin >> n >> k;
		josephus(n, k);
	}
	return 0;
}
