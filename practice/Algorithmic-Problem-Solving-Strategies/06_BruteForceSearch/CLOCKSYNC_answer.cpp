// https://algospot.com/judge/problem/read/CLOCKSYNC
#include <iostream>
#include <vector>
using namespace std;

const int INF = 9999, SWITCH = 10, CLOCKS = 16;
// linked[i][j] = 'x': connected i-th switch and j-th clock.
// linked[i][j] = '.': not connected betweeen two things.
const char linked[SWITCH][CLOCKS+1] = {
  "xxx.............", // 0, 1, 2
  "...x...x.x.x....", // 3, 7, 9, 11
  "....x.....x...xx", // 4, 10, 14, 15
  "x...xxxx........", // 0, 4, 5, 6, 7
  "......xxx.x.x...", // 6, 7, 8, 10, 12
  "x.x...........xx", // 0, 2, 14, 15
  "...x..........xx", // 3, 14, 15
  "....xx.x......xx", // 4, 5, 7, 14, 15
  ".xxxxx..........", // 1, 2, 3, 4, 5
  "...xxx...x...x..", // 3, 4, 5, 9, 13
};

// Check if all the clocks take 12.
bool areAligned(const vector<int> &clocks) {
  bool flag = true;
  for (int i=0; i<CLOCKS; i++) {
    if (clocks[i] != 12) {
      flag = false;
    }
  }
  return flag;
}

// Push the switch of s_number.
void push(vector<int> &clocks, int s_number) {
  for (int i=0; i<CLOCKS; i++) {
    if (linked[s_number][i] == 'x') {
      clocks[i] += 3;
      if (clocks[i] == 15) clocks[i] = 3;
    }
  }
}

int solve(vector<int> &clocks, int s_number) {
  if (s_number == SWITCH) return areAligned(clocks) ? 0 : INF;
  int ret = INF;
  for (int cnt=0; cnt<4; cnt++) { // 누르는 횟수
    ret = min(ret, cnt + solve(clocks, s_number + 1));
    push(clocks, s_number);
  }
  return ret;
}

int main() {
  int T;
  cin >> T;
  for (int tc=0; tc<T; tc++) {
    vector<int> clocks(CLOCKS);
    for (int i=0; i<CLOCKS; i++) {
      cin >> clocks[i];
    }
    int answer = solve(clocks, 0);
    if (answer == INF) answer = -1;
    cout << answer << endl;
  }
}

