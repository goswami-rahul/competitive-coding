/*
 * We binary search on the position x such that, if we drop
 * the first passenger on bus at x, then he and the last
 * passenger reach at the destination at the exact same time.
 * If we find such x, it is optimal to always drop the first
 * person at x, and the answer will be the time for x distance
 * using bus, and the rest on foot.
 */
#include<bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
template<typename T, typename V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<T, V, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>; // find_by_order(), order_of_key()
using ll = long long int;
using i64 = long long int;
#define SZ(v) (int((v).size()))
#define ALL(vec) (vec).begin(),(vec).end()
template<typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template<typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}

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
inline std::ostream &operator << (std::ostream & os,const set<T>& v) {
    bool first = true;
    os << "{";
    for (auto ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii;
        first = false;
    }
    return os << "}";
}
inline std::ostream &operator << (std::ostream & os,const std::multiset<pair<int,int>,greater<pair<int,int>>>& v) {
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
inline std::ostream &operator << (std::ostream & os,const std::map<T1, T2>& v) {
    bool first = true;
    os << "{";
    for (typename std::map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii ;
        first = false;
        return os << "}";
    }
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
/***********************************************************************/
inline bool f(long double x, int v1, int v2, int m, int d) {
    long double p = 0;
    for (int i = 0; i < m - 1; ++i) {
        p += 2 * (x - p) * v1 / (v1 + v2);
        x += (x - p) * v1 / v2;
        x = (x * v2 - p * v1) / (v2 - v1);
    }
    return x >= d;
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout << fixed; cout.precision(10);
    
    int n, d, v1, v2, k;
    cin >> n >> d >> v1 >> v2 >> k;
    long double lo = 0, hi = d;
    int m = (n + k - 1) / k;
    for (int iter = 0; iter < 200; ++iter) {
        long double mid = (lo + hi) / 2.0;
        if (f(mid, v1, v2, m, d)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    long double ans = lo / v2 + (d - lo) / v1;
    cout << ans << '\n';
    
    return 0;
}
