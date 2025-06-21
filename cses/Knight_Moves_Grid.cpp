#include<bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<vector<int>> a(n, vector<int>(n, -1));
  a[0][0] = 0;
  vector<pair<int, int>> bfs = {{0, 0}};
  for (int i = 0; i < bfs.size(); ++i) {
    auto [x, y] = bfs[i];
    auto dxs = {+2, -2};
    auto dys = {+1, -1};
    for (int j = 0; j < 2; ++j, swap(dxs, dys))
      for (int dx : dxs) for (int dy : dys) {
        int nx = x + dx, ny = y + dy;
        if (nx >= 0 && nx < n && ny >= 0 && ny < n && a[nx][ny] == -1) {
          a[nx][ny] = 1 + a[x][y];
          bfs.emplace_back(nx, ny);
        }
      }
  }  
  for (auto &v : a) {
    for (auto x : v) cout << x << ' ';
    cout << '\n';
  }
}
