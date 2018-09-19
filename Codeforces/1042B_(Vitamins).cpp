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

    ll n;
    cin >> n;
    vector<ll> a(n);
    vector<string> s(n);
    map<string, ll> b;
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> s[i];
        sort(all(s[i]));
        if (b.count(s[i]))
            b[s[i]] = min(a[i], b[s[i]]);
        else
            b[s[i]] = a[i];
        if (s[i].size() == 3) {
            string c;
            c = "A";
            if (b.count(c))
                b[c] = min(a[i], b[c]);
            else
                b[c] = a[i];
            c = "B";
            if (b.count(c))
                b[c] = min(a[i], b[c]);
            else
                b[c] = a[i];
            c = "C";
            if (b.count(c))
                b[c] = min(a[i], b[c]);
            else
                b[c] = a[i];
            c = "AB";
            if (b.count(c))
                b[c] = min(a[i], b[c]);
            else
                b[c] = a[i];
            c = "AC";
            if (b.count(c))
                b[c] = min(a[i], b[c]);
            else
                b[c] = a[i];
            c = "BC";
            if (b.count(c))
                b[c] = min(a[i], b[c]);
            else
                b[c] = a[i];
        }
        if (s[i].size() == 2) {
            for (char c: s[i]) {
                string u(1, c);
                if (b.count(u))
                    b[u] = min(a[i], b[u]);
                else
                    b[u] = a[i];
            }
        }
    }
    ll ans = INF;
    if (b.count("A") && b.count("B") && b.count("C")) {
        ans = min(ans, b["A"] + b["B"] + b["C"]);
    }
    if (b.count("A") && b.count("BC")) {
        ans = min(ans, b["A"] + b["BC"]);
    }
    if (b.count("B") && b.count("AC")) {
        ans = min(ans, b["B"] + b["AC"]);
    }
    if (b.count("C") && b.count("AB")) {
        ans = min(ans, b["C"] + b["AB"]);
    }
    if (b.count("ABC")) {
        ans = min(ans, b["ABC"]);
    }
    if (ans == INF)
        ans = -1LL;
    cout << ans;

    return 0;
}
