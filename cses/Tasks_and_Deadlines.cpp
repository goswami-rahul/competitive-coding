#include<bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> a(n);
  long long ans = 0;
  for (int &x : a) {
    cin >> x;
    int d; cin >> d;
    ans += d;
  }
  sort(a.begin(), a.end());
  long long sum = 0;
  for (int x : a) {
    sum += x;
    ans -= sum;
  }
  cout << ans;
}
