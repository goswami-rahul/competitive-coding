/*
Divide the array into 2 equal parts. let A and B
A subset which is good, can be partitioned into L and R
now L_A + L_B = R_A + R_B
=>  L_A - R_A = R_B - R_B
It means the differences should be equal in the A and B sets for the subset to be good
So, we generate all differences that can be formed in A, and B
Finally, for each difference that is same in A and B, include the
subset containing such elements of A and B.
*/
#include<bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

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
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int &i: a) cin >> i;
    vector<int> b(a.begin() + n / 2, a.end());
    a.erase(a.begin() + n / 2, a.end());
    n = (int) a.size();
    int m = (int) b.size();
    vector<int> A;
    for (int mask = 0; mask < (1 << n); ++mask) {
        int sum = 0;
        for (int j = 0; j < n; ++j) {
            if (mask >> j & 1) {
                sum += a[j];
            }
        }
        A.push_back(sum);
    }
    vector<int> B;
    for (int mask = 0; mask < (1 << m); ++mask) {
        int sum = 0;
        for (int j = 0; j < m; ++j) {
            if (mask >> j & 1) {
                sum += b[j];
            }
        }
        B.push_back(sum);
    }
    unordered_map<int,vector<int>> aa;
    for (int i = 0; i < (1 << n); ++i) {
        for (int j = i; j < (1 << n); ++j) {
            if (i & j) continue;
            int p = A[j] - A[i];
            if (p < 0) p = -p;
            aa[p].push_back(i|j);
        }
    }
    bitset<(1 << 20)> ans;
    for (int i = 0; i < (1 << m); ++i) {
        for (int j = i; j < (1 << m); ++j) {
            if (i & j) continue;
            int p = B[j] - B[i];
            if (p < 0) p = -p;
            if (!aa.count(p)) continue;
            for (int &k: aa[p]) ans.set((i | j) << n | k);
        }
    }
    // -1 for empty subset
    cout << ans.count() - 1 << '\n';

    return 0;
}
