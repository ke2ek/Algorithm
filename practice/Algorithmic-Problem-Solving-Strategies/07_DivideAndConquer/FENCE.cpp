// https://algospot.com/judge/problem/read/FENCE
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> H;

// answer: 144ms
int getMaximumSize_answer(int left, int right) {
    if (left == right) return H[left];
    int mid = (left + right) / 2;
    int lo = mid, hi = mid + 1;
    int h = min(H[lo], H[hi]);
    int ret = max(h * 2, max(getMaximumSize_answer(left, mid), getMaximumSize_answer(mid + 1, right)));
    while (lo > left or hi < right) {
        if (hi < right and (lo == left or H[lo - 1] <= H[hi + 1]))
            h = min(h, H[++hi]);
        else
            h = min(h, H[--lo]);
        ret = max(ret, h * (hi - lo + 1));
    }
    return ret;
}

// my solution: 172ms
int getMaximumSize(int left, int right) {
    if (left == right) return H[left];
    int mid = (left + right) / 2;
    int h = H[mid], l = mid - 1, r = mid + 1, w = 1;
    int ret = max(h, max(getMaximumSize(left, mid), getMaximumSize(mid + 1, right)));
    while (l >= left or r <= right) {
        if (r <= right and (l == left or H[l] <= H[r]))
            h = min(h, H[r++]);
        else
            h = min(h, H[l--]);
        ret = max(ret, h * (++w));
    }
    return ret;
}

void solve() {
    int N;
    cin >> N;
    H = vector<int> (N, 0);
    for (int i = 0; i < N; i++) cin >> H[i];
    // O(n*lg(n))
    cout << getMaximumSize_answer(0, N-1) << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}

