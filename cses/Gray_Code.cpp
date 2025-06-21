#include<bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<string> a = {""};
  for (int i = 0; i < n; ++i) {
    for (int j = a.size() - 1; j >= 0; --j) {
      a.push_back(a[j] + '1');
      a[j] += '0';
    }
  }
  for (auto s : a) cout << s << '\n';
}
