#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define vi vector< int >
#define vl vector< ll >
#define pii pair< int, int >
#define pll pair< ll , ll >
#define pdd pair< double, double >
#define vii vector< pii >
#define vll vector< pll >
#define vd vector< double >
#define vb vector< bool >
#define el "\n"
#define ull unsigned long long int
#define ld long double
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define sqr(x) ((x) * (x))
#define FOR(i, a, b) for(ll i=a; i<=b; i++)
#define RFOR(i, b, a) for(ll i=b; i>=a; i--)
#define all(vec) (vec).begin(),(vec).end()

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " =: " << a << "\n";
    // cerr << "\n";
	err(++it, args...);
}
template<class T1, class T2, class T3>
struct triple {
    T1 a; T2 b; T3 c;
    triple() : a(T1()), b(T2()), c(T3()) {};
    triple(T1 _a, T2 _b, T3 _c) :a(_a), b(_b), c(_c) {}
};
template<class T1, class T2, class T3>
bool operator<(const triple<T1,T2,T3>&t1,const triple<T1,T2,T3>&t2) {
    if(t1.a!=t2.a)return t1.a<t2.a;
    else if(t1.b!=t2.b)return t1.b<t2.b;
    else return t1.c<t2.c;
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
template<typename T1, typename T2>
inline std::ostream &operator << (std::ostream & os,const std::unordered_map<T1, T2>& v) {
    return os << std::map<T1, T2>(v.begin(), v.end());
}

const ll MOD = 1e9+7;
const ll INF = 1e18;
const double EPS = 1e-6;
/***********************************************************************/

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T = 1;
    // cin >> T;
    while (T--) {
        int n, q, m;
        cin >> n >> m;
        vector<vector<pair<ll, int>>> g(n);
        set<pair<ll, pair<int, int>>> bad_edges;
        for (int i = 0; i < m; ++i) {
            ll u, v, w;
            cin >> u >> v >> w;
            --u, --v;
            g[u].emplace_back(w, v);
            g[v].emplace_back(w, u);
            if (u > v) swap(u, v);
            bad_edges.emplace(w, make_pair(u, v));
        }
        vector<bool> vis(n, false);
        vector<ll> distree(n, -1LL), depth(n);
        const int LOGN = (int) ceil(log2(n)) + 5;
        vector<vector<int>> par(n, vector<int>(LOGN, -1));

        function<void(int, int, ll, int)> make_tree = [&] (int s, int pa, ll dis, int dep) {
            vis[s] = true;
            distree[s] = dis;
            depth[s] = dep;
            par[s][0] = pa;
            vis[s] = true;
            for (int i = 1; i < LOGN; ++i)
                if (par[s][i - 1] != -1)
                    par[s][i] = par[par[s][i - 1]][i - 1];
            for (auto d: g[s]) {
                if (vis[d.second])
                    continue;
                int a = s, b = d.second;
                if (a > b) swap(a, b);
                assert(bad_edges.count(make_pair(d.first, make_pair(a, b))));
                bad_edges.erase(make_pair(d.first, make_pair(a, b)));
                make_tree(d.second, s, dis + d.first, dep + 1);
            }
        };
        make_tree(0, -1, 0, 0);
        function<int(int, int)> lca = [&] (int a, int b) {
            if (depth[b] < depth[a])
                swap(a, b);
            for (int i = LOGN - 1; i >= 0; --i)
                if (par[b][i] != -1 && depth[par[b][i]] >= depth[a])
                    b = par[b][i];
            assert(depth[a] == depth[b]);
            if (a == b)
                return a;
            for (int i = LOGN - 1; i >= 0; --i)
                if (par[a][i] != par[b][i])
                    a = par[a][i], b = par[b][i];
            assert(par[a][0] == par[b][0]);
            return par[a][0];
        };
        vector<vector<ll>> disdij(n);
        function<void(int)> make_dij = [&] (int s) {
            if (!disdij[s].empty()) return;
            disdij[s] = vector<ll>(n, INF);
            set<pair<ll, int>> pq;
            disdij[s][s] = 0LL;
            pq.insert({0LL, s});
            while (!pq.empty()) {
                int v;
                ll w;
                tie(w, v) = *pq.begin(); pq.erase(pq.begin());
                for (auto e: g[v]) {
                    if (w + e.first < disdij[s][e.second]) {
                        pq.erase({disdij[s][e.second], e.second});
                        disdij[s][e.second] = w + e.first;
                        pq.emplace(disdij[s][e.second], e.second);
                    }
                }
            }
        };
        for (auto &pe: bad_edges) {
            auto e = pe.second;
            make_dij(e.first);
            make_dij(e.second);
        }

        assert(m - bad_edges.size() == n - 1);
        cin >> q;
        while (q--) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            ll ans = distree[u] + distree[v] - 2LL * distree[lca(u, v)];
            for (auto &pe: bad_edges) {
                auto e = pe.second;
                ans = min(ans, disdij[e.first][u] + disdij[e.first][v]);
                ans = min(ans, disdij[e.second][u] + disdij[e.second][v]);
            }
            cout << ans << el;
        }
    }

    return 0;
}
