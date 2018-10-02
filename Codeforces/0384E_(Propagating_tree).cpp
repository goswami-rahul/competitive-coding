#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
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

const int MOD = 1e9+7;
const ll INF = 1e18;
const double EPS = 1e-6;
/***********************************************************************/

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int &e : a) cin >> e;
    vector<vector<int>> tree(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    vector<int> depth(n), idx(n), altsize(n), par(n);
    vector<vector<int>> nodes(2, vector<int>(1, -1));
    function<int(int, int, int)> dfs = [&] (int u, int pa, int dep) {
        depth[u] = dep;
        idx[u] = nodes[dep & 1].size();
        nodes[dep & 1].push_back(a[u]);
        int total = 1;
        altsize[u] = 0;
        par[u] = pa;
        for (int v: tree[u]) {
            if (v == pa) continue;
            total += dfs(v, u, dep + 1);
            altsize[u] -= altsize[v];
        }
        altsize[u] += total;
        return total;
    };
    dfs(0, -1, 0);
    // init BIT
    for (int id = 0; id < 2; ++id) {
        for (int i = (int) nodes[id].size() - 1; i > 1; --i) {
            nodes[id][i] -= nodes[id][i - 1];
        }
        for (int i = 1; i < (int) nodes[id].size(); ++i) {
            if (i + (i & -i) < nodes[id].size())
                nodes[id][i + (i & -i)] += nodes[id][i];
        }
    }
    auto add = [&] (int u, int val) {
        int p = depth[u] & 1;
        for (int i = idx[u]; i <= (int) nodes[p].size(); i += i & -i)
            nodes[p][i] += val;
        for (int i = idx[u] + altsize[u]; i <= nodes[p].size(); i += i & -i)
            nodes[p][i] -= val;
    };

    auto get = [&] (int u) {
        int p = depth[u] & 1;
        int ret = 0;
        for (int i = idx[u]; i > 0; i -= i & -i)
            ret += nodes[p][i];
        return ret;
    };
    while (m--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, val;
            cin >> x >> val;
            --x;
            add(x, val);
            for (int v : tree[x])
                if (v != par[x])
                    add(v, -val);
        } else if (t == 2) {
            int x;
            cin >> x;
            --x;
            cout << get(x) << el;
        } else assert(false);
    }

    return 0;
}
