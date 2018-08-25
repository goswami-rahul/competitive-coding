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
#define fio ios_base::sync_with_stdio(false),cin.tie(NULL)
#define ull unsigned long long int
#define ld long double
#define F first
#define S second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define FOR(i, a, b) for(int i=a; i<=b; i++)
#define RFOR(i, b, a) for(int i=b; i>=a; i--)
#define all(vec) (vec).begin(),(vec).end()
#define rall(vec) (vec).rbegin(),(vec).rend()

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " =: " << a << "\n";
    // cerr << "\n";
	err(++it, args...);
}

template <typename T1, typename T2>
inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p)
{
    return os << "(" << p.first << ": " << p.second << ")";
}

template<typename T>
inline std::ostream &operator << (std::ostream & os,const std::vector<T>& v)
{
    bool first = true;
    os << "[";
    for(unsigned int i = 0; i < v.size(); i++)
    {
        if(!first)
            os << ", ";
        os << v[i];
        first = false;
    }
    return os << "]";
}

template<typename T>
inline std::ostream &operator << (std::ostream & os,const std::set<T>& v)
{
    bool first = true;
    os << "{";
    for (typename std::set<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        if(!first)
            os << ", ";
        os << *ii;
        first = false;
    }
    return os << "}";
}

template<typename T1, typename T2>
inline std::ostream &operator << (std::ostream & os,const std::map<T1, T2>& v)
{
    bool first = true;
    os << "{";
    for (typename std::map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        if(!first)
            os << ", ";
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
const double PI = 4.0 * atan(1.0);

/***********************************************************/

int main()
{
    fio;
    ll n, x, y, m, k, d, T;
    cin >> n;
    vector<ll> cost(n);
    for (int i = 0; i < n; ++i) cin >> cost[i];
    cin >> m;
    vector<vector<int>> g(n), r(n);
    while (m--) {
        cin >> x >> y;
        g[x - 1].push_back(y - 1);
        r[y - 1].push_back(x - 1);
    }
    vector<bool> vis(n, false);
    vector<int> nodes;
    function<void(int)> dfs1 = [&] (int s) {
        vis[s] = true;
        for (int &e: g[s]) {
            if (vis[e]) continue;
            dfs1(e);
        }
        nodes.push_back(s);
    };
    for (int i = 0; i < n; ++i)
        if (!vis[i]) dfs1(i);

    fill(all(vis), false);
    ll mincnt, mincost;
    function<void(int)> dfs2 = [&] (int s) {
        vis[s] = true;
        if (mincost == cost[s]) mincnt++;
        else if (cost[s] < mincost) {
            mincost = cost[s];
            mincnt = 1;
        }
        for (int &e: r[s]) {
            if (vis[e]) continue;
            dfs2(e);
        }
    };
    ll ans = 0LL, ways = 1LL;
    while (!nodes.empty()) {
        int source = nodes.back();
        nodes.pop_back();
        if (vis[source]) continue;
        mincnt = -1, mincost = INF;
        dfs2(source);
        ans += mincost;
        ways *= mincnt;
        ways %= MOD;
    }
    cout << ans << " " << ways;

    return 0;
}
