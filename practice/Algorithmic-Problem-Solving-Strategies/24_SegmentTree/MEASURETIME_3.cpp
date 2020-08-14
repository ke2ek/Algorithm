// https://algospot.com/judge/problem/read/MEASURETIME
#include <cstdio>
#include <vector>
using namespace std;

// O(N * lg(N))
// merge recursivly A[left..right].
// return the number of inversions in the range.
long long countMoves3(vector<int> &A, int left, int right) {
    if (left == right) return 0;
    int mid = (left + right) / 2;
    // divide and conquer two part
    long long ret = countMoves3(A, left, mid);
    ret += countMoves3(A, mid + 1, right);
    // merge
    vector<int> tmp(right - left + 1);
    int tmpIndex = 0, leftIndex = left, rightIndex = mid + 1;
    while (leftIndex <= mid || rightIndex <= right) {
        if (leftIndex <= mid &&
            (rightIndex > right || A[leftIndex] <= A[rightIndex])) {
            tmp[tmpIndex++] = A[leftIndex++];
        } else {
            // A[rightIndex] is smaller than the left part of an array.
            // add the number of inversions.
            ret += mid - leftIndex + 1;
            tmp[tmpIndex++] = A[rightIndex++];
        }
    }
    
    for (int i=0; i<tmp.size(); i++) {
        A[left + i] = tmp[i];
    }
    return ret;
}

void solve() {
    int n;
    scanf("%d", &n);
    vector<int> A(n);
    for (int i=0; i<n; i++) scanf("%d", &A[i]);
    printf("%lld\n", countMoves3(A, 0, n-1)); // Using Treap
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
