/*
 * for every repeated x coordinates, count their number and multiply
 * the number of ways that they can be arranged to the answer.
 * for duplicates, divide by 2 for each duplicate.
 */

#include<bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

template<typename T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>; // find_by_order(), order_of_key()
using ll = long long int;
using i64 = long long int;
#define all(vec) (vec).begin(),(vec).end()
template <typename T> inline void ckmax(T &x, T y) {if (y > x) x = y; }
template <typename T> inline void ckmin(T &x, T y) {if (y < x) x = y; }
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " =: " << a << endl;
    err(++it, args...);
}
template <typename T1, typename T2>
inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& buf) {
    return os << "(" << buf.first << ": " << buf.second << ")";
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
inline std::ostream &operator << (std::ostream & os,const std::multiset<T>& v) {
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
inline std::ostream &operator << (std::ostream & os,const vector<vector<T>>& v) {
    for (auto &u: v) os << '\n' << u;
    return os;
}
template<typename T>
void finish(T ans) {cout << ans << '\n'; exit(0);}
const int MOD = 1e9 + 7;
const long long INF = 1e18;
const double EPS = 1e-6;
#define PI 3.14159265358979323846
#define sz(v) (int((v).size()))
/***********************************************************************/
inline int add(int a, int b, int mod = MOD) {
    a += b;
    if (a >= mod) a -= mod;
    return a;
}
inline int sub(int a, int b, int mod = MOD) {
    a -= b;
    if (a < 0) a += mod;
    return a;
}
inline int mul(int a, int b, int mod = MOD) {
    return (long long) a * b % mod;
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
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    map<int,int> cnt;
    for (auto &i: a) cin >> i, cnt[i]++;
    for (auto &i: b) cin >> i, cnt[i]++;
    int m;
    cin >> m;
    int rep = 0;
    for (int i = 0; i < n; ++i) rep += (a[i] == b[i]);
    int ans = 1;
    for (auto [val, c]: cnt) {
        if (c > 1) {
            for (int i = c; i > 1; --i) {
                int p = i;
                while (rep > 0 && p % 2 == 0) p /= 2, rep--;
                ans = (i64) ans * p % m;
            }
        }
    }
    cout << ans << '\n';
    
    return 0;
}
