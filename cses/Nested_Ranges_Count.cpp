#include<bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template<typename T, typename V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<T, V, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
// find_by_order(), order_of_key()


int main() {
  int n; cin >> n;
  vector<tuple<int,int,int>> a(n);
  for (int i = 0; i < n; ++i) {
    int x, y; cin >> x >> y;
    a[i] = {x, -y, i};
  }
  sort(a.rbegin(), a.rend());
  vector<int> ans(n);
  ordered_set<pair<int,int>> rs;
  for (auto [l, r, i] : a) {
    r = -r;
    ans[i] = rs.order_of_key({r + 1, -1});
    rs.insert({r, i});
  }
  for (int i = 0; i < n; ++i) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
  reverse(a.begin(), a.end());
  rs.clear();
  for (auto [l, r, i] : a) {
    r = -r;
    ans[i] = rs.size() - rs.order_of_key({r, -1});
    rs.insert({r, i});
  }
  for (int i = 0; i < n; ++i) {
    cout << ans[i] << ' ';
  }
}
