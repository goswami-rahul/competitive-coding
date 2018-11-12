#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define ll long long int
#define el "\n"
#define sqr(x) ((x) * (x))
#define all(vec) (vec).begin(),(vec).end()
template <typename T> inline void maxme(T &x, T y) {if (y > x) x = y; }
template <typename T> inline void minme(T &x, T y) {if (y < x) x = y; }
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " =: " << a << endl;
	err(++it, args...);
}
template <typename T1, typename T2>
inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p) {
    return os << "(" << p.first << ": " << p.second << ")";
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
void finish(int ok) {
    error(ok)
    cout << (ok > 0 ? "YES\n" : "NO\n");
    exit(0);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    ll k;
    cin >> n >> m >> k;
    vector<ll> a(n);
    for (ll& e: a) cin >> e;
    set<pair<int,int>> segs;
    int pos = -1, len = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] > k) {
            if (pos == -1) {
                pos = i;
                len = 1;
            } else {
                len++;
            }
        } else {
            if (pos > -1) {
                segs.emplace(pos, len);
                pos = -1;
                len = 0;
            }
        }
    }
    if (pos > -1) {
        segs.emplace(pos, len);
        pos = -1;
        len = 0;
    }
    while (m--) {
        int t;
        cin >> t;
        if (t) {
            int p;
            ll d;
            cin >> p >> d;
            --p;
            if (a[p] > k) continue;
            a[p] += d;
            if (a[p] <= k) continue;
            auto it = segs.upper_bound(make_pair(p, -1));
            if (it == segs.end()) {
                if (it == segs.begin()) {
                    segs.emplace(p, 1);
                    continue;
                }
                auto itl = segs.upper_bound(make_pair(p, -1));
                --itl;
                if (itl->first + itl->second == p) {
                    auto pr = make_pair(itl->first, itl->second + 1);
                    segs.erase(*itl);
                    segs.insert(pr);
                } else {
                    segs.emplace(p, 1);
                }
            } else if (it == segs.begin()) {
                assert(it->first > p);
                if (it->first == p + 1) {
                    auto pr = make_pair(p, it->second + 1);
                    segs.erase(it);
                    segs.insert(pr);
                } else {
                    segs.emplace(p, 1);
                }
            } else {
                assert(it->first > p);
                auto itl = segs.upper_bound(make_pair(p, -1));
                --itl;
                if (itl->first + itl->second == p && it->first == p + 1) {
                    auto pr = make_pair(itl->first, itl->second + it->second + 1);
                    segs.erase((*it));
                    segs.erase((*itl));
                    segs.insert(pr);
                } else if (itl->first + itl->second == p) {
                    auto pr = make_pair(itl->first, itl->second + 1);
                    segs.erase(*itl);
                    segs.insert(pr);
                    continue;
                } else if (it->first == p + 1) {
                    auto pr = make_pair(p, it->second + 1);
                    segs.erase(*it);
                    segs.insert(pr);
                    continue;
                } else {
                    segs.emplace(p, 1);
                }
            }
        } else {
            cout << (int) segs.size() << el;
        }
    }

    return 0;
}
