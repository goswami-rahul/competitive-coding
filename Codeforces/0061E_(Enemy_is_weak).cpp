#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define ll long long int
#define vi vector< int >
#define vl vector< ll >
#define pii pair< int, int >
#define pll pair< ll , ll >
#define pdd pair< double, double >
#define vii vector< pii >
#define vll vector< pll >
#define vd vector< double >
#define vb vector< bool >
#define el "\n"
#define ull unsigned long long int
#define ld long double
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define sqr(x) ((x) * (x))
#define FOR(i, a, b) for(ll i=a; i<=b; i++)
#define RFOR(i, b, a) for(ll i=b; i>=a; i--)
#define all(vec) (vec).begin(),(vec).end()
template <typename T> void maxme(T &x, T y) {if (y > x) x = y; }
template <typename T> void minme(T &x, T y) {if (y < x) x = y; }
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " =: " << a << "\n";
    // cerr << "\n";
	err(++it, args...);
}
template<class T1, class T2, class T3>
struct triple {
    T1 a; T2 b; T3 c;
    triple() : a(T1()), b(T2()), c(T3()) {};
    triple(T1 _a, T2 _b, T3 _c): a(_a), b(_b), c(_c) {}
};
template<class T1, class T2, class T3>
bool operator<(const triple<T1,T2,T3>&t1,const triple<T1,T2,T3>&t2) {
    if(t1.a!=t2.a)return t1.a<t2.a;
    else if(t1.b!=t2.b)return t1.b<t2.b;
    else return t1.c<t2.c;
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
struct SegTree {
    using data = vector<int>;
    vector<data> tree;
    vector<int> arr;
    int n;
    SegTree(size_t sz, vector<int> &vec) {
        // 1-indexed vec!
        arr = vec;
        n = (int) sz;
        assert(sz == vec.size() - 1);
        tree.resize(4 * n);
        build(1, n, 1);
    }
    inline data make_data(int pos) {
        return data{arr[pos]};
    }
    inline data combine(const data &left, const data &right) {
        data node = data(left.size() + right.size());
        merge(all(left), all(right), node.begin());
        return node;
    }
    inline void build(int tl, int tr, int idx) {
        if (tl == tr) {
            tree[idx] = make_data(tl);
            return;
        }
        int m = (tl + tr) >> 1;
        build(tl, m, idx << 1);
        build(m + 1, tr, idx << 1 | 1);
        tree[idx] = combine(tree[idx << 1], tree[idx << 1 | 1]);
    }
    inline int ask_util_low(int idx, int tl, int tr, int L, int R, int val) {
        assert(L <= R);
        if (L == tl && R == tr) {
            return (int) (lower_bound(all(tree[idx]), val) - tree[idx].begin());
        }
        int m = (tr + tl) >> 1;
        if (L > m) {
            return ask_util_low(idx << 1 | 1, m + 1, tr, L, R, val);
        } else if (R < m + 1) {
            return ask_util_low(idx << 1, tl, m, L, R, val);
        } else {
            return ask_util_low(idx << 1, tl, m, L, min(m, R), val)
                + ask_util_low(idx << 1 | 1, m + 1, tr, max(m + 1, L), R, val);
        }
    }
    inline int ask_util_high(int idx, int tl, int tr, int L, int R, int val) {
        assert(L <= R);
        if (L == tl && R == tr) {
            return (int) tree[idx].size() - (int) (upper_bound(all(tree[idx]), val) - tree[idx].begin());
        }
        int m = (tr + tl) >> 1;
        if (L > m) {
            return ask_util_high(idx << 1 | 1, m + 1, tr, L, R, val);
        } else if (R < m + 1) {
            return ask_util_high(idx << 1, tl, m, L, R, val);
        } else {
            return ask_util_high(idx << 1, tl, m, L, min(m, R), val)
                + ask_util_high(idx << 1 | 1, m + 1, tr, max(m + 1, L), R, val);
        }
    }
    inline int askl(int L, int R, int val) {
        return ask_util_low(1, 1, n, L, R, val);
    }
    inline int askh(int L, int R, int val) {
        return ask_util_high(1, 1, n, L, R, val);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    a[0] = 42;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    SegTree seg(n, a);
    long long ans = 0LL;
    for (int i = 2; i <= n - 1; ++i) {
        ans += (long long) seg.askh(1, i - 1, a[i]) * seg.askl(i + 1, n, a[i]);
    }
    cout << ans << el;

    return 0;
}
