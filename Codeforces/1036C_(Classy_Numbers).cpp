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

    ll n, m, k, T;
    auto val = [] (ll n, ll r) {
        ll ans = 1LL;
        if (r > n) r = n;
        if (r >= 1) ans += 9LL * n;
        if (r >= 2) ans += 81LL * n * (n - 1) / 2LL;
        if (r >= 3) ans += 729LL * n * (n - 1) * (n - 2) / 6LL;
        return ans;
    };
    function<ll(string, int)> solve = [&] (string s, int x) {
        int n = s.size();
        if (n == 0)
            return 0LL;
        ll ret = 0;
        int p = s[0] - '0';
        if (p == 0)
            return solve(s.substr(1, n - 1), x);
        if (x == 1) {
            s = to_string(stoll(s) - 1);
            n = s.size();
            ret =  (ll) (s[0] - '0') + (n - 1) * 9LL + 1LL;
        }
        else {
            ret += val(n - 1, x);
            p--;
            ret += (ll) p * val(n - 1, x - 1);
            ret += solve(s.substr(1, n - 1), x - 1);
        }
        return ret;
    };
    cin >> T;
    while (T--) {
        ll l, r;
        cin >> l >> r;
        string L = to_string(l), R = to_string(r + 1);
        cout << solve(R, 3) - solve(L, 3) << el;
    }

    return 0;
}
