/*
The problem requires to find the cycle with smallest number of vertices in the given graph.
Process every edge one by one, and find the shortest distance between the 2
endpoints of this edge without considering this edge. The minimum cycle
containing this edge is 1 + shortest distance.
Minimize the answer after each step.
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

template<typename T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
#define ll long long int
#define el "\n"
#define sqr(x) ((x) * (x))
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
inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p) {
    return os << "(" << p.first << ": " << p.second << ")";
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
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tt;
    cin >> tt;
    for (int t = 1; t <= tt; ++t) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> g(n);
        vector<pair<int,int>> edges;
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            edges.push_back(make_pair(u, v));
            g[u].push_back(v);
            g[v].push_back(u);
        }
        int ans = MOD;
        for (auto e: edges) {
            int u = e.first, v = e.second;
            vector<int> dis(n, -1);
            queue<int> que;
            dis[u] = 0;
            que.push(u);
            bool ok = false;
            while (!que.empty() && !ok) {
                int x = que.front(); que.pop();
                for (int y: g[x]) {
                    if (x == u && y == v) continue;
                    if (y == v) {
                        ans = min(ans, 2 + dis[x]);
                        ok = true;
                        break;
                    }
                    if (dis[y] == -1) {
                        dis[y] = 1 + dis[x];
                        que.push(y);
                    }
                }
            }
        }
        cout << "Case " << t << ": ";
        if (ans == MOD) cout << "impossible\n";
        else cout << ans << '\n';
    }

    return 0;
}
