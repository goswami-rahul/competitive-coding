#include<bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<pair<int,int>> a = {{0, 0}};
  for (int i = 1; i <= n; ++i) {
    int x; cin >> x;
    while (x <= a.back().first) a.pop_back();
    cout << a.back().second << ' ';
    a.emplace_back(x, i);
  }
}
