// https://algospot.com/judge/problem/read/QUANTIZE
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int N, S;
int A[100];
int pSum[101], pSqrSum[101];
int cache[100][10];
const int INF = 987654321;

int minError(int l, int r) {
    if (l == r) return 0;
    int psum = pSum[r+1] - pSum[l], divider = r - l + 1;
    // Calculate the minimum error with the differential of SSE.
    int m = int(0.5 + (double)psum / divider);
    // Return the minimum SSE.
    return (pSqrSum[r+1] - pSqrSum[l]) - 2 * m * psum + m * m * divider;
}

int quantize(int from, int parts) {
    if (from == N) return 0; // If all the numbers are quantized
    if (parts == S) return INF; // If any numbers could not be quantized
    int &ret = cache[from][parts];
    if (ret != -1) return ret;
    ret = INF;
    // Divide A[from ... from+L-1] and A[from+L ... ].
    for (int L = 1; from + L <= N; L++)
        ret = min(ret, minError(from, from + L - 1) + quantize(from + L, parts + 1));
    return ret;
}

// O(N^2 * S)
void solve() {
    cin >> N >> S;
    for (int i = 0; i < N; i++) cin >> A[i];
    sort(A, A + N);
    pSum[0] = pSqrSum[0] = 0;
    for (int i = 0; i < N; i++) {
        pSum[i+1] = pSum[i] + A[i];
        pSqrSum[i+1] = pSqrSum[i] + A[i] * A[i];
    }
    memset(cache, -1, sizeof(cache));    
    cout << quantize(0, 0) << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}
