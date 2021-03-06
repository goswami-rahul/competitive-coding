/*
 * First observation is that the number of paints at each column
 * remain the same as the first square.
 * The solve the answer using DP.
 * My solution was similar to this editorial https://codeforces.com/blog/entry/5514
 */
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define SZ(v) (int((v).size()))
#define ALL(vec) (vec).begin(),(vec).end()
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
using namespace std;
 
template<typename T, typename V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<T, V, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>; // find_by_order(), order_of_key()
using ll = long long int;
using i64 = long long int;
template <typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template <typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}

void err(__attribute__((unused)) istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " =: " << a << endl;
    err(++it, args...);
}
template <typename T1, typename T2>
inline ostream& operator << (ostream& os, const pair<T1, T2>& buf) {
    return os << "(" << buf.first << ": " << buf.second << ")";
}
template<typename T>
inline ostream &operator << (ostream & os,const vector<T>& v) {
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
inline ostream &operator << (ostream & os,const set<T>& v) {
    bool first = true;
    os << "{";
    for (auto ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii;
        first = false;
    }
    return os << "}";
}
inline ostream &operator << (ostream & os,const multiset<pair<int,int>>& v) {
    bool first = true;
    os << "{";
    for (auto x: v) {
        if(!first) os << ", ";
        os << x;
        first = false;
    }
    return os << "}";
}
template<typename T1, typename T2>
inline ostream &operator << (ostream & os,const map<T1, T2>& v) {
    bool first = true;
    os << "{";
    for (typename map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii ;
        first = false;
        return os << "}";
    }
}
template<typename T>
inline ostream &operator << (ostream & os,const vector<vector<T>>& v) {
    for (auto &u: v) os << '\n' << u;
    return os;
}
template<typename T>
void finish(T ans) {cout << ans << '\n'; exit(0);}
const int MOD = 1e9 + 7;
const long long INF = 1e18;
const double EPS = 1e-6;
#define PI 3.14159265358979323846
/***********************************************************************/
inline int add(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}
inline int sub(int a, int b) {
    a -= b;
    if (a < 0) a += MOD;
    return a;
}
inline int mul(int a, int b) {
    return (long long) a * b % MOD;
}
inline int mpow(int base, long long ex, int mod = MOD) {
    int res = 1;
    while (ex > 0) {
        if (ex & 1) res = (long long) res * base % mod;
        base = (long long) base * base % mod;
        ex >>= 1;
    }
    return res;
}
inline int inv(int a, int mod = MOD) {
    return mpow(a, mod - 2, mod);
}
vector<int> fac, ifac;
inline int ncr(int n, int r) {
    if (n < r) return 0;
    return mul(fac[n], mul(ifac[n - r], ifac[r]));
}
void init_fac(int nax = 1e6 + 10) {
    fac.resize(nax);
    ifac.resize(nax);
    fac[0] = 1;
    for (int i = 1; i < nax; ++i) fac[i] = mul(i, fac[i - 1]);
    ifac[nax - 1] = inv(fac[nax - 1]);
    for (int i = nax - 1; i > 0; --i) ifac[i - 1] = mul(i, ifac[i]);
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    init_fac(200);
    int n, k; i64 m;
    cin >> n >> m >> k;

    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        i64 freq = m / n + (i <= m % n);
        for (int j = 0; j <= n && j <= k; ++j) {
            int x = mpow(ncr(n, j), freq);
            for (int p = j; p <= k; ++p) {
                int y = mul(x, dp[i - 1][p - j]);
                dp[i][p] = add(dp[i][p], y);
            }
        }
    }
    cout << dp[n][k] << '\n';
    
    return 0;
}
