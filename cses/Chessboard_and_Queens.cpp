#include<bits/stdc++.h>
using namespace std;

string a[8];
bool row[8];
bool col[8];
bool sum[14];
bool dif[14];

int Solve(int n) {
  if (n == 0) return 1;
  int ways = 0;
  int i = 8 - n;
  for (int j = 0; j < 8; ++j) {
    if (a[i][j] != '.' || row[i] || col[j] || sum[i + j] || dif[i - j + 7])
      continue;
    a[i][j] = 'Q';
    row[i] = col[j] = sum[i + j] = dif[i - j + 7] = true;
    ways += Solve(n - 1);
    a[i][j] = '.';
    row[i] = col[j] = sum[i + j] = dif[i - j + 7] = false;
  }
  return ways;
}

int main() {
  for (int i = 0; i < 8; ++i) cin >> a[i];
  cout << Solve(8) << '\n';
}
