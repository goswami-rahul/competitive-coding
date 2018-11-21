/*
Problem asked to delete 2 edges from the tree optimaly such that the difference
between maximum and minimum remaining subtrees is minimized.
I maintained 2 multisets:
for current vertex v
A with sizes of nodes which are neither in the subtree of v, nor is an ancestor of v.
B with sizes of nodes which are ancestor of v.
for each subtree, update answers using binary search on sets A and B.
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

template<typename T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
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
inline std::ostream &operator << (std::ostream & os,const std::multiset<T>& v) {
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
    vector<vector<int>> tree(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    vector<int> sum(n), bigchild(n);
    function<int(int,int)> predfs = [&] (int s, int pa) {
        sum[s] = 1;
        bigchild[s] = -1;
        int mx = -1;
        for (const int &v: tree[s]) {
            if (v == pa) continue;
            sum[s] += predfs(v, s);
            if (sum[v] > mx) {
                mx = sum[v];
                bigchild[s] = v;
            }
        }
        return sum[s];
    };
    predfs(0, -1);
    int ans = n + 1;
    auto relax = [&] (const int &a, const int &b) {
        ans = min(ans, max({a, b, n - a - b}) - min({a, b, n - a - b}));
    };
    multiset<int> A, B;
    for (int i = 0; i < n; ++i) A.insert(sum[i]);
    function<void(int,int,vector<int>&)> dfs = [&] (int s, int pa, vector<int> &C) {
        // returns subtree
        B.insert(sum[s]);
        A.erase(A.find(sum[s]));
        vector<int> buf;
        for (const int &v: tree[s]) {
            if (v == pa || v == bigchild[s]) continue;
            vector<int> his;
            dfs(v, s, his);
            for (const int &e: his) {
                A.insert(e);
                buf.push_back(e);
            }
        }
        if (bigchild[s] > -1) {
            dfs(bigchild[s], s, C);
            for (const int &e: buf) {
                A.erase(A.find(e));
                C.push_back(sum[s]);
            }
        }
        C.push_back(sum[s]);
        auto a = A.upper_bound((n - sum[s]) / 2);
        if (a != A.end()) {
            relax(sum[s], *a);
        }
        if (a != A.begin()) {
            --a;
            relax(sum[s], *a);
        }
        B.erase(B.find(sum[s]));
        a = B.upper_bound((n - sum[s]) / 2 + sum[s]);
        if (a != B.end()) {
            relax(sum[s], *a - sum[s]);
        }
        if (a != B.begin()) {
            --a;
            relax(sum[s], *a - sum[s]);
        }
    };
    vector<int> C;
    dfs(0, -1, C);
    cout << ans << '\n';

    return 0;
}
