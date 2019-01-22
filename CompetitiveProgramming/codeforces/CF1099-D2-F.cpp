#pragma GCC optimize("O3")
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
    }
    return os << "}";
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
#define sz(v) (int((v).size()))
/***********************************************************************/
template <class T>
struct Fenwick {
    int n;
    vector<T> bit;
    Fenwick(int n): n(n), bit(n + 1, T()) {}
    T ask(int x) {
        T ans = 0;
        for(; x > 0; x -= x & -x)
            ans += bit[x];
        return ans;
    }
    void upd(int x, T v) {
        if(x <= 0) return;
        for(; x <= n; x += x & -x)
            bit[x] += v;
    }
};

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    i64 t;
    cin >> n >> t;
    vector<int> cok(n), tym(n), cost(n, 0);
    for (int &i: cok) cin >> i;
    for (int &i: tym) cin >> i;
    vector<vector<int>> tree(n);
    for (int i = 1; i < n; ++i) {
        int u, x;
        cin >> u >> x;
        --u;
        cost[i] = x;
        tree[u].push_back(i);
    }
    Fenwick<i64> fen(1e6 + 5), fen2(1e6 + 5);
    function<i64(int,i64)> dfs = [&] (int u, i64 cum) {
        cost[u] += cum;
        i64 avail = t - 2LL * cost[u];
        if (avail <= 0LL) {
            return 0LL;
        }
        fen.upd(tym[u], (i64) cok[u] * tym[u]);
        fen2.upd(tym[u], (i64) cok[u]);
        i64 ret = -1;
        if (fen.ask(1e6) <= avail) {
            ret = fen2.ask(1e6);
        } else {
            int lo = 1, hi = 1e6;
            while (lo < hi) {
                int mid = (lo + hi + 1) >> 1;
                if (fen.ask(mid) <= avail) {
                    lo = mid;
                } else {
                    hi = mid - 1;
                }
            }
            i64 k = fen.ask(lo);
            ret = fen2.ask(lo);
            ret += (avail - k) / (lo + 1);
        }
        multiset<i64> mxs;
        for (int v: tree[u]) {
            mxs.insert(dfs(v, cost[u]));
            if (sz(mxs) > 2) mxs.erase(mxs.begin());
        }
        if (!mxs.empty()) {
            if (u == 0) {
                ret = max(ret, *mxs.rbegin());
            } else if (sz(mxs) == 2){
                ret = max(ret, *mxs.begin());
            }
        }
        fen.upd(tym[u], (i64) -cok[u] * tym[u]);
        fen2.upd(tym[u], -cok[u]);
        return ret;
    };
    cout << dfs(0, 0LL) << '\n';
    
    return 0;
}
