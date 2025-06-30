#include<bits/stdc++.h>
using namespace std;

const int N = 7;
string s;
map<long long, int> dp[8][8];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
char d[] = {'R', 'L', 'D', 'U'};

bool Ok(int i, int j, long long mask) {
  if (i >= N || j >= N || i < 0 || j < 0) return false;
  if (mask >> (i * N + j) & 1) return false; 
  return true;
}

void Count(int i, int j, int steps, long long mask) {
  if (!Ok(i, j, mask)) return;
  if (steps * 2 == N * N - 1) {
    ++dp[i][j][mask];
    return;
  }
  mask |= 1LL << (i * N + j);
  array<int, 2> ok{};
  for (int k = 0; k < 4; ++k) {
    ok[k / 2] += Ok(i + dx[k], j + dy[k], mask);
  }
  if (ok[0] % 2 == 0 && ok[1] % 2 == 0) return;
  for (int k = 0; k < 4; ++k) {
    if (s[steps] == d[k] || s[steps] == '?') {
      Count(i + dx[k], j + dy[k], steps + 1, mask);
    }
  }
}

int Count2(int i, int j, int steps, long long mask) {
  if (!Ok(i, j, mask)) return 0;
  mask |= 1LL << (i * N + j);
  if (steps * 2 == N * N - 1) {
    mask ^= (1LL << N * N) - 1;
    if (dp[i][j].count(mask)) {
      return dp[i][j][mask];
    }
    return 0;
  }
  array<int, 2> ok{};
  for (int k = 0; k < 4; ++k) {
    ok[k / 2] += Ok(i + dx[k], j + dy[k], mask);
  }
  if (ok[0] % 2 == 0 && ok[1] % 2 == 0) return 0;
  int res = 0;
  for (int k = 0; k < 4; ++k) {
    if (s[steps] == d[k] || s[steps] == '?') {
      res += Count2(i + dx[k], j + dy[k], steps + 1, mask);
    }
  }
  return res;
}

int main() {
  cin >> s;
  Count(0, 0, 0, 0);
  reverse(s.begin(), s.end());
  for (char &c : s) {
    if (c == 'R') c = 'L';
    else if (c == 'L') c = 'R';
    else if (c == 'D') c = 'U';
    else if (c == 'U') c = 'D';
  }
  cout << Count2(N - 1, 0, 0, 0) << '\n';
}
