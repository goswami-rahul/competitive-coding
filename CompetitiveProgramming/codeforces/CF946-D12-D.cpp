/**
 * For every string, calculate the minimum amount of time he need to spend
 * when he skips i classes, i from 0 to k
 * Then, create dp[n][k] - dp[i][j] denotes the minimum time needed upto
 * ith day, skipping j or less classes.
 * The transitions are in k^2 for each i, therefore
 * Complexity is O(n * k * k)
**/
#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
template<typename T, typename V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<T, V, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>; // find_by_order(), order_of_key()
using ll = long long int;
using i64 = long long int;
#define SZ(v) (int((v).size()))
#define ALL(vec) (vec).begin(),(vec).end()
template <typename T> inline void ckmax(T &x, T y) {if (y > x) x = y; }
template <typename T> inline void ckmin(T &x, T y) {if (y < x) x = y; }
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " =: " << a << endl;
    err(++it, args...);
}
template <typename T1, typename T2>
inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& buf) {
    return os << "(" << buf.first << ": " << buf.second << ")";
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const std::vector<T>& v) {
    bool first = true;
    os << "[";
    for(unsigned int i = 0; i < v.size(); i++) {
        if(!first) os << ", ";
        os << v[i];
        first = false;
    }
    return os << "]";
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const multiset<T>& v) {
    bool first = true;
    os << "{";
    for (auto ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii;
        first = false;
    }
    return os << "}";
}
inline std::ostream &operator << (std::ostream & os,const std::multiset<pair<int,int>,greater<pair<int,int>>>& v) {
    bool first = true;
    os << "{";
    for (auto x: v) {
        if(!first) os << ", ";
        os << x;
        first = false;
    }
    return os << "}";
}
template<typename T1, typename T2>
inline std::ostream &operator << (std::ostream & os,const std::map<T1, T2>& v) {
    bool first = true;
    os << "{";
    for (typename std::map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii ;
        first = false;
        return os << "}";
    }
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const vector<vector<T>>& v) {
    for (auto &u: v) os << '\n' << u;
    return os;
}
template<typename T>
void finish(T ans) {cout << ans << '\n'; exit(0);}
const int MOD = 1e9 + 7;
const long long INF = 1e18;
const double EPS = 1e-6;
#define PI 3.14159265358979323846
/***********************************************************************/

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> can(n, vector<int>(k + 1, MOD));
    for (int x = 0; x < n; ++x) {
        string s;
        cin >> s;
        vector<int> pre(m + 1, 0);
        for (int i = 1; i <= m; ++i) {
            pre[i] = pre[i - 1] + (s[i - 1] == '1');
        }
        for (int i = 0; i < m; ++i) {
            for (int j = i + 1; j <= m; ++j) {
                int p = pre[m] - (pre[j] - pre[i]);
                if (p > k) continue;
                can[x][p] = min(can[x][p], j - i);
            }
        }
        for (int i = pre[m]; i <= k; ++i) can[x][i] = 0;
    }
    for (int i = 1; i < n; ++i) {
        vector<int> now(k + 1, MOD);
        for (int j = 0; j <= k; ++j) {
            for (int r = 0; r <= j; ++r) {
                now[j] = min(now[j], can[i - 1][r] + can[i][j - r]);
            }
        }
        can[i] = now;
    }
    cout << *min_element(ALL(can[n - 1])) << '\n';
    
    return 0;
}

