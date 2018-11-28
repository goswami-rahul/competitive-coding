#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

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

    int n, m;
    cin >> n >> m;

    if (n * m == 1) {
        cout << "YES\n1\n";
        return 0;
    }
    if (n * m == 9) {
        cout << "YES\n";
        cout << "6 1 8\n7 5 3\n2 9 4\n";
        return 0;
    }
    if (max(n, m) < 4) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    if (n == 1 || m == 1) {
        int p = max(n, m);
        vector<int> a(p);
        int val = 1;
        for (int i = 1; i < p; i += 2) a[i] = val++;
        for (int i = 0; i < p; i += 2) a[i] = val++;
        for (auto i: a) cout << i << " \n"[m == 1];
        return 0;
    }
    vector<vector<int>> b(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            b[i][j] = i * m + j + 1;
    bool swapped = false;
    if (m < 4) {
        swap(n, m);
        swapped = true;
    }
    vector<vector<int>> a;
    a.assign(n, vector<int>(m));
    if (swapped) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                a[i][j] = b[j][i];
    } else {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                a[i][j] = b[i][j];
    }
    for (int i = 1; i < n; i += 2) {
        int x = a[i][m - 1], y = a[i][m - 2];
        for (int j = m - 1; j > 1; j--) {
            a[i][j] = a[i][j - 2];
        }
        a[i][1] = x;
        a[i][0] = y;
    }
    for (int j = 1; j < m; j += 2) {
        int x = a[0][j];
        for (int i = 0; i < n - 1; ++i)
            a[i][j] = a[i + 1][j];
        a[n - 1][j] = x;
    }
    if (swapped) {
        for (int j = 0; j < m; ++j) {
            for (int i = 0; i < n; ++i)
                cout << a[i][j] << ' ';
            cout << '\n';
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
                cout << a[i][j] << ' ';
            cout << '\n';
        }
    }

    return 0;
}
