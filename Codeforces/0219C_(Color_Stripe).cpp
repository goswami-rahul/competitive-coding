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
const double E=1e-6;

/***********************************************************************/
ll modpow(ll base, ll e, ll M) {
  ll res = 1;
  base %= M;
  while (e > 0) {
    if (e & 1) res = (res * base) % M;
    e >>= 1;
    base = (base * base) % M;
  }
  return res;
}

int main()
{
    fio;
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    if (k == 2) {
        string tema(n, '.'), temb(n, '.');
        int a = 0, b = 0;
        for (int i = 0; i < n; i++) {
            tema[i] = "AB"[i&1];
            temb[i] = "BA"[i&1];
            a += (s[i] != tema[i]);
            b += (s[i] != temb[i]);
        }
        if (a < b) cout << a << el << tema;
        else cout << b << el << temb;
        return 0;
    }
    int ans = 0;
    s.push_back('*');
    for (int i = 1; i < n; ++i) {
        if (s[i] == s[i - 1]) {
            for (int j = 0; j < 3; ++j) {
                s[i] = (char) (j + 'A');
                if (s[i] == s[i - 1] || s[i] == s[i + 1]) continue;
                break;
            }
            ans++;
        }
    }
    s.pop_back();
    cout << ans << el << s;

    return 0;
}
