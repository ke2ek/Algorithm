// https://algospot.com/judge/problem/read/PICNIC
#include <iostream>
#include <cstring>
using namespace std;

int n;
bool areFriends[10][10];

// taken[i] = true if i-th student has found a friend already, otherwise false.
int countPairings(bool taken[10]) {
    int firstFree = -1;
    // get the smallest number in student id.
    for (int i = 0; i < n; i++) {
        if (!taken[i]) {
            firstFree = i;
            break;
        }
    }

    // base case: all students have their own partenr.
    if (firstFree == -1) return 1;
    int ret = 0;
    // make the friends pair.
    for (int pairWith = firstFree + 1; pairWith < n; pairWith++) {
        if (!taken[pairWith] && areFriends[firstFree][pairWith]) {
            taken[firstFree] = taken[pairWith] = true;
            ret += countPairings(taken);
            taken[firstFree] = taken[pairWith] = false;
        }
    }
    return ret;
}

void solve() {
    int m;
    cin >> n >> m;
    bool taken[10];
    memset(areFriends, 0, sizeof(areFriends));
    memset(taken, 0, sizeof(taken));
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        areFriends[a][b] = areFriends[b][a] = true;
    }
    cout << countPairings(taken) << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
