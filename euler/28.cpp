#include <bits/stdc++.h>
using namespace std;
const int N = 1001;
int a[N][N];

int32_t main(int argc, char * argv[]) {
  cin.tie(nullptr) -> sync_with_stdio(false);
  (void) argc; (void) argv;
  
  int ans = 1;
  for (int j = 0, val = 1, len = 2; j < 500; ++j) {
    for (int i = 0; i < 4; ++i)
      val += len, ans += val;
    len += 2;
  }
  cout << ans << endl;
}
