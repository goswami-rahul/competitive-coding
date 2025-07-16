#include<bits/stdc++.h>
using namespace std;

int dp[5050][5050];

int main() {
  string a, b;
  cin >> a >> b;
  for (int i = 1; i <= a.size(); ++i) {
    dp[i][0] = dp[i - 1][0] + 1;
    for (int j = 1; j <= b.size(); ++j) {
      dp[0][j] = dp[0][j - 1] + 1;
      dp[i][j] = 2e9;
      dp[i][j] = dp[i - 1][j - 1] + (a[i - 1] != b[j - 1]);
      dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
      dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
    }
  }
  cout << dp[a.size()][b.size()];
}
