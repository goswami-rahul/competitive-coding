/* https://cses.fi/110/list
 * Idea is similar to the editorial - https://github.com/mostafa-saad/MyCompetitiveProgramming/tree/master/Olympiad/Baltic/official/boi2006_solutions
 * First decode the array to contain adjacent item with frequencies. 
 * Traverse i from 1 to size of decoded array
 * len(x) denotes minimum length to encode upto i characters, such that
 * the repetition symbol is set to x at last.
 * Maintain len(x), and keep track of the transitions to reconstruct
 * the array.
*/

#include <bits/stdc++.h>
#define SZ(v) (int((v).size()))
#define ALL(vec) (vec).begin(),(vec).end()
using namespace std;
typedef long long int i64;
template<typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template<typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}
 
/***********************************************************************/

// return ajacent blocks with their counts
vector<pair<int,i64>> decode(const vector<int> &enc) {
  vector<pair<int,i64>> a;
  int rep = 0;
  for (int i = 0; i < (int) enc.size(); ++i) {
    int x = enc[i];
    if (x == rep) {
      int y = enc[i + 1], z = enc[i + 2];
      i += 2;
      if (y == rep) {
        if (a.empty() || a.back().first != rep)
          a.emplace_back(rep, 0);
        a.back().second += z + 1;
      } else {
        if (z == 0) {
          rep = y;
        } else {
          if (a.empty() || a.back().first != y) 
            a.emplace_back(y, 0);
          a.back().second += z + 3;
        }
      }
    } else {
      if (a.empty() || a.back().first != x) 
        a.emplace_back(x, 0);
      a.back().second++;
    }
  }
  return a;
}

int32_t main() {

  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vector<int> enc(m);
  for (int &z: enc) cin >> z;
  auto a = decode(enc);
  int k = SZ(a);
  
  vector<int> link(k), len(n, 3);
  len[0] = 0;
  set<pair<int,int>> st;
  for (int i = 0; i < n; ++i) {
    st.emplace(len[i], i);
  }
  int add = 0;
  for (int i = 0; i < k; ++i) {
    int x; i64 cnt;
    tie(x, cnt) = a[i];
    int cost = (int) (cnt / (n + 2) * 3) + min(3, (int) (cnt % (n + 2)));
    int my_cost = (int) (cnt / n * 3) + (cnt % n == 0 ? 0 : 3);
    st.erase({len[x], x});
    int opt = st.begin()->second;
    int check = 3 + cost + len[opt];
    len[x] = my_cost + len[x];
    link[i] = x;
    if (uin(len[x], check)) {
      link[i] = opt;
    }
    add += cost;  // add cost to every y
    len[x] -= cost; // decrease cost from x (same effect as below O(n) loop)
    st.emplace(len[x], x);
    
    /*for (int y = 0; y < n; ++y) if (y != x) {
      len[y] += cost;
    }*/
  }
  int now = -1, min_len = INT_MAX;
  for (int i = 0; i < n; ++i) {
    if (uin(min_len, len[i] += add)) now = i;
  }
  vector<int> change(k, -1); // change rep to change[i] at pos i
  for (int i = k - 1; i >= 0; --i) {
    if (a[i].first == now) {
      if (link[i] == now) continue;
      if (i <= k) change[i + 1] = now;
      now = link[i];
    }
  }
  change[0] = now;
  
  vector<int> ans;
  int rep = 0;
  for (int i = 0; i < k; ++i) {
    int new_rep = change[i];
    if (new_rep != -1 && new_rep != rep) {
      // change new_rep
      ans.push_back(rep);
      ans.push_back(new_rep);
      ans.push_back(0);
      rep = new_rep;
    }
    int x = a[i].first;
    i64 cnt = a[i].second;
    if (x == rep) {
      while (cnt > n) {
        ans.push_back(rep);
        ans.push_back(rep);
        ans.push_back(n - 1);
        cnt -= n;
      }
      ans.push_back(rep);
      ans.push_back(rep);
      ans.push_back((int) cnt - 1);
    } else {
      while (cnt > n + 2) {
        ans.push_back(rep);
        ans.push_back(x);
        ans.push_back(n - 1);
        cnt -= n + 2;
      }
      if (cnt > 3) {
        ans.push_back(rep);
        ans.push_back(x);
        ans.push_back((int) cnt - 3);
      } else {
        while (cnt--) {
          ans.push_back(x);
        }
      }
    }
  }
  assert (SZ(ans) == min_len);
  assert (SZ(ans) <= SZ(enc));
  assert (decode(ans) == a);
  cout << SZ(ans) << '\n';
  for (int x: ans) {
    cout << x << ' ';
  } cout << endl;

  return 0;
}
