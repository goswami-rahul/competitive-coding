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
const ll MOD = 1e9+7;
const ll INF = 1e18;
const double E=1e-6;

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " = " << a << "\n";
	err(++it, args...);
}

bool powertwo(ll x) {
	return ( (x > 0) && ((x & (x - 1)) == 0) );
}

int main()
{
    fio;
    ll t=1, T;
    ll n, m, i, j, x, y, k, w, a, b, p;
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
	cin >> n;
	unordered_map<ll, ll> mpp;
	FOR(i,1,n) {
		cin >> x;
		mpp[x]++;
	}
	ll ans = 0;
	unordered_set<ll> done;
	for (pll e: mpp) {
		x = e.F;
		k = e.S;
		if (done.count(x)) {
			// ans++;
		}
		else {
			bool ok = false;
			FOR(i,1,32) {
				if (x < (1 << i) && mpp.count((1 << i) - x)) {
					// ans++;
					if (2 * x == (1 << i) && k == 1) {
						continue;
					}
					ok = true;
					done.insert((x - (1 << i)));
					break;
				}
			}
			if (!ok) ans += k;
		}
		// error(x, k, ans); cerr << el;
	}
	cout << ans;

    return 0;
}
