#include<bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template<typename T, typename V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<T, V, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
// find_by_order(), order_of_key()

int main() {
  int n, k; cin >> n >> k;
  ordered_set<int> s;
  for (int i = 0; i < n; ++i) {
    s.insert(i + 1);
  }
  int p = 0;
  while (!s.empty()) {
    p = (p + k) % s.size();
    auto it = s.find_by_order(p);
    cout << *it << ' ';
    s.erase(it);
  }
}
