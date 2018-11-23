#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

template<typename T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
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
inline std::ostream &operator << (std::ostream & os,const std::unordered_set<T>& v) {
    return os << std::set<T>(v.begin(), v.end());
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const std::multiset<T,greater<T>>& v) {
    return os << std::vector<T>(v.begin(), v.end());
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const ordered_set<T>& v) {
    return os << std::set<T>(v.begin(), v.end());
}
template<typename T1, typename T2>
inline std::ostream &operator << (std::ostream & os,const std::unordered_map<T1, T2>& v) {
    return os << std::map<T1, T2>(v.begin(), v.end());
}

const int MOD = 1e9 + 7;
const long long INF = 1e18;
const double EPS = 1e-6;
/***********************************************************************/
struct node_t {
    int v; int w;
    node_t(int v, int w): v(v), w(w) {}
};
inline ostream &operator << (ostream & os,const node_t& v) {
    return os << make_pair(v.v, v.w);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<node_t>> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }
    vector<int> xr(n, 0), vis(n, 0), a;
    function<void(int)> dfs = [&] (int u) {
        vis[u] = 1;
        for (const node_t& v: g[u]) {
            if (vis[v.v] == 2) continue;
            if (vis[v.v] == 1) {
                if (xr[v.v] ^ xr[u] ^ v.w)
                    a.push_back(xr[v.v] ^ xr[u] ^ v.w);
                continue;
            }
            xr[v.v] = v.w ^ xr[u];
            dfs(v.v);
        }
        vis[u] = 2;
    };
    dfs(0);
    sort(all(a));
    a.erase(unique(all(a)), a.end());
    vector<int> b;
    for (int i = 27; ~i; --i) {
        bool f = false;
        for (int &j: a) {
            if (j >> i & 1) {
                swap(j, a.back());
                f = true;
                break;
            }
        }
        if (not f) continue;
        b.push_back(a.back());
        a.pop_back();
        for (int &j: a) {
            if (j >> i & 1)
                j ^= b.back();
        }
    }
    int ans = xr[n - 1];
    for (int j: b) {
        ans = min(ans, ans ^ j);
    }
    cout << ans << '\n';

    return 0;
}
