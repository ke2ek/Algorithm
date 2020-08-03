// https://algospot.com/judge/problem/read/NERD2
#include <iostream>
#include <map>
using namespace std;

map<int, int> coords;

// check if (x, y) is dominated by existing coordinates.
bool isDominated(int x, int y) {
    map<int, int>::iterator it = coords.lower_bound(x);
    if (it == coords.end()) return false;
    return y < it->second;
}

// remove all dominated coordinates by (x, y).
void removeDominated(int x, int y) {
    map<int, int>::iterator it = coords.lower_bound(x);
    // no coordinates is located on the left of (x, y).
    if (it == coords.begin()) return;
    --it;
    // find the most left coordinate of (x, y)
    while (1) {
        // if one is not dominated, the others after that are not.
        if (it->second > y) break;
        // if there is no coordinates on the left, remove the last coordinate.
        if (it == coords.begin()) {
            coords.erase(it);
            break;
        } else {
            map<int, int>::iterator jt = it;
            --jt;
            coords.erase(it);
            it = jt; // move to the left.
        }
    }
    
}

// if new coordinate (x,y) is added, update coords.
// and then return the number of the undominated.
int registered(int x, int y) {
    if (isDominated(x, y)) return coords.size(); // abandon (x, y)
    removeDominated(x, y);
    coords[x] = y;
    return coords.size();
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        int N, x, y, ans=0;
        cin >> N;
        for (int i=0; i<N; i++) {
            cin >> x >> y;
            ans += registered(x, y);
        }
        cout << ans << endl;
        coords.clear();
    }
    return 0;
}
