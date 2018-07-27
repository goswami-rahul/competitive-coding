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

int main()
{
    fio;
    ll t=1, T;
    ll n, m, i, j, x, y, k, w, b;
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
	cin >> n;
	unordered_map<ll, ll> mpp;
	string s;
	vl a;
	FOR(i,1,n) {
		cin >> s;
		ll cur = 0, cl = 0, cr = 0;
		for (auto& c: s) {
			if (c == ')') cl++;
			else cr++;
		}
		bool ok = true;
		if (cl > cr) {
			for (j=s.size()-1; j>=0; j--) {
				char c = s[j];
				if (c == ')') cur++;
				else cur--;
				if (cur < 0) {
					ok = false;
					break;
				}
			}
		}
		else if (cr > cl) {
			for (auto& c: s) {
				if (c == '(') cur++;
				else cur--;
				if (cur < 0) {
					ok = false;
					break;
				}
			}
		}
		else if (cr == cl) {
			for (auto& c: s) {
				if (c == '(') cur++;
				else cur--;
				if (cur < 0) {
					ok = false;
					break;
				}
			}
			if (cur != 0) ok = false;
		}
		if (ok) {
			mpp[cr - cl]++;
			if (cl < cr) a.pb(cr - cl);
		}
	}
	ll ans = mpp[0]*mpp[0];
	for (auto e: a) {
		ans += mpp[-e];
	}
	cout << ans;
    return 0;
}
