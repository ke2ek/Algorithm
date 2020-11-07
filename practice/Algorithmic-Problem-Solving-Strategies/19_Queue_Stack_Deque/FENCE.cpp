// https://algospot.com/judge/problem/read/FENCE
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

int N;

int solveByMe(vector<int> &heights) {
    int ret = 0;
    // find the maximum width of each fence.
    for (int i=0; i<N; i++) {
        int width = 1;
        for (int j=i-1; j>=0 && heights[j] >= heights[i]; j--) width++;
        for (int j=i+1; j<N && heights[j] >= heights[i]; j++) width++;
        ret = max(ret, width * heights[i]);
    }
    return ret;
}

// To get the width of each fence, re-use the width of the previous fences.
// Sweeping Algorithm with Stack
int solve(vector<int> &heights) {
    stack<int> remaining;
    heights.push_back(0);
    int ret = 0;
    for (int i=0; i<=N; i++) {
        // if the right one of the remaining fences is higher than heights[i],
        // the maximum rectangle of the right one has width ending to i-th fence.
        while (!remaining.empty() && heights[remaining.top()] >= heights[i])
        {
            int j = remaining.top();
            remaining.pop();
            int width = -1;
            // if no fences are on the left of j-th fence, left[j] = -1.
            // if not, left[j] = the the most right fence's number.
            if (remaining.empty()) width = i;
            else width = (i - remaining.top() - 1);
            ret = max(ret, heights[j] * width);
        }
        remaining.push(i);
    }
    return ret;
}

int main() {
    int T;
    cin >> T;
    for (int tc=0; tc<T; tc++) {
        cin >> N;
        vector<int> heights(N);
        for (int i=0; i<N; i++) cin >> heights[i];
        cout << solve(heights) << endl; // 176 ms
        // cout << solveByMe(heights) << endl; // 940 ms
    }
    return 0;
}
