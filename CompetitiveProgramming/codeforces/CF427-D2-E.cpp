/*
 * The optimal position for police station is at the midpoint of
 * the array.
 * So, calculate the cost, when the police station is at midpoint
 * and print the answer.
 */
#include<bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

template<typename T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>; // find_by_order(), order_of_key()
using ll = long long int;
using i64 = long long int;
#define all(b) (b).begin(),(b).end()
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
inline std::ostream &operator << (std::ostream & os,const ordered_set<T>& v) {
    bool first = true;
    os << "{";
    for (auto ii = v.begin(); ii != v.end(); ++ii) {
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
const int MOD = 998244353;
const long long INF = 1e18;
const double EPS = 1e-6;
#define PI 3.14159265358979323846
#define sz(v) (int((v).size()))
/***********************************************************************/

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int &i: a) cin >> i;
    int pos = n / 2;
    int i = n - 1;
    int cap = 0;
    i64 ans = 0;
    while (a[pos] < a[i]) {
        if (cap == 0) {
            cap = m;
            ans += 2LL * (a[i] - a[pos]);
        }
        --cap;
        --i;
    }
    i = 0;
    cap = 0;
    while (a[i] < a[pos]) {
        if (cap == 0) {
            cap = m;
            ans += 2LL * (a[pos] - a[i]);
        }
        --cap;
        ++i;
    }
    cout << ans << '\n';
    
    return 0;
}
