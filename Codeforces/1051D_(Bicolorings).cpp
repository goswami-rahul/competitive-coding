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

    int n, k;
    cin >> n >> k;
    ll dp[2][2][n + 10][k + 10]; // B W n k

    FOR(i,0,1) FOR(j,0,1) FOR(m,0,n+2) FOR(l,0,k+4) {
        dp[i][j][m][l] = 0LL;
    }
    dp[0][0][1][1] = 1LL;
    dp[1][1][1][1] = 1LL;
    dp[1][0][1][2] = 1LL;
    dp[0][1][1][2] = 1LL;

    auto add = [] (ll &a, ll b) {
        a += b;
        a %= 998244353;
    };
    for (int in = 2; in <= n; ++in) {
        for (int ik = 1; ik <= k; ++ik) {
            if (ik - 1 >= 1) add(dp[1][1][in][ik], dp[0][0][in - 1][ik - 1]);
            add(dp[1][1][in][ik], dp[0][1][in - 1][ik]);
            add(dp[1][1][in][ik], dp[1][0][in - 1][ik]);
            add(dp[1][1][in][ik], dp[1][1][in - 1][ik]);

            add(dp[0][0][in][ik], dp[0][0][in - 1][ik]);
            add(dp[0][0][in][ik], dp[0][1][in - 1][ik]);
            add(dp[0][0][in][ik], dp[1][0][in - 1][ik]);
            if (ik - 1 >= 1) add(dp[0][0][in][ik], dp[1][1][in - 1][ik - 1]);

            if (ik - 1 >= 1) add(dp[0][1][in][ik], dp[0][0][in - 1][ik - 1]);
            add(dp[0][1][in][ik], dp[0][1][in - 1][ik]);
            if (ik - 2 >= 1) add(dp[0][1][in][ik], dp[1][0][in - 1][ik - 2]);
            if (ik - 1 >= 1) add(dp[0][1][in][ik], dp[1][1][in - 1][ik - 1]);

            if (ik - 1 >= 1) add(dp[1][0][in][ik], dp[0][0][in - 1][ik - 1]);
            if (ik - 2 >= 1) add(dp[1][0][in][ik], dp[0][1][in - 1][ik - 2]);
            add(dp[1][0][in][ik], dp[1][0][in - 1][ik]);
            if (ik - 1 >= 1) add(dp[1][0][in][ik], dp[1][1][in - 1][ik - 1]);
        }
    }
    ll ans = 0LL;
    FOR(i,0,1) FOR(j,0,1) {
        add(ans, dp[i][j][n][k]);
    }
    cout << ans;
    return 0;
}
