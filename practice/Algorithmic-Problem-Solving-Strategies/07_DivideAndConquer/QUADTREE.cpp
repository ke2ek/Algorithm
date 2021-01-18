// https://algospot.com/judge/problem/read/QUADTREE
#include <iostream>
#include <string>
using namespace std;

// answer (faster)
string reverse(string::iterator& it) {
    char head = *it;
    ++it;
    if (head != 'x') return string(1, head);
    string upperLeft = reverse(it);
    string upperRight = reverse(it);
    string lowerLeft = reverse(it);
    string lowerRight = reverse(it);
    return head + lowerLeft + lowerRight + upperLeft + upperRight;
}

// my solution
string divideAndConquer(string s) {
    if (s[0] != 'x') return s.substr(0,1);
    string tl = divideAndConquer(s.substr(1));
    string tr = divideAndConquer(s.substr(tl.size() + 1));
    string bl = divideAndConquer(s.substr(tl.size() + tr.size() + 1));
    string br = divideAndConquer(s.substr(tl.size() + tr.size() + bl.size() + 1));
    return s[0] + bl + br + tl + tr;
}

// O(n), where n is the length of the given string.
void solve() {
    string s;
    cin >> s;
    // cout << divideAndConquer(s) << endl;
    string::iterator it = s.begin();
    cout << reverse(it) << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}

