/**
 * Notice that the empty squares which are not reachable from any 2x2 
 * valid placement can only be placed with 1x1. Thus , their grundy is 1.
 * So, xor all such 1x1 squares' grundy, and replace them with filled.
 * Now, Every set of 2 consecutive rows must have some empty squares left,
 * but they will always be in pairs.
 * Formally they form 2xL bars. 
 * Also notice that moves at every pairs of rows are independent from the next pair.
 * So, xor their grundy numbers and determine the winner. 
 * Also note that since we need grundy value of upto 10, 
 * we can also precompute and hardcode grudy upto 10.
**/
#include <bits/stdc++.h>
using namespace std;

class LittleSquares {
public:

  const vector<int> grundy{0, 0, 2, 2, 1, 4, 3, 3, 1, 4, 2};
  string winner(vector<string> state){
    int g = 0;
    int n = (int) state.size();
    int m = (int) state[0].size();
    vector<vector<int>> ok(n, vector<int>(m, 0));
    for (int i = 0; i < n; i += 2) {
      for (int j = 0; j < m - 1; ++j) {
        bool can = true;
        can &= state[i][j] == '.';
        can &= state[i][j + 1] == '.';
        can &= i + 1 < n && state[i + 1][j] == '.';
        can &= i + 1 < n && state[i + 1][j + 1] == '.';
        if (can) ok[i][j] = ok[i][j + 1] = ok[i + 1][j] = ok[i + 1][j + 1] = 1;
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (!ok[i][j] && state[i][j] == '.') {
          g ^= 1;
          state[i][j] = '#';
        } 
      }
    }
    vector<int> a;
    memo.assign(16, -1);
    for (int i = 0; i < n; i += 2) {
      int cur = 0;
      for (int j = 0; j < m; ++j) {
        if (state[i][j] == '.') {
          cur++;
        } else if (cur > 0) {
          g ^= grundy[cur];
          cur = 0;
        }
      }
      if (cur > 0) g ^= grundy[cur];
    }
    return g ? "first" : "second";
  };
  
  /*
  int grundy(int x) {
    if (x <= 1) return 0;
    int has = 0;
    // 1x1
    for (int i = 1; i <= x; ++i) 
      has |= 1 << (1 ^ grundy(i - 1) ^ grundy(x - i));
    // 2x2
    for (int i = 1; i < x; ++i) 
      has |= 1 << (grundy(i - 1) ^ grundy(x - i - 1));
    for (int g = 0;; ++g) if (!(has >> g & 1)) return g;
  }
  */
};

int main() {
  LittleSquares sol;
  sol.memo.assign(11, -1);
  for (int i = 0; i <= 10; ++i) sol.grundy(i);
  for (int x: sol.memo) cout << x << ", ";
}
