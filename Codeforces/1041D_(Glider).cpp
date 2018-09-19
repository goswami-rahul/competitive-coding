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
    ll h;
    cin >> n >> h;
    vector<ll> csum(n + 1, 0LL);
    vector<pair<ll, ll>> a(n);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i - 1].first >> a[i - 1].second;
        csum[i] = a[i - 1].second - a[i - 1].first + csum[i - 1];
    }
    auto geth = [&] (ll L, ll R) -> ll {
        int l = lower_bound(all(a), mp(L, INF)) - a.begin();
        int r = lower_bound(all(a), mp(R, INF)) - a.begin();
        ll res = csum[r - 1] - csum[l];
        res += max(0LL, a[l - 1].second - L);
        res += min(a[r - 1].second, R) - a[r - 1].first;
        return res + h - (R - L);
    };
    ll ans = -1LL;
    for (int i = 0; i < n; ++i) {
        ll x = a[i].first;
        ll hi = 1e10, lo = x;
        ll mid;
        while (lo < hi) {
            mid = (lo + hi + 1) / 2;
            ll hh = geth(x, mid);
            if (hh > 0) {
                lo = mid;
            }
            else {
                hi = mid - 1;
            }
        }
        assert(lo == hi);
        ans = max(ans, hi - x + 1);
    }
    cout << ans;

    return 0;
}
