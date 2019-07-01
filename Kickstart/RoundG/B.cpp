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

void test_case() {
    int n, q;
    cin >> n >> q;
    vector<ll> X(n + 1), Y(n + 1), Z(q + 1), L(n), R(n);
    ll a, b, c, m;

    cin >> X[0] >> X[1] >> a >> b >> c >> m;
    for (int i = 2; i < n; ++i)
        X[i] = (a * X[i - 1] + b * X[i - 2] + c) % m;

    cin >> Y[0] >> Y[1] >> a >> b >> c >> m;
    for (int i = 2; i < n; ++i)
        Y[i] = (a * Y[i - 1] + b * Y[i - 2] + c) % m;

    cin >> Z[0] >> Z[1] >> a >> b >> c >> m;
    for (int i = 2; i < q; ++i)
        Z[i] = (a * Z[i - 1] + b * Z[i - 2] + c) % m;

    for (int i = 0; i < n; ++i) {
        L[i] = -(max(X[i], Y[i]) + 1);
        R[i] = -(min(X[i], Y[i]) + 1);
    }

    map<ll, ll> cum;
    for (int i = 0; i < n; ++i) {
        cum[L[i]]++;
        cum[R[i] + 1]--;
    }
    vector<ll> arr;
    vector<ll> freq, siz, cumsiz;
    arr.push_back(-INF);
    freq.push_back(0);
    siz.push_back(0);
    cumsiz.push_back(0);
    ll cur = 0, pre = -1;
    for (auto &e : cum) {
        if (e.second == 0) continue;
        if (cur == 0) {
            pre = e.first;
            cur += e.second;
            continue;
        }
        arr.push_back(pre);
        freq.push_back(cur);
        siz.push_back(cur * (e.first - pre));
        cumsiz.push_back(cumsiz.back() + siz.back());
        pre = e.first;
        cur += e.second;
    }
    ll ans = 0;
    // cerr << el;
    // error(arr, freq, siz, cumsiz)
    for (ll i = 1; i <= q; ++i) {
        int k = Z[i - 1];
        int p = (int) (upper_bound(all(cumsiz), k) - cumsiz.begin());
        // error(k, p)
        if (p == arr.size()) continue;
        assert(p < arr.size());
        ll idx = (k - cumsiz[p - 1]) / freq[p];
        // error(k, p, idx)
        ans += i * (arr[p] + idx);
    }
    cout << -ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int tt = 1; tt <= T; ++tt) {
        cout << "Case #" << tt << ": ";
        test_case();
        cout << el;
        cerr << "Case " << tt << " solved!" << endl;
    }

    return 0;
}
