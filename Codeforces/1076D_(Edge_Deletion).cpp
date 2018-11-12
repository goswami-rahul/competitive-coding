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
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<ll,int>>> g(n);
    map<pair<int,int>, int> mp;
    for (int i = 0; i < m; ++i) {
        int x, y;
        ll w;
        cin >> x >> y >> w;
        --x, --y;
        mp[{x,y}] = i + 1;
        mp[{y,x}] = i + 1;
        g[x].push_back({w, y});
        g[y].push_back({w, x});
    }
    vector<ll> dis(n, INF);
    dis[0] = 0;
    set<pair<ll, int>> a;
    a.emplace(0LL, 0);
    map<pair<ll,int>,int> link;
    link[{0LL,0}] = -1;
    vector<int> ans;
    while (!a.empty()) {
        int x;
        ll w;
        tie(w, x) = *a.begin();
        a.erase(a.begin());

        int p = link[{w,x}];
        if (p != -1) ans.push_back(p);
        if (ans.size() == k) break;
        for (auto &e: g[x]) {
            if (dis[e.second] == INF) {
                dis[e.second] = w + e.first;
                a.emplace(w + e.first, e.second);
                link[{w + e.first, e.second}] = mp[{x, e.second}];
            } else if (w + e.first < dis[e.second]) {
                a.erase({dis[e.second], e.second});
                dis[e.second] = w + e.first;
                a.emplace(w + e.first, e.second);
                link[{w + e.first, e.second}] = mp[{x, e.second}];
            }
        }
    }
    cout << ans.size() << el;
    for (int &e: ans) cout << e << " ";
    cout << el;

    return 0;
}
