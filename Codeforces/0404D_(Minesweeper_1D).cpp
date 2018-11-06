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
inline void add(int &a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    if (s == "?") {
        cout << 2 << el;
        return 0;
    } else if (s == "0" || s == "*") {
        cout << 1 << el;
        return 0;
    }
    int n = (int) s.size();
    s = "##" + s;
    vector<vector<int>> dp(n + 2, vector<int>(5, 0));
    // 0 -> nw to fill  00, 10
    // 1 -> nw to fill  *1
    // 2 -> nw to fill *2*
    // 3 -> nw to fill  **
    // 4 -> nw to fill  1*
    for (int i = 2; i < n + 2; ++i) {
        if (i - 1 < 2) add(dp[i][0], 1);
        if (s[i - 1] == '?' || s[i - 1] == '0') {
            add(dp[i][0], dp[i - 1][0]);
        }
        if (s[i - 1] == '?' || s[i - 1] == '1') {
            add(dp[i][0], dp[i - 1][1]);

            if (i - 2 < 2) add(dp[i][4], 1);
            if (s[i - 2] == '?' || s[i - 2] == '0')
                add(dp[i][4], dp[i - 2][0]);
            if (s[i - 2] == '?' || s[i - 2] == '1')
                add(dp[i][4], dp[i - 2][1]);
        }
        if (s[i - 1] == '?' || s[i - 1] == '*') {
            add(dp[i][1], dp[i - 1][2]);
            add(dp[i][1], dp[i - 1][3]);
            add(dp[i][1], dp[i - 1][4]);
            if (i - 2 < 2) add(dp[i][1], 1);

            add(dp[i][3], dp[i - 1][2]);
            add(dp[i][3], dp[i - 1][3]);
            add(dp[i][3], dp[i - 1][4]);
            if (i - 2 < 2) add(dp[i][3], 1);
        }
        if (s[i - 1] == '?' || s[i - 1] == '2') {
            if (s[i - 2] == '?' || s[i - 2] == '*') {
                if (i - 3 < 2) add(dp[i][2], 1);
                add(dp[i][2], dp[i - 2][2]);
                add(dp[i][2], dp[i - 2][3]);
                add(dp[i][2], dp[i - 2][4]);
            }
        }
    }
    int ans = 0;
    if (s[n + 1] == '?' || s[n + 1] == '0') add(ans, dp[n + 1][0]);
    if (s[n + 1] == '?' || s[n + 1] == '1') add(ans, dp[n + 1][1]);
    if (s[n + 1] == '?' || s[n + 1] == '2') add(ans, 0);
    if (s[n + 1] == '?' || s[n + 1] == '*') {
        add(ans, dp[n + 1][2]);
        add(ans, dp[n + 1][3]);
        add(ans, dp[n + 1][4]);
    }
    cout << ans << el;
    return 0;
}
