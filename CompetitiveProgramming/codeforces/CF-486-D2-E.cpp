/*
 * First find f1_i and f2_i for each i, f1 is lis ending at ith position
 * f2 is lis starting at ith position
 * then if f1_i + f2_i - 1 == LIS, then only ith elemnet is in the LIS
 * the elements with unique f1_i or f2_i are in every LIS.
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
const int MOD = 1e9 + 7;
const long long INF = 1e18;
const double EPS = 1e-6;
#define PI 3.14159265358979323846
#define sz(v) (int((v).size()))
/***********************************************************************/

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &i: a) cin >> i;
    vector<int> f1(n), f2(n), seq(n + 1, MOD);
    for (int i = 0; i < n; ++i) {
        int x = a[i];
        int p = lower_bound(all(seq), x) - seq.begin();
        seq[p] = x;
        f1[i] = p + 1;
    }
    int lis = (int) (lower_bound(all(seq), MOD) - seq.begin());
    seq.assign(n + 1, MOD);
    for (int i = n - 1; i >= 0; --i) {
        int x = -a[i];
        int p = lower_bound(all(seq), x) - seq.begin();
        seq[p] = x;
        f2[i] = p + 1;
    }
    vector<int> cnt(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        if (f1[i] + f2[i] - 1 == lis) {
            cnt[f1[i]]++;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (f1[i] + f2[i] - 1 == lis) {
            if (cnt[f1[i]] == 1) cout << 3;
            else cout << 2;
        } else cout << 1;
    }
    cout << '\n';
    
    return 0;
}
