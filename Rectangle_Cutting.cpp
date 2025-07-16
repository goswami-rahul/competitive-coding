#include<bits/stdc++.h>
using namespace std;

const int N = 505;
int dp[N][N];

int main() {
  for (int i = 1; i < N; ++i) {
    dp[i][1] = dp[1][i] = i - 1;
  }
  for (int i = 2; i < N; ++i) {
    for (int j = 2; j < N; ++j) {
      dp[i][j] = 2e9;
      if (i == j) dp[i][j] = 0;
      for (int k = 1; k < i; ++k) {
        dp[i][j] = min(dp[i][j], 1 + dp[k][j] + dp[i - k][j]);
      }
      for (int k = 1; k < j; ++k) {
        dp[i][j] = min(dp[i][j], 1 + dp[i][k] + dp[i][j - k]);
      }
    }
  }
  int x, y; cin >> x >> y;
  cout << dp[x][y];
}
