/*
 * Precompute the cumulative locations and directions for each step.
 * Now, for each character, try changing it to the other two, and
 * insert the points obtainded through vector additions and rotations
 * into a set. There are atmost 2 insertions
 * at each step, so complexity is O(n log n).
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define SZ(v) (int((v).size()))
#define ALL(vec) (vec).begin(),(vec).end()
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
using namespace std;
 
template<typename T, typename V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<T, V, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>; // find_by_order(), order_of_key()
using ll = long long int;
using i64 = long long int;
template <typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template <typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}

void err(__attribute__((unused)) istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " =: " << a << endl;
    err(++it, args...);
}
template <typename T1, typename T2>
inline ostream& operator << (ostream& os, const pair<T1, T2>& buf) {
    return os << "(" << buf.first << ": " << buf.second << ")";
}
template<typename T>
inline ostream &operator << (ostream & os,const vector<T>& v) {
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
inline ostream &operator << (ostream & os,const set<T>& v) {
    bool first = true;
    os << "{";
    for (auto ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii;
        first = false;
    }
    return os << "}";
}
inline ostream &operator << (ostream & os,const multiset<pair<int,int>>& v) {
    bool first = true;
    os << "{";
    for (auto x: v) {
        if(!first) os << ", ";
        os << x;
        first = false;
    }
    return os << "}";
}
template<typename T1, typename T2>
inline ostream &operator << (ostream & os,const map<T1, T2>& v) {
    bool first = true;
    os << "{";
    for (typename map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii ;
        first = false;
        return os << "}";
    }
}
template<typename T>
inline ostream &operator << (ostream & os,const vector<vector<T>>& v) {
    for (auto &u: v) os << '\n' << u;
    return os;
}
template<typename T>
void finish(T ans) {cout << ans << '\n'; exit(0);}
const int MOD = 1e9 + 7;
const long long INF = 1e18;
const double EPS = 1e-6;
#define PI 3.14159265358979323846
/***********************************************************************/
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
// NESW
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    int n = SZ(s);
    set<pair<int,int>> ans;
    vector<int> x(n + 1, 0), y(n + 1, 0), d(n + 1, 0);
    auto L = [] (int x, int y) {
        return make_pair(-y, x);
    };
    auto R = [] (int x, int y) {
        return make_pair(y, -x);
    };
    for (int i = 1; i <= n; ++i) {
        x[i] = x[i - 1];
        y[i] = y[i - 1];
        int &dir = d[i];
        dir = d[i - 1];
        if (s[i - 1] == 'F') {
            x[i] += dx[dir];
            y[i] += dy[dir];
        } else if (s[i - 1] == 'L') {
            dir = (dir - 1 + 4) % 4;
        } else if (s[i - 1] == 'R') {
            dir = (dir + 1) % 4;
        }
    }
    for (int i = 1; i <= n; ++i) {
        char c = s[i - 1];
        if (c == 'F') {
            int ax = x[n] - x[i];
            int ay = y[n] - y[i];
            ans.emplace(x[i - 1] - ay, y[i - 1] + ax);
            ans.emplace(x[i - 1] + ay, y[i - 1] - ax);
        } else if (c == 'L') {
            int ax, ay;
            tie(ax, ay) = R(x[n] - x[i], y[n] - y[i]);
            int dir = d[i - 1];
            ans.emplace(x[i] + ax + dx[dir], y[i] + ay + dy[dir]);
            tie(ax, ay) = R(ax, ay);
            ans.emplace(x[i] + ax, y[i] + ay);
        } else if (c == 'R') {
            int ax, ay;
            tie(ax, ay) = L(x[n] - x[i], y[n] - y[i]);
            int dir = d[i - 1];
            ans.emplace(x[i] + ax + dx[dir], y[i] + ay + dy[dir]);
            tie(ax, ay) = L(ax, ay);
            ans.emplace(x[i] + ax, y[i] + ay);
        }
    }
    finish(SZ(ans));
    
    return 0;
}
