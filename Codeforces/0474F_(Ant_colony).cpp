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
    struct data {
        int mnn, gcd, cnt;
        data() {};
        data(int _1, int _2, int _3): mnn(_1), gcd(_2), cnt(_3) {};
    };
    vector<data> tree;
    vector<int> val;
    int n;
    SegTree(size_t sz, vector<int> &vec) {
        val = vec;
        n = (int) sz;
        assert(sz == vec.size());
        tree.resize(4 * n);
        build(1, n, 1);
    }
    data make_data(int pos) {
        int x = val[pos - 1];
        return data(x, x, 1);
    }
    data combine(const data &left, const data &right) {
        data node;
        node.gcd = __gcd(left.gcd, right.gcd);
        if (left.mnn == right.mnn) {
            node.mnn = left.mnn;
            node.cnt = left.cnt + right.cnt;
        } else if (left.mnn < right.mnn) {
            node.mnn = left.mnn;
            node.cnt = left.cnt;
        } else if (right.mnn < left.mnn) {
            node.mnn = right.mnn;
            node.cnt = right.cnt;
        }
        return node;
    }
    void build(int tl, int tr, int idx) {
        if (tl == tr) {
            tree[idx] = make_data(tl);
            return;
        }
        int m = (tl + tr) >> 1;
        build(tl, m, idx << 1);
        build(m + 1, tr, idx << 1 | 1);
        tree[idx] = combine(tree[idx << 1], tree[idx << 1 | 1]);
    }
    data ask_util(int idx, int tl, int tr, int L, int R) {
        assert(L <= R);
        if (L == tl && R == tr) {
            return tree[idx];
        }
        int m = (tr + tl) >> 1;
        if (L > m) {
            return ask_util(idx << 1 | 1, m + 1, tr, L, R);
        } else if (R < m + 1) {
            return ask_util(idx << 1, tl, m, L, R);
        } else {
            return combine(ask_util(idx << 1, tl, m, L, min(m, R)),
                    ask_util(idx << 1 | 1, m + 1, tr, max(m + 1, L), R));
        }
    }
    int ask(int L, int R) {
        data node = ask_util(1, 1, n, L, R);
        int ans = R - L + 1;
        if (node.gcd == node.mnn) {
            ans -= node.cnt;
        }
        return ans;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int &e: a) cin >> e;
    SegTree seg(n, a);
    int t;
    cin >> t;
    while (t--) {
        int L, R;
        cin >> L >> R;
        cout << seg.ask(L, R) << el;
    }

    return 0;
}
