#include<bits/stdc++.h>
using namespace std;
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

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " =: " << a << "\n";
    // cerr << "\n";
	err(++it, args...);
}

template <typename T1, typename T2>
inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p)
{
    return os << "(" << p.first << ": " << p.second << ")";
}

template<typename T>
inline std::ostream &operator << (std::ostream & os,const std::vector<T>& v)
{
    bool first = true;
    os << "[";
    for(unsigned int i = 0; i < v.size(); i++)
    {
        if(!first)
            os << ", ";
        os << v[i];
        first = false;
    }
    return os << "]";
}

template<typename T>
inline std::ostream &operator << (std::ostream & os,const std::set<T>& v)
{
    bool first = true;
    os << "{";
    for (typename std::set<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        if(!first)
            os << ", ";
        os << *ii;
        first = false;
    }
    return os << "}";
}

template<typename T1, typename T2>
inline std::ostream &operator << (std::ostream & os,const std::map<T1, T2>& v)
{
    bool first = true;
    os << "{";
    for (typename std::map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        if(!first)
            os << ", ";
        os << *ii ;
        first = false;
    }
    return os << "}";
}

template<typename T>
inline std::ostream &operator << (std::ostream & os,const std::unordered_set<T>& v) {
    return os << std::set<T>(v.begin(), v.end());
}

template<typename T1, typename T2>
inline std::ostream &operator << (std::ostream & os,const std::unordered_map<T1, T2>& v) {
    return os << std::map<T1, T2>(v.begin(), v.end());
}

const ll MOD = 1e9+7;
const ll INF = 1e18;
const double E = 1e-6;
/***********************************************************************/
bool dig(char c) {
    return ('0' <= c && c <= '9');
}
bool low(char c) {
    return ('a' <= c && c <= 'z');
}
bool upp(char c) {
    return ('A' <= c && c <= 'Z');
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, x, y, m;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        int d = 0, l = 0, u = 0;
        for (char c: s) {
            d += dig(c);
            l += low(c);
            u += upp(c);
        }
        error(d, l, u)
        if (d == 0) {
            if (l > 1) {
                l--;
                for (char &c: s) {
                    if (low(c)) {
                        c = '1';
                        break;
                    }
                }
                d++;
            }
            else if (u > 1) {
                u--;
                for (char &c: s) {
                    if (upp(c)) {
                        c = '1';
                        break;
                    }
                }
                d++;
            }
        }
        if (l == 0) {
            if (d > 1) {
                d--;
                for (char &c: s) {
                    if (dig(c)) {
                        c = 'a';
                        break;
                    }
                }
                l++;
            }
            else if (u > 1) {
                u--;
                for (char &c: s) {
                    if (upp(c)) {
                        c = 'a';
                        break;
                    }
                }
                l++;
            }
        }
        if (u == 0) {
            if (l > 1) {
                l--;
                for (char &c: s) {
                    if (low(c)) {
                        c = 'A';
                        break;
                    }
                }
                u++;
            }
            else if (d > 1) {
                d--;
                for (char &c: s) {
                    if (dig(c)) {
                        c = 'A';
                        break;
                    }
                }
                u++;
            }
        }
        cout << s << el;
    }

    return 0;
}
