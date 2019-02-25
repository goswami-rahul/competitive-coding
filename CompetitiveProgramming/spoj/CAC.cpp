/*
 * It can easily seen that the answer is the product of the lengths
 * of all the edge-disjoint cycles. i.e. such cycles, in which no
 * vertex appears more than once. To count those cycles, lets
 * traverse the edges one by one, marking them as used if they were
 * a part of some cycle. Now, search a path from this edge's vertex
 * that ends on the same vertex **with no repeating vertex**. If
 * found such path, mark all the edges on the path as used, and
 * use the size of the path (cycle) to update the answer.
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

void err(__attribute__((unused)) istream_iterator<string> it) {}
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
    
    int tt, tno = 1;
    cin >> tt;
    while (tt--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> g(n), E(n, vector<int>(n, -1));
        vector<pair<int,int>> edges;
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u; --v;
            g[u].push_back(v);
            g[v].push_back(u);
            E[u][v] = E[v][u] = i;
            edges.emplace_back(u, v);
        }
        vector<bool> used(m, false);
        unsigned long long ans = 1;
        for (auto &edge: edges) {
            int id = E[edge.first][edge.second];
            if (used[id]) continue;
            vector<bool> mark(n, false);
            int source = edge.first;
            vector<pair<int,int>> buf = {edge};
            
            function<bool(int,int)> dfs = [&] (int u, int p) {
                mark[u] = true;
                for (int v: g[u]) {
                    if (v == p) continue;
                    if (mark[v]) continue;
                    if (v == source) {
                        buf.emplace_back(u, v);
                        return true;
                    }
                    if (used[E[u][v]]) continue;
                    buf.emplace_back(u, v);
                    if (dfs(v, u)) {
                        return true;
                    } else {
                        buf.pop_back();
                    }
                }
                mark[u] = false;
                return false;
            };
            dfs(edge.second, edge.first);
            for (auto e: buf) {
                int x = E[e.first][e.second];
                assert (!used[x]);
                used[x] = true;
            }
            ans *= buf.size();
        }
        cout << "Case " << tno++ << ": " << ans << '\n';
    }
    
    return 0;
}
