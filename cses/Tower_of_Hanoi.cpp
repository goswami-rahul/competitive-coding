#include<bits/stdc++.h>
using namespace std;

vector<pair<int,int>> ans;
void Solve(int n, int a, int b, int c) {
  if (n == 0) return;
  Solve(n - 1, a, c, b);
  ans.emplace_back(a, b);
  Solve(n - 1, c, b, a);
}

int main() {
  int n; 
  cin >> n;
  Solve(n, 1, 3, 2);
  cout << ans.size() << '\n';
  for (auto [a, b] : ans) {
    cout << a << ' ' << b << '\n';
  }
}
