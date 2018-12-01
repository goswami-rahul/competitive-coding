/*
The intended and correct solution was using bitmasks, which unfortunately,
I didn't understand yet.
However, I managed to solve this problem with a different, randomized approach.
I choose the starting vertex randomly, and then choose vertices greedily, which
connects the most number of edges. If there are multiple such vertices, I choose
one at random.
This solution passes easily in 1s TL, after running it through the tests multiple
times.
*/
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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randint(int a, int b) {
    return uniform_int_distribution<int>(a, b)(rng);
}
auto gettime() {
    return std::chrono::high_resolution_clock::now();
}
int duration(auto d) {
    // time from d till now (in milliseconds)
    return (int) std::chrono::duration_cast<std::chrono::milliseconds>(gettime() - d).count();
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto starttime = gettime();
    int n, m;
    cin >> n >> m;
    vector<vector<bool>> g(n, vector<bool>(n, true));
    vector<vector<bool>> gg(n, vector<bool>(n, true));
    for (int i = 0; i < n; ++i) gg[i][i] = false;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        gg[u][v] = gg[v][u] = false;
    }
    auto get = [&] (int &u) {
        int done = true;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (g[i][j]) done = false;
        if (done) return false;
        int mn = n;
        vector<int> suspects;
        for (int i = 0; i < n; ++i) {
            int cur = 0;
            for (int j = 0; j < n; ++j)
                cur += g[i][j];
            if (cur < mn) {
                mn = cur;
                suspects = {i};
            } else if (cur == mn) {
                suspects.push_back(i);
            }
        }
        u = suspects[randint(0, (int) suspects.size() - 1)];
        return true;
    };
    auto prune = [&] (int u) {
        set<int> s;
        for (int v = 0; v < n; ++v)
            if (g[u][v]) s.insert(v);
        for (int i = 0; i < n; ++i) {
            if (s.count(i)) continue;
            for (int j = 0; j < n; ++j) {
                if (s.count(j)) continue;
                g[i][j] = false;
            }
        }
    };
    vector<int> ans;
    int u;
    g = gg;
    while (get(u)) {
        ans.push_back(u);
        prune(u);
    }
    while (duration(starttime) < 950) {
        g = gg;
        int u = randint(0, n - 1);
        vector<int> a = {u};
        prune(u);
        while (get(u)) {
            a.push_back(u);
            prune(u);
        }
        if ((int) ans.size() > (int) a.size()) {
            ans = a;
        }
    }
    cout << ans.size() << '\n';
    for (int u: ans) cout << u + 1 << ' ';
    cout << '\n';

    return 0;
}
