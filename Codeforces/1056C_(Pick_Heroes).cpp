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
#define mp make_pair
int main()
{
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> p(2 * n);
    set<pair<int,int>, greater<pair<int,int>>> s;
    for (int i = 0; i < 2 * n; ++i) {
        cin >> p[i];
        s.insert({p[i], i});
    }
    vector<vector<int>> a(m, vector<int>(2));
    for (int i = 0; i < m; ++i) {
        cin >> a[i][0] >> a[i][1];
        --a[i][0]; --a[i][1];
        if (p[a[i][0]] < p[a[i][1]])
            swap(a[i][0], a[i][1]);
    }
    int t;
    cin >> t;
    if (t == 1) {
        for (int i = 0; i < m; ++i) {
            cout << a[i][0] + 1 << endl;
            s.erase(mp(p[a[i][0]], a[i][0]));
            int x;
            cin >> x;
            --x;
            assert(x == a[i][1]);
            s.erase(mp(p[a[i][1]], a[i][1]));
        }
        while (!s.empty()) {
            cout << s.begin()->second + 1 << endl;
            s.erase(s.begin());
            int x;
            cin >> x;
            --x;
            s.erase(mp(p[x], x));
        }
    } else {
        bool ff = false;
        while (!s.empty()) {
            int x;
            cin >> x;
            --x;
            s.erase(mp(p[x], x));
            bool done = false;
            for (int i = 0; i < m; ++i) {
                if (a[i][0] == x) {
                    cout << a[i][1] + 1 << endl;
                    done = true;
                    s.erase(mp(p[a[i][1]], a[i][1]));
                    break;
                } else if (a[i][1] == x) {
                    cout << a[i][0] + 1 << endl;
                    done = true;
                    s.erase(mp(p[a[i][0]], a[i][0]));
                    break;
                }
            }
            if (done) continue;
            if (!ff) {
                ff = true;
                for (int i = 0; i < m; ++i) {
                    if (s.count(mp(p[a[i][0]], a[i][0]))) {
                        cout << a[i][0] + 1 << endl;
                        s.erase(mp(p[a[i][0]], a[i][0]));
                        int x;
                        cin >> x;
                        --x;
                        assert(x == a[i][1]);
                        s.erase(mp(p[a[i][1]], a[i][1]));
                    }
                }
            }
            cout << s.begin()->second + 1 << endl;
            s.erase(s.begin());
        }
    }

    return 0;
}
