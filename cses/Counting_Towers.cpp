#include<bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
inline int mul(int a, int b, int mod = MOD) {
  return int((long long) a * b % mod);
}
inline void adds(int &a, int b, int mod = MOD) {
  a += b; if (a >= mod) a -= mod;
}

const int N = 1e6 + 5;
int dp[N][3];

int main() {
  dp[0][0] = 1;
  for (int i = 1; i < N; ++i) {
    adds(dp[i][0], mul(2, dp[i-1][0]));
    adds(dp[i][0], mul(3, dp[i-1][1]));
    adds(dp[i][0], dp[i-1][2]);
    
    adds(dp[i][1], dp[i-1][0]);
    adds(dp[i][1], mul(3, dp[i-1][1]));

    adds(dp[i][2], dp[i-1][0]);
    adds(dp[i][2], dp[i-1][2]);
  }
  int tt; cin >> tt;
  while (tt--) {
    int n; cin >> n;
    cout << dp[n][0] << '\n';
  }
}
