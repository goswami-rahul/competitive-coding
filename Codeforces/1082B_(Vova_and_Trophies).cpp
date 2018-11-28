#include<bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

template<typename T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
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
template<typename T>
inline std::ostream &operator << (std::ostream & os,const std::multiset<T,greater<T>>& v) {
    return os << std::vector<T>(v.begin(), v.end());
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const ordered_set<T>& v) {
    return os << std::set<T>(v.begin(), v.end());
}
template<typename T1, typename T2>
inline std::ostream &operator << (std::ostream & os,const std::unordered_map<T1, T2>& v) {
    return os << std::map<T1, T2>(v.begin(), v.end());
}

const int MOD = 1e9 + 7;
const long long INF = 1e18;
const double EPS = 1e-6;
/***********************************************************************/
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> a(n, 0);
    int i2 = -1, i1 = -1;
    a[0] = (s[0] == 'G');
    if (a[0]) i2 = 0;
    int ans = a[0];
    for (int i = 1; i < n; ++i) {
        if (s[i] == 'G') {
            a[i] = a[i - 1] + 1;
            i2 = i;
        }
        ans = max(ans, a[i]);
    }
    vector<int> b(n, 0);
    b[n - 1] = (s[n - 1] == 'G');
    if (b[n - 1]) i1 = n - 1;
    for (int i = n - 2; i >= 0; --i) {
        if (s[i] == 'G') {
            b[i] = b[i + 1] + 1;
            i1 = i;
        }
        ans = max(ans, b[i]);
    }
    if (i1 == -1) {
        cout << 0 << '\n';
        return 0;
    }
    if (s[0] == 'S') {
        swap(s[0], s[i2]);
        vector<int> x(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            if (s[i - 1] == 'G') {
                x[i] = x[i - 1] + 1;
            }
            ans = max(ans, x[i]);
        }
        swap(s[0], s[i2]);
    }
    if (s[n - 1] == 'S') {
        swap(s[n - 1], s[i1]);
        vector<int> x(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            if (s[i - 1] == 'G') {
                x[i] = x[i - 1] + 1;
            }
            ans = max(ans, x[i]);
        }
        swap(s[n - 1], s[i1]);
    }
    for (int i = 1; i < n - 1; ++i) {
        if (s[i] == 'S') {
            if (a[i - 1] + b[i + 1] + 1 > ans) {
                ans = max(ans, a[i - 1] + b[i + 1]);
                if (i1 + b[i1] - 1 < i - 1) {
                    ans = max(ans, a[i - 1] + b[i + 1] + 1);
                }
                if (i2 - a[i2] + 1 > i + 1) {
                    ans = max(ans, a[i - 1] + b[i + 1] + 1);
                }
            }
        }
    }
    cout << ans << '\n';

    return 0;
}
