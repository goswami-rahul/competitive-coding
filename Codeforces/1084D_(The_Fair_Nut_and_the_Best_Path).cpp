#pragma GCC optimize ("O3")
#include<bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

template<typename T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>; // find_by_order(), order_of_key()
using ll = long long int;
using i64 = long long int;
#define all(vec) (vec).begin(),(vec).end()
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
inline std::ostream &operator << (std::ostream & os,const std::set<T>& v) {
    bool first = true;
    os << "{";
    for (typename std::set<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii;
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
    }
    return os << "}";
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const vector<vector<T>>& v) {
    os << '\n';
    for (auto &u: v) os << u << '\n';
    return os;
}

const int MOD = 1e9 + 7;
const long long INF = 1e18;
const double EPS = 1e-6;
/***********************************************************************/
inline int add(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}
inline int sub(int a, int b) {
    a -= b;
    if (a < 0) a += MOD;
    return a;
}
inline int mul(int a, int b) {
    return (long long) a * b % MOD;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<i64> a(n);
    for (auto &i: a) cin >> i;
    vector<vector<pair<int,i64>>> tree(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        i64 w;
        cin >> u >> v >> w;
        --u; --v;
        tree[u].emplace_back(v, w);
        tree[v].emplace_back(u, w);
    }
    i64 ans = -1;
    vector<i64> dp(n, 0), take(n, -1);
    function<void(int,int)> dfs1 = [&] (int u, int pa) {
        take[u] = a[u];
        i64 mx = 0;
        for (auto [v, c]: tree[u]) {
            if (v == pa) continue;
            dfs1(v, u);
            if (take[v] > c) {
                mx = max(mx, take[v] - c);
                take[v] -= c;
            } else {
                take[v] = 0;
            }
        }
        take[u] += mx;
    };
    dfs1(0, -1);
    function<void(int,int,i64)> dfs2 = [&] (int u, int pa, i64 push) {
        dp[u] = a[u] + push;
        int k = -1;
        i64 mx = 0;
        for (auto [v, c]: tree[u]) {
            if (v == pa) continue;
            if (take[v] > mx) {
                mx = take[v];
                k = v;
            }
        }
        if (push >= mx) {
            push += a[u];
            for (auto [v, c]: tree[u]) {
                if (v == pa) continue;
                if (c < push) {
                    dfs2(v, u, push - c);
                    dp[u] = max(dp[u], dp[v]);
                } else {
                    dfs2(v, u, 0);
                }
            }
            push -= a[u];
            ans = max(ans, dp[u]);
            return;
        }
        mx += a[u];
        for (auto [v, c]: tree[u]) {
            if (v == pa || v == k) continue;
            if (c < mx) {
                dfs2(v, u, mx - c);
                dp[u] = max(dp[u], dp[v]);
            } else {
                dfs2(v, u, 0);
            }
        }
        mx = push;
        for (auto [v, c]: tree[u]) {
            if (v == k || v == pa) continue;
            mx = max(mx, take[v]);
        }
        mx += a[u];
        for (auto [v, c]: tree[u]) {
            if (v != k) continue;
            if (c < mx) {
                dfs2(v, u, mx - c);
                dp[u] = max(dp[u], dp[v]);
            } else {
                dfs2(v, u, 0);
            }
        }
        ans = max(ans, dp[u]);
    };
    dfs2(0, -1, 0);
    cout << ans << '\n';

    return 0;
}
