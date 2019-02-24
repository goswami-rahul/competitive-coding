/*
the problem involved graphs and dijstra algorithm, but the crux of the problem
is minimizing the equation [t + v * (a ^ t)]. To get the formula,
differentiate it to get the minima t = log(v log(a)) / log(a)
also check if t < 0, in case it is, set t = 0;
*/
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
    int x, id;
    double v, a;
    node_t() {};
    node_t(int id, int x, double v, double a): id(id), x(x), v(v), a(a) {};
};
template <typename T>
using pq_greater = priority_queue<T, vector<T>, greater<T>>;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const double inf = 1 / 0.0;
    assert(inf - 100 == inf + 100);
    cout << fixed << setprecision(3);
    while (true) {
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0) break;
        vector<vector<node_t>> g(n);
        for (int i = 0; i < m; ++i) {
            int x, y;
            double v, a;
            cin >> x >> y >> v >> a;
            --x; --y;
            g[x].emplace_back(i, y, v, a);
            g[y].emplace_back(i, x, v, a);
        }
        double ans = inf;
        for (int i = 0; i < m; ++i) {
            // repair ith road
            pq_greater<pair<double,int>> pq;
            pq.emplace(0.0, 0);
            vector<double> dis(n, inf);
            vector<bool> mark(n, false);
            dis[0] = 0.0;
            while(!pq.empty()) {
                const auto e = pq.top(); pq.pop();
                int u = e.second;
                if (mark[u]) continue;
                mark[u] = true;
                for (node_t v: g[u]) {
                    double cost = v.v;
                    if (v.id == i) {
                        cost *= pow(v.a, -dis[u]);
                        double t = log(cost * log(v.a)) / log(v.a);
                        if (t > 0)
                            cost = cost * pow(v.a, -t) + t;
                    }
                    cost += dis[u];
                    if (cost < dis[v.x]) {
                        dis[v.x] = cost;
                        pq.emplace(cost, v.x);
                    }
                }
            }
            ans = min(ans, dis[n - 1]);
        }
        cout << ans << '\n';
    }

    return 0;
}
