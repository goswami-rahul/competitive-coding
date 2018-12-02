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
inline std::ostream &operator << (std::ostream & os,const vector<vector<T>>& v) {
    os << '\n';
    for (auto &u: v) os << u << '\n';
    return os;
}

const int MOD = 1e9 + 7;
const long long INF = 1e18;
const double EPS = 1e-6;
/***********************************************************************/
template<typename T>
struct sparse_table {
    function<T(T,T)> F;
    vector<vector<T>> table;
    vector<int> logn;
    int n, k;
    sparse_table(vector<T> &vec, function<T(T,T)> func): F(func) {
        n = (int) vec.size();
        logn.resize(n + 1);
        logn[1] = 0;
        for (int i = 2; i <= n; ++i)
            logn[i] = 1 + logn[i >> 1];
        k = logn[n];
        table.assign(k + 1, vector<T>(n));
        table[0] = vec;
        for (int i = 1; i <= k; ++i) {
            for (int j = 0; j + (1 << i) <= n; ++j) {
                table[i][j] = F(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    T ask(int L, int R) {
        int j = logn[R - L + 1];
        return F(table[j][L], table[j][R - (1 << j) + 1]);
    }
};
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n;
    vector<int> a(n);
    for (int &i: a) cin >> i;
    sparse_table<int> smx(a, [] (int i, int j) {
        return max(i, j);
    });
    sparse_table<int> sor(a, [] (int i, int j) {
        return i | j;
    });
    vector<int> b(n);
    b[n - 1] = 1;
    for (int i = n - 2; i >= 0; --i) {
        b[i] = 1;
        if (a[i] == a[i + 1])
            b[i] += b[i + 1];
    }
    map<int,int> last;
    for (int i: a) last[i] = -1;
    long long ans = 0;
    for (int i = 0; i < n; i += b[i]) {
        int lo, hi, mid;
        int i1 = i, i2 = i + b[i] - 1;
        lo = last[a[i]] + 1, hi = i1;
        while (lo < hi) {
            mid = (lo + hi) >> 1;
            if (smx.ask(mid, i1) == a[i]) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        int lmx = lo;
        lo = i2, hi = n - 1;
        while (lo < hi) {
            mid = (lo + hi + 1) >> 1;
            if (smx.ask(i2, mid) == a[i]) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        int rmx = lo;
        ans += (long long) (i1 - lmx) * (rmx - i2);
        ans += (long long) (i2 - i1 + 1) * (i1 - lmx + rmx - i2);
        lo = last[a[i]] + 1, hi = i;
        while (lo < hi) {
            mid = (lo + hi) >> 1;
            if (sor.ask(mid, i) == a[i]) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        lmx = lo;
        lo = i, hi = n - 1;
        while (lo < hi) {
            mid = (lo + hi + 1) >> 1;
            if (sor.ask(i, mid) == a[i]) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        rmx = lo;
        ans -= (long long) (i1 - lmx) * (rmx - i2);
        ans -= (long long) (i2 - i1 + 1) * (i1 - lmx + rmx - i2);
        last[a[i]] = i2;
    }
    cout << ans << '\n';

    return 0;
}
