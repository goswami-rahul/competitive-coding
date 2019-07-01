#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
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
template <typename T> void chkmax(T &x, T y) {if (y > x) x = y; }
template <typename T> void chkmin(T &x, T y) {if (y < x) x = y; }
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " =: " << a << "\n";
    // cerr << "\n";
	err(++it, args...);
}
template<class T1, class T2, class T3>
struct triple {
    T1 a; T2 b; T3 c;
    triple() : a(T1()), b(T2()), c(T3()) {};
    triple(T1 _a, T2 _b, T3 _c) :a(_a), b(_b), c(_c) {}
};
template<class T1, class T2, class T3>
bool operator<(const triple<T1,T2,T3>&t1,const triple<T1,T2,T3>&t2) {
    if(t1.a!=t2.a)return t1.a<t2.a;
    else if(t1.b!=t2.b)return t1.b<t2.b;
    else return t1.c<t2.c;
}
template <typename T1, typename T2>
inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p) {
    return os << "(" << p.first << ": " << p.second << ")";
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const std::vector<T>& v) {
    bool first = true;
    os << "[";
    for(unsigned int i = 0; i < v.size(); i++) {
        if(!first) os << ", ";
        os << v[i];
        first = false;
    }
    return os << "]";
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const std::set<T>& v) {
    bool first = true;
    os << "{";
    for (typename std::set<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii;
        first = false;
    }
    return os << "}";
}
template<typename T1, typename T2>
inline std::ostream &operator << (std::ostream & os,const std::map<T1, T2>& v) {
    bool first = true;
    os << "{";
    for (typename std::map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
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

void test_case(vector<ll>& vec) {
    int n = vec.size();
    // cin >> n;
    vector<ll> a;
    ll zero = 0, ones = 0;
    map<ll, int> cnt;
    for (int i = 0; i < n; ++i) {
        ll x = vec[i];
        // cin >> x;
        if (x == 0) zero++;
        else if (x == 1) ones++;
        else {
            a.push_back(x);
            cnt[x]++;
        }
    }
    ll ans = 0;
    if (zero >= 2) ans += (n - zero) * (zero * (zero - 1)) / 2LL;
    if (zero >= 3) ans += (zero * (zero - 1) * (zero - 2)) / 6LL;
    if (ones >= 3) ans += (ones * (ones - 1) * (ones - 2)) / 6LL;
    for (auto &pr : cnt) {
        ans += (ones * (pr.second * (pr.second - 1)) / 2);
    }
    // error(ans)
    n = (int) a.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (cnt.count(a[i] * a[j]))
                ans += (ll) cnt[a[i] * a[j]];
        }
    }
    cout << ans;
    error(ans)
}

void brute(vector<ll> &a) {
    ll ans = 0;
    int n = a.size();
    // error(a)
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (a[i] * a[j] == a[k] || a[i] * a[k] == a[j] || a[j] * a[k] == a[i]) {
                    ans++;
                }
            }
        }
    }
    cout << ans;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int tt = 1; tt <= T; ++tt) {
        cout << "Case #" << tt << ": ";
        int n;
        cin >> n;
        vector<ll> a(n);
        for (ll &e : a) cin >> e;
        // sort(all(a));
        // cout << "   (my) ";
        // brute(a);
        test_case(a);
        cout << el;
    }

    return 0;
}
