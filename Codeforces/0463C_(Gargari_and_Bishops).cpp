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
#define FOR(i, a, b) for(ll i=a; i<=b; i++)
#define RFOR(i, b, a) for(ll i=b; i>=a; i--)
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

/***********************************************************************/

int main()
{
    fio;
    ll t=1, T;
    ll i, j, x, y, n, m, k;
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    cin >> n;
    vector<vector<ll>> diag(2, vector<ll>(2 * n - 1, 0));
    ll a[n][n];
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j) {
            cin >> k;
            a[i][j] = k;
            diag[0][i + j] += k;
            diag[1][n - 1 + i - j] += k;
        }
    // error(diag);
    pair<ll, ll> coo[2];
    ll maxx[2] = {-1, -1};
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j) {
            ll val = diag[0][i + j];
            val += diag[1][n - 1 + i - j];
            val -= a[i][j];
            if (val > maxx[(i ^ j) & 1]) {
                maxx[(i ^ j) & 1] = val;
                coo[(i ^ j) & 1] = {i, j};
            }
        }
    cout << maxx[0] + maxx[1] << el;
    cout << coo[0].first + 1 << " " << coo[0].second + 1 << " ";
    cout << coo[1].first + 1 << " " << coo[1].second + 1;

    return 0;
}
