/*
 * maintain an array of ranges/segments which are reachable for the
 * current row. Now move to the next row which contains any blocking cell.
 * If there are 1 or more rows in between, change the segment and add
 * the cells to the answer.
 * When changing rows, carefully merge them to the previous segment,
 * and update the answer.
*/
#include <bits/stdc++.h>
using namespace std;
#define ALL(vec) (vec).begin(),(vec).end()

int32_t main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vector<pair<int,int>> a(m);
  set<int> xs;
  for (auto &[x, y] : a) {
    cin >> x >> y;
    --x; --y;
    xs.insert(x);
  }
  xs.insert(n - 1);
  long long ans = 0LL;
  for (int x : xs) {
    a.emplace_back(x, n);
    ++m;
  }
  sort(ALL(a));
  vector<pair<int,int>> reach = {{0, 1}};
  int ptr = 0, last_row = -1;
  while (ptr < m) {
    int row = a[ptr].first;
    int diff = row - last_row;
    if (diff > 1) {
      ans += (long long) (diff - 1) * (n - reach[0].first);
      reach = {{reach[0].first, n}}; diff = 1;
    }
    vector<pair<int,int>> new_reach;
    int last_col = -1;
    while (ptr < m && a[ptr].first == row) {
      int col = a[ptr++].second;
      if (col > last_col + 1) {
        auto it = upper_bound(ALL(reach), last_col + 1, [] (const auto &lhs, const auto &rhs) {
          return lhs < rhs.second;
        });
        if (it != reach.end()) {
          int from = max(last_col + 1, it->first);
          if (col > from) new_reach.emplace_back(from, col);
        }
      }
      last_col = col;
    }
    last_row = row;
    reach = move(new_reach);
    for (auto [x, y] : reach) ans += y - x;
    if (reach.empty()) break;
  }
  cout << ans << endl;
  
  return 0;
}
