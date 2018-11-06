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
inline void finish(int x) {cout << -1; exit(0);}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> col(n);
    for (int &e: col) cin >> e;
    vector<vector<int>> tree(n);
    tree[0].push_back(-1);
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }
    vector<long long> ans(n, 0);
    vector<int> best(n), cnt(n, 0);
    function<int(int,int)> dfs_sum = [&] (int s, int pa) {
        int sz = 1, large = -1;
        best[s] = -1;
        for (int v: tree[s]) {
            if (v == pa) continue;
            int cur = dfs_sum(v, s);
            if (cur > large) {
                best[s] = v;
                large = cur;
            }
            sz += cur;
        }
        return sz;
    };
    dfs_sum(0, -1);
    function<void(int,int,map<int,int>&)> dfs = [&] (int s, int pa, map<int,int> &cur) {
        if (tree[s].size() == 1) {
            ans[s] = col[s];
            cnt[s] = 1;
            cur = {{col[s], 1}};
            return;
        }
        dfs(best[s], s, cur);
        ans[s] = ans[best[s]];
        cnt[s] = cnt[best[s]];
        for (int v: tree[s]) {
            if (v == pa || v == best[s]) continue;
            map<int,int> other;
            dfs(v, s, other);
            for (auto& [c, freq]: other) {
                cur[c] += freq;
                if (cur[c] == cnt[s]) {
                    ans[s] += c;
                } else if (cur[c] > cnt[s]) {
                    cnt[s] = cur[c];
                    ans[s] = c;
                }
            }
        }
        cur[col[s]]++;
        if (cur[col[s]] > cnt[s]) {
            cnt[s] = cur[col[s]];
            ans[s] = col[s];
        } else if (cur[col[s]] == cnt[s]) {
            ans[s] += col[s];
        }
        return;
    };
    map<int,int> temp;
    dfs(0, -1, temp);
    for (long long &e: ans) cout << e << ' ';
    cout << el;

    return 0;
}
