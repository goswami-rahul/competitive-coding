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
struct rec {
    i64 x1, y1, x2, y2;
    rec(i64 a, i64 b, i64 c, i64 d) {
        x1 = a;
        y1 = b;
        x2 = c;
        y2 = d;
    }
    rec() {};
};
bool ins(const rec &a, const rec &b) {
    // a in b?
    return (a.x1 >= b.x1 && a.x2 <= b.x2 && a.y1 >= b.y1 && a.y2 <= b.y2);
}
vector<rec> cut(rec a, rec b) {
    vector<rec> ret;
    if (a.x2 < b.x1 || a.y2 < b.y1 || a.x1 > b.x2 || a.y1 > b.y2) {
        ret.push_back(b);
        return ret;
    }
    a.x2 = min(a.x2, b.x2);
    a.y2 = min(a.y2, b.y2);
    a.x1 = max(a.x1, b.x1);
    a.y1 = max(a.y1, b.y1);
    if (a.x2 + 1 <= b.x2) {
        ret.emplace_back(a.x2 + 1, a.y1, b.x2, a.y2);
    }
    if (a.y2 + 1 <= b.y2) {
        ret.emplace_back(a.x1, a.y2 + 1, a.x2, b.y2);
    }
    if (a.x1 - 1 >= b.x1) {
        ret.emplace_back(b.x1, a.y1, a.x1 - 1, a.y2);
    }
    if (a.y1 - 1 >= b.y1) {
        ret.emplace_back(a.x1, b.y1, a.x2, a.y1 - 1);
    }
    if (a.x2 + 1 <= b.x2 && a.y2 + 1 <= b.y2) {
        ret.emplace_back(a.x2 + 1, a.y2 + 1, b.x2, b.y2);
    }
    if (a.x2 + 1 <= b.x2 && a.y1 - 1 >= b.y1) {
        ret.emplace_back(a.x2 + 1, b.y1, b.x2, a.y1 - 1);
    }
    if (a.x1 - 1 >= b.x1 && a.y2 + 1 <= b.y2) {
        ret.emplace_back(b.x1, a.y2 + 1, a.x1 - 1, b.y2);
    }
    if (a.x1 - 1 >= b.x1 && a.y1 - 1 >= b.y1) {
        ret.emplace_back(b.x1, b.y1, a.x1 - 1, a.y1 - 1);
    }
    return ret;
}
i64 get(i64 x, i64 y) {
    if (x * y % 2 == 0) {
        return x * y / 2;
    }
    return x * y / 2 + 1;
}
i64 getw(const rec &a) {
    assert(a.x1 <= a.x2 && a.y1 <= a.y2);
    i64 ret = get(a.x2, a.y2);
    ret -= get(a.x1 - 1, a.y2);
    ret -= get(a.x2, a.y1 - 1);
    ret += get(a.x1 - 1, a.y1 - 1);
    return ret;
}
i64 getb(const rec &a) {
    assert(a.x1 <= a.x2 && a.y1 <= a.y2);
    return (a.x2 - a.x1 + 1) * (a.y2 - a.y1 + 1) - getw(a);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> q;
    while (q--) {
        i64 n, m;
        cin >> n >> m;
        rec b, w;
        cin >> w.x1 >> w.y1 >> w.x2 >> w.y2;
        cin >> b.x1 >> b.y1 >> b.x2 >> b.y2;
        i64 W = get(m, n);
        auto ret = cut(b, w);
        W -= getw(b);
        for (const auto& r: ret) {
            W += getb(r);
        }
        cout << W << ' ' << m * n - W << '\n';
    }

    return 0;
}