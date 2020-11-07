// https://algospot.com/judge/problem/read/ITES
#include <iostream>
#include <queue>
using namespace std;

typedef unsigned long long ull;
const ull MOD = 4294967296L;

ull A[50000001];

void generateSignals() {
    ull seed = 1983;
    for (int i = 0; i < 50000000; i++) {
        A[i] = seed % 10000 + 1;
        seed = (seed * 214013 + 2531011) % MOD;
    }
}


// O(N*K)
int simple(int n, int k) {
    int ret = 0;
    for (int head = 0; head <= n; head++) {
        int sum = 0;
        for (int tail = head; tail <= n; tail++) {
            sum += A[tail];
            if (sum == k) ret++;
            if (sum >= k) break;
        }
    }
    return ret;
}


// O(N)
// in simple(...), the index `tail` starts at `head`,
// so whenever head increments, there are some duplicated ranges.
// The ranges are usually useless because it would have been counted in previous
// if each range is greater or equal than K.
// To solve it, restart `tail` at the previous.
int optimized(int K, int N) {
    int ret = 0, tail = 0, rangeSum = A[0];
    for (int head = 0; head < N; head++) {
        while (rangeSum < K && tail + 1 < N)
            rangeSum += A[++tail];

        if (rangeSum == K) ret++;
        rangeSum -= A[head];
    }
    return ret;
}


// Answer O(N)
// But, in this problem, memory is limited so hard.
// Online Algorithm solves it by sliding memory with queue.
int countRanges(int k, int n) {
    queue<int> range;
    ull seed = 1983;
    int ret = 0, rangeSum = 0;
    for (int i = 0; i < n; i++) {
        int newSignal = seed % 10000 + 1;
        rangeSum += newSignal;
        range.push(newSignal);

        while (rangeSum > k) {
            rangeSum -=range.front();
            range.pop();
        }

        if (rangeSum == k) ret++;
        seed = (seed * 214013 + 2531011) % MOD;
    }
    return ret;
}


int main() {
    int T;
    cin >> T;
    // generateSignals();
    while(T--) {
        int K, N;
        cin >> K >> N;
        // cout << simple(N, K) << endl;
        // cout << optimized(K, N) << endl;
        cout << countRanges(K, N) << endl;
    }
    return 0;
}
