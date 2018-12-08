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
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> tree(n);
    for (int i = 1; i < n; ++i) {
        int u;
        cin >> u; --u;
        tree[u].push_back(i);
    }
    string s;
    cin >> s;
    vector<vector<pair<int,int>>> Q(n);
    for (int i = 0; i < m; ++i) {
        int v, h;
        cin >> v >> h;
        --v;
        Q[v].emplace_back(i, h);
    }
    vector<int> mxd(n), dep(n);
    dep[0] = 1;
    function<void(int)> pre = [&] (int u) {
        mxd[u] = dep[u];
        int x = -1;
        for (int &v: tree[u]) {
            dep[v] = 1 + dep[u];
            pre(v);
            if (mxd[v] > mxd[u]) {
                mxd[u] = mxd[v];
                x = v;
            }
        }
        for (int &v: tree[u]) {
            if (v == x) {
                swap(v, tree[u].back());
                break;
            }
        }
    };
    pre(0);
    using H = unordered_map<int, unordered_map<int, int>>;
    vector<bool> ans(m);
    function<void(int, H&)> dfs = [&] (int u, H &a) {
        if (!tree[u].empty()) {
            dfs(tree[u].back(), a);
            for (int &v: tree[u]) {
                if (v == tree[u].back()) break;
                H his;
                dfs(v, his);
                for (auto& [h, b]: his)
                    for (auto& [c, x]: b)
                        a[h][c] += x;
            }
        }
        a[dep[u]][s[u] - 'a']++;
        for (auto& [id, h]: Q[u]) {
            if (a.find(h) == a.end()) {
                ans[id] = true;
            } else {
                int odds = 0;
                for (auto& [ignore, i]: a[h])
                    odds += (i & 1);
                ans[id] = (odds < 2);
            }
        }
    };
    H a;
    dfs(0, a);
    for (auto x: ans) cout << (x ? "Yes\n" : "No\n");

    return 0;
}
