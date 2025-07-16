#include<bits/stdc++.h>
using namespace std;

int dp[1050][1050];
int mm[1050][1050];

int main() {
  int n, m; cin >> n >> m;
  vector<int> a(n), b(m);
  for (int &x : a) cin >> x;
  for (int &x : b) cin >> x;
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  for (int i = 1; i <= a.size(); ++i) {
    for (int j = 1; j <= b.size(); ++j) {
      dp[i][j] = dp[i - 1][j - 1] + (a[i - 1] == b[j - 1]);
      mm[i][j] = 3;
      if (dp[i - 1][j] > dp[i][j]) {
        dp[i][j] = dp[i - 1][j];
        mm[i][j] = 1;
      }
      if (dp[i][j - 1] > dp[i][j]) {
        dp[i][j] = dp[i][j - 1];
        mm[i][j] = 2;
      }
    }
  }
  cout << dp[a.size()][b.size()] << '\n';
  for (int i = a.size(), j = b.size(); i > 0 && j > 0; ) {
    int t = mm[i][j];
    if (t == 3 && a[i - 1] == b[j - 1]) cout << a[i - 1] << ' ';
    if (t & 1) --i;
    if (t & 2) --j;
  }
}
