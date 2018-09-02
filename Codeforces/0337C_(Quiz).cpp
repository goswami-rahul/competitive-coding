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

const ll MOD = 1e9+9;
const ll INF = 1e18;
const double E = 1e-6;

/***********************************************************************/

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m, k, ans = 0;
    cin >> n >> m >> k;
    ans += n % k;
    m -= (n % k);
    n -= (n % k);
    if (m * k <= n * (k - 1)) {
        ans = (ans + m) % MOD;
        cout << ans;
        return 0;
    }
    ll p = m - (n / k * (k - 1));
    ans += (m - p * k);
    ans %= MOD;
    auto mul = [] (vector<vector<ll>> a, vector<vector<ll>> b) {
        int r = a.size(), c = b[0].size(), m = a[0].size();
        assert(m == b.size());
        vector<vector<ll>> res(r, vector<ll>(c, 0LL));
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                for (int k = 0; k < m; ++k) {
                    res[i][j] += a[i][k] * b[k][j];
                    res[i][j] %= MOD;
                }
        return res;
    };
    auto mpow = [mul] (vector<vector<ll>> base, ll ex) {
        vector<vector<ll>> res = {{1LL, 0LL}, {0LL, 1LL}};
        while (ex > 0) {
            if (ex & 1) res = mul(base, res);
            base = mul(base, base);
            ex >>= 1;
        }
        return res;
    };
    vector<vector<ll>> bmat = {{2, 1}, {0, 1}}, x = {{0LL}, {2 * k}}, a = mpow(bmat, p);
    vector<vector<ll>> res = mul(a, x);
    ans += res[0][0];
    ans %= MOD;
    cout << ans;

    return 0;
}
