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
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n;
    vector<vector<int>> tree(n);
    vector<int> roots;
    for (int i = 0; i < n; ++i) {
        int u;
        cin >> u; --u;
        if (u != -1)
            tree[u].push_back(i);
        else
            roots.push_back(i);
    }
    vector<int> sz(n), big(n, -1), h(n);
    const int LOGN = 20;
    vector<vector<int>> par(n, vector<int>(LOGN, -1));
    function<void(int)> pre = [&] (int u) {
        sz[u] = 1;
        int mx = -1;
        for (int &v: tree[u]) {
            h[v] = 1 + h[u];
            par[v][0] = u;
            int x = u;
            for (int i = 1; par[v][i - 1] != -1; ++i) {
                par[v][i] = par[par[v][i - 1]][i - 1];
            }
            pre(v);
            sz[u] += sz[v];
            if (sz[v] > mx) {
                mx = sz[v];
                big[u] = v;
            }
        }
    };
    for (int r: roots) {
        h[r] = 0;
        pre(r);
    }
    vector<vector<pair<int,int>>> Q(n);
    cin >> m;
    vector<int> ans(m);
    for (int i = 0; i < m; ++i) {
        int v, p;
        cin >> v >> p;
        --v;
        for (int j = 0; j < LOGN; ++j) if (p >> j & 1) {
            v = par[v][j];
            if (v == -1) {
                ans[i] = 0;
                break;
            }
        }
        if (v != -1)
            Q[v].emplace_back(i, p + h[v]);
    }
    using H = unordered_map<int, int>;
    function<void(int, H&)> dfs = [&] (int u, H &a) {
        if (!tree[u].empty()) {
            dfs(big[u], a);
            for (int &v: tree[u]) {
                if (v == big[u]) continue;
                H his;
                dfs(v, his);
                for (auto& [hh, x]: his)
                    a[hh] += x;
            }
        }
        a[h[u]]++;
        for (auto& [id, hh]: Q[u]) {
            assert(a.count(hh));
            ans[id] = a[hh] - 1;
        }
    };
    for (int r: roots) {
        H a;
        dfs(r, a);
    }
    for (auto x: ans) cout << x << ' ';
    cout << '\n';

    return 0;
}
