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
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define FOR(i, a, b) for(i=a; i<=b; i++)
#define RFOR(i, b, a) for(i=b; i>=a; i--)
#define all(vec) vec.begin(),vec.end()

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " = " << a << "\n";
	err(++it, args...);
}

const ll MOD = 1e9+7;
const ll INF = 1e18;
const double E=1e-6;

/*************************************************************/

int main()
{
    fio;
    ll t=1, T;
    ll i, j, x, y, k, w, n, m;
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    cin >> n;
    ll a[n + 1];
    a[0] = 0;
    ll csum = 0LL;
    FOR(i,1,n) {
        cin >> a[i];
        csum += a[i];
    }
    if (abs(csum) % 3) {
        cout << 0;
        return 0;
    }
    k = csum / 3;
    ll k1 = 0;
    ll ans = 0, cur = 0LL;
    FOR(i,1,n-1) {
        cur += a[i];
        if (cur==2*k) ans += k1;
        if (cur==k) k1++;
    }
    cout << ans;

    return 0;
}
