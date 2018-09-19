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
const double E = 1e-6;
/***********************************************************************/

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    ll d;
    cin >> d;
    vector<ll> a(n + 1, 0LL);
    for (int i = 0; i < n; ++i) {
        cin >> a[i + 1];
        a[i + 1] += a[i];
    }
    vector<vector<ll>> tree(4 * n);
    int errdent = 0;
    function<void(int, int, int)> build = [&]
    (int tl, int tr, int idx) {
        if (tl == tr) {
            tree[idx].push_back(a[tl]);
            return;
        }
        int m = (tl + tr) / 2;
        build(tl, m, 2 * idx);
        build(m + 1, tr, 2 * idx + 1);
        merge(all(tree[2 * idx]), all(tree[2 * idx + 1]), back_inserter(tree[idx]));
    };
    function<int(int, int, int, int, int, ll)> get = [&]
    (int L, int R, int idx, int tl, int tr, ll val) {
        if (L > R)
            return 0;
        if (L == tl && R == tr) {
            return (int) (lower_bound(all(tree[idx]), val) - tree[idx].begin());
        }
        int m = (tl + tr) / 2;
        int ret = get(L, min(R, m), idx * 2, tl, m, val);
        ret += get(max(L, m + 1), R, idx * 2 + 1, m + 1, tr, val);
        return ret;
    };
    build(1, n, 1);
    ll ans = 0LL;
    for (int L = 1; L <= n; ++L) {
        ans += (ll) get(L, n, 1, 1, n, a[L - 1] + d);
    }
    cout << ans;

    return 0;
}
