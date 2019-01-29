/*
 * There is an important observation, that every edge that we add
 * (without the offer) must be joining a component with the minimum
 * cost vertex in it. After we know this, we can insert all n - 1
 * such edges to our edge set, and run Kruskal's to get minimum cost.
 */

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
struct edge {
    int u, v; i64 w;
    edge(int u, int v, i64 w): u(u), v(v), w(w) {};
    bool operator < (const edge& o) {
        return w < o.w;
    }
};
struct DSU {
    vector<int> par;
    int num_items;
    DSU(int n) {
        par.resize(n);
        iota(par.begin(), par.end(), 0);
        num_items = n;
    }
    inline int find(int u) {
        return (u == par[u] ? u : par[u] = find(par[u]));
    }
    inline bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (rand() % 2) swap(u, v);
        par[v] = u;
        num_items--;
        return true;
    }
};
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    vector<i64> a(n);
    for (auto &e: a) cin >> e;
    vector<edge> b;
    for (int i = 0; i < m; ++i) {
        int u, v; i64 w;
        cin >> u >> v >> w;
        --u; --v;
        b.emplace_back(u, v, w);
    }
    int x = 0;
    for (int i = 1; i < n; ++i) {
        if (a[i] < a[x]) x = i;
    }
    for (int i = 0; i < n; ++i) {
        if (x == i) continue;
        b.emplace_back(i, x, a[x] + a[i]);
    }
    sort(ALL(b));
    DSU dsu(n);
    i64 ans = 0LL;
    for (const edge& e: b) {
        ans += e.w * dsu.merge(e.u, e.v);
    }
    cout << ans << '\n';
    
    return 0;
}
