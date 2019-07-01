/**
 *    author:  tourist
 *    created: 31.03.2018 11:41:48       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  mt19937 rng(58);
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    vector<pair<int, int>> to_spam;
    for (int day = 1; day <= 100; day++) {
      int foo;
      cin >> foo;
      if (foo == -1) {
        exit(0);
      }
      assert(foo == day);
      if (day <= 80) {
        cout << (day % 15 + 1) << " " << (rng() % 99 + 1) << endl;
        continue;
      }
      if (day <= 85) {
        cout << day % 5 + 16 << " " << 0 << endl;
        int cc;
        cin >> cc;
        for (int bar = 0; bar < cc; bar++) {
          int baz;
          cin >> baz;
        }
        to_spam.emplace_back(cc, day % 5 + 16);
        continue;
      }
      if (day < 100) {
        sort(to_spam.begin(), to_spam.end());
        cout << to_spam[1].second << " " << 100 << endl;
        to_spam[1].first++;
        continue;
      }
      sort(to_spam.begin(), to_spam.end());
      cout << to_spam[0].second << " " << 100 << endl;
    }
  }
  return 0;
}
