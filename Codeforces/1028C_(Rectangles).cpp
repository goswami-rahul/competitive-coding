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
#define fio ios_base::sync_with_stdio(false),cin.tie(NULL)
#define ull unsigned long long int
#define ld long double
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define FOR(i, a, b) for(int i=a; i<=b; i++)
#define RFOR(i, b, a) for(int i=b; i>=a; i--)
#define all(vec) (vec).begin(),(vec).end()
#define rall(vec) (vec).rbegin(),(vec).rend()

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
const double EPS = 1e-6;

/***********************************************************************/
int main()
{
   fio;
   ll n, x, y, m, d, k;
   cin >> n;
   vector<pair<ll, ll>> a(n + 1), la(n + 1), ra(n + 2), b(n + 1), lb(n + 1), rb(n + 2);
   FOR(i,1,n) {
       ll x1, x2, y1, y2;
       cin >> x1 >> y1 >> x2 >> y2;
       a[i] = {x1, x2};
       b[i] = {y1, y2};
   }
   la[0] = {-INF, INF};
   lb[0] = {-INF, INF};
   ra[n + 1] = {-INF, INF};
   rb[n + 1] = {-INF, INF};
   for (int i = 1; i <= n; ++i) {
       la[i].first = max(la[i - 1].first, a[i].first);
       lb[i].first = max(lb[i - 1].first, b[i].first);
       la[i].second = min(la[i - 1].second, a[i].second);
       lb[i].second = min(lb[i - 1].second, b[i].second);
   }
   for (int i = n; i > 0; --i) {
       ra[i].first = max(ra[i + 1].first, a[i].first);
       rb[i].first = max(rb[i + 1].first, b[i].first);
       ra[i].second = min(ra[i + 1].second, a[i].second);
       rb[i].second = min(rb[i + 1].second, b[i].second);
   }
   // error(la, lb, ra, rb)
   for (int i = 1; i <= n; ++i) {
       ll mna = min(la[i - 1].second, ra[i + 1].second);
       ll mxa = max(la[i - 1].first, ra[i + 1].first);
       ll mnb = min(lb[i - 1].second, rb[i + 1].second);
       ll mxb = max(lb[i - 1].first, rb[i + 1].first);
       // error(i, mxa, mna, mxb, mnb) cerr << el;
       if (mxa <= mna && mxb <= mnb) {
           cout << mxa << " " << mxb;
           break;
       }
   }

   return 0;
}