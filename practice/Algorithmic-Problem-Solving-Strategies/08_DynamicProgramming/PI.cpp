// https://algospot.com/judge/problem/read/PI
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

int N;
int nums[10000];
int cache[10000];
const int INF = 987654321;

int classify(int a, int b) {
    int diff = nums[a+1] - nums[a];
    bool progressive = true;
    for (int i = a; i < b; i++) {
        if (nums[i+1] - nums[i] != diff)
            progressive = false;
    }
    if (progressive) {
        if (diff == 0) return 1;
        else if (abs(diff) == 1) return 2;
    }
    bool alternating = true;
    for (int i = a; i + 1 < b; i++)
        if (nums[i] != nums[i+2])
            alternating = false;
    if (alternating) return 4;
    if (progressive) return 5;
    return 10;
}

int minLevelSum(int begin) {
    if (begin == N) return 0;
    int &ret = cache[begin];
    if (ret != -1) return ret;
    ret = INF;
    for (int L = 3; L <= 5; L++)
        if (begin + L <= N)
            ret = min(ret, minLevelSum(begin + L) + classify(begin, begin + L - 1));
    return ret;
}

// O(N)
void solve() {
    string s;
    cin >> s;
    N = s.size();
    memset(nums, 0, sizeof(nums));
    memset(cache, -1, sizeof(cache));
    for (int i = 0; i < N; i++) nums[i] = s[i] - '0';
    cout << minLevelSum(0) << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--)
        solve();
    return 0;
}