/*
 * The problem requires to find the nodes whch can reach a negative cycle
 * in the directed graph. So, first find the connected components, then
 * for each component, check for negative cycle using Bellman Ford.
 * Make a condensed DAG with the connected components with reverse edges,
 * And find the connected components reachable from those with a cycle;
 * Finally, print the vertices in all such components.
 */
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define SZ(v) (int((v).size()))
#define ALL(vec) (vec).begin(),(vec).end()
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
using namespace std;
 
template<typename T, typename V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<T, V, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>; // find_by_order(), order_of_key()
using ll = long long int;
using i64 = long long int;
template <typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template <typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " =: " << a << endl;
    err(++it, args...);
}
template <typename T1, typename T2>
inline ostream& operator << (ostream& os, const pair<T1, T2>& buf) {
    return os << "(" << buf.first << ": " << buf.second << ")";
}
template<typename T>
inline ostream &operator << (ostream & os,const vector<T>& v) {
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
inline ostream &operator << (ostream & os,const set<T>& v) {
    bool first = true;
    os << "{";
    for (auto ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii;
        first = false;
    }
    return os << "}";
}
inline ostream &operator << (ostream & os,const multiset<pair<int,int>>& v) {
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
inline ostream &operator << (ostream & os,const map<T1, T2>& v) {
    bool first = true;
    os << "{";
    for (typename map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii ;
        first = false;
        return os << "}";
    }
}
template<typename T>
inline ostream &operator << (ostream & os,const vector<vector<T>>& v) {
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
    
    int tt;
    cin >> tt;
    for (int tnt = 1; tnt <= tt; ++tnt) {
        int n, m; cin >> n >> m;
        vector<vector<pair<int,int>>> g(n);
        vector<vector<int>> r(n);
        map<pair<int,int>,int> edge;
        for (int i = 0; i < m; ++i) {
            int u, v, w; cin >> u >> v >> w;
            if (edge.count({u, v})) uin(edge[{u, v}], w);
            edge[{u, v}] = w;
        }
        for (auto &e: edge) {
            int u, v, w;
            tie(u, v) = e.first;
            w = e.second;
            g[u].emplace_back(v, w);
            r[v].push_back(u);
        }
        vector<int> order, vis;
        function<void(int)> dfs1 = [&] (int u) {
            vis[u] = true;
            for (auto e: g[u]) {
                int v, w; tie(v, w) = e;
                if (!vis[v]) dfs1(v);
            }
            order.push_back(u);
        };
        vis.assign(n, false);
        for (int i = 0; i < n; ++i) {
            if (!vis[i]) dfs1(i);
        }
        reverse(ALL(order));
        int t = 0;
        vector<int> cc, cid(n, -1);
        function<void(int)> dfs2 = [&] (int u) {
            cc.push_back(u);
            cid[u] = t;
            for (int v: r[u]) {
                if (cid[v] == -1) dfs2(v);
            }
        };
        vector<vector<int>> ccs;
        for (int u: order) {
            if (cid[u] == -1) {
                dfs2(u);
                ++t;
                ccs.push_back({});
                swap(ccs.back(), cc);
            }
        }
        vector<vector<int>> R(t); // condensed reversed graph
        for (int i = 0; i < t; ++i) {
            set<int> in;
            for (int u: ccs[i]) {
                for (int v: r[u]) in.insert(cid[v]);
            }
            in.erase(i);
            for (int x: in) R[i].push_back(x);
        }
        vis.assign(t, false);
        function<void(int)> dfs3 = [&] (int u) {
            vis[u] = true;
            for (int v: R[u]) {
                if (!vis[v]) dfs3(v);
            }
        };
        vector<vector<pair<int,int>>> ccg(n);
        for (int i = 0; i < n; ++i) {
            for (auto &e: g[i]) {
                if (cid[e.first] == cid[i])
                    ccg[i].push_back(e);
            }
        }
        for (int i = 0; i < t; ++i) {
            bool has_cycle = false;
            const auto &cc = ccs[i];
            int sz = SZ(cc);
            
            vector<int> dis(n, 0);
            bool relax = true;
            for (int j = 0; relax; ++j) {
                if (j == sz) {
                    has_cycle = true;
                    break;
                }
                relax = false;
                for (int u: cc) {
                    for (auto &e: ccg[u]) {
                        int v, w; tie(v, w) = e;
                        relax |= uin(dis[v], w + dis[u]);
                    }
                }
            }
            if (has_cycle) dfs3(i);
        }
        vector<int> ans;
        for (int i = 0; i < t; ++i)
            if (vis[i]) ans.insert(ans.end(), ALL(ccs[i]));
        sort(ALL(ans));
        cout << "Case " << tnt << ":";
        if (ans.empty()) cout << " impossible";
        for (int x: ans) {
            cout << ' ' << x;
        }
        cout << '\n';
    }
    
    return 0;
}
