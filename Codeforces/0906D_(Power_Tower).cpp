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
int phi(int n) {
    int res = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res -= res / i;
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1)
        res -= res / n;
    return res;
}
int magic_mul(int a, int b, int md) {
    long long mul = (long long) a * b;
    if (mul < md) return mul;
    else return (int) (mul % md + md);
}
int modpow(int b, int e, int md) {
    int res = 1;
    while (e > 0) {
        if (e & 1) res = magic_mul(res, b, md);
        b = magic_mul(b, b, md);
        e >>= 1;
    }
    return res;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    const int LOGM = (int) log2(m) + 5;
    vector<int> prephi(LOGM);
    prephi[0] = m;
    for (int i = 1; i < LOGM; ++i)
        prephi[i] = phi(prephi[i - 1]);
    assert(prephi[LOGM - 1] == 1);

    vector<int> a(n);
    for (int &e: a) cin >> e;
    function<int(int,int,int)> get = [&] (int l, int r, int idx) {
        if (l == r) return magic_mul(1, a[l], prephi[idx]);
        if (prephi[idx] == 1) return 1;
        int ret = modpow(a[l], get(l + 1, r, idx + 1), prephi[idx]);
        return ret;
    };
    int qq;
    cin >> qq;
    while (qq--) {
        int L, R;
        cin >> L >> R;
        cout << get(L - 1, R - 1, 0) % m << el;
    }

    return 0;
}
