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
#define point complex<ll>
#define line pair<point, point>

ll cross(const point &a, const point &b) {
    return imag(conj(a) * b);
}
inline bool inside(const point &p, const line &l) {
    ll x1 = l.first.real(), x2 = l.second.real();
    ll y1 = l.first.imag(), y2 = l.second.imag();
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);
    return (x1 <= p.real() && p.real() <= x2 && y1 <= p.imag() && p.imag() <= y2);
}
pair<bool, point> intersect(const line &l1, const line &l2) {
    point a = l1.first, b = l1.second, p = l2.first, q = l2.second;
    ll d1 = cross(p - a, b - a);
    ll d2 = cross(q - a, b - a);
    point s = (d1 * q - d2 * p);
    if ((d1 == d2) || s.real() % abs(d1 - d2) || s.imag() % abs(d1 - d2))
        return make_pair(false, point());
    s /= (d1 - d2);
    return make_pair((inside(s, l1) && inside(s, l2)), s);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<line> a(n);
    ll p1, p2, p3, p4, ans = 0;

    auto cmp = [] (const point &a, const point &b) -> bool {
        return (bool) (mp(a.real(), a.imag()) < mp(b.real(), b.imag()));
    };
    set<point, decltype(cmp)> points(cmp), temp(cmp);
    for (int i = 0; i < n; ++i) {
        cin >> p1 >> p2 >> p3 >> p4;
        a[i].first = point(p1, p2);
        a[i].second = point(p3, p4);
        ll g = __gcd(abs(p1 - p3), abs(p2 - p4));
        ans += g + 1;
        temp.clear();
        for (int j = 0; j < i; ++j) {
            bool ok; point x;
            tie(ok, x) = intersect(a[i], a[j]);
            if (ok) temp.insert(x);
        }
        for (auto e: temp) {
            if (points.count(e)) ans--;
            else points.insert(e);
        }
    }
    cout << ans - points.size();

    return 0;
}
