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

    while (n--) {
        vector<pair<int, int>> a(4), c(4);
        for (int i = 0; i < 4; ++i)
            cin >> a[i].first >> a[i].second >> c[i].first >> c[i].second;

        auto rotate = [] (auto &p, auto x) -> void {
            p = make_pair(x.first - (p.second - x.second), x.second + p.first - x.first);
        };
        auto dist = [] (auto a, auto b) -> int {
            return (sqr(a.first - b.first) + sqr(a.second - b.second));
        };
        auto check = [dist] (auto a, auto b, auto c, auto d) -> bool {
            if (a == b || b == c || c == d || d == a || a == c || b == d)
                return false;
            int d1 = dist(a, b);
            int d2 = dist(a, c);
            int d3 = dist(a, d);
            if (d1 == d2) {
                return (d3 == d1 + d2 &&
                        dist(b, d) == dist(c, d) &&
                        dist(b, d) == d1);
            }
            if (d1 == d3) {
                return (d2 == d1 + d3 &&
                        dist(b, c) == dist(d, c) &&
                        dist(b, c) == d1);
            }
            if (d2 == d3) {
                return (d1 == d2 + d3 &&
                        dist(b, c) == dist(b, d) &&
                        dist(b, c) == d2);
            }
            return false;
        };
        int ans = MOD;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                for (int k = 0; k < 4; ++k) {
                    for (int p = 0; p < 4; ++p) {
                        if (check(a[0], a[1], a[2], a[3])) {
                            ans = min(ans, i + j + k + p);
                            // error(a, ans)
                        }
                        rotate(a[3], c[3]);
                    }
                    rotate(a[2], c[2]);
                }
                rotate(a[1], c[1]);
            }
            rotate(a[0], c[0]);
        }
        if (ans == MOD) ans = -1;
        cout << ans << el;
    }

    return 0;
}
