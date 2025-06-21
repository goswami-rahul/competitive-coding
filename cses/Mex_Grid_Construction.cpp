#include<bits/stdc++.h>
using namespace std;

int a[101][101];

int main() {
  int n; cin >> n;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      set<int> s;
      for (int k = 0; k < i; ++k) s.insert(a[k][j]);
      for (int k = 0; k < j; ++k) s.insert(a[i][k]);
      while (s.count(a[i][j])) ++a[i][j];
      cout << a[i][j] << ' ';
    }
    cout << '\n';
  }  
}
