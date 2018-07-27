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
bool arr[26];
ll dp[100][100];

ll solve(ll i, ll k) {
	if (k==1) return i + 1;
	if (dp[i][k]==-1){
		ll ret = INF;
		ll j;
		FOR(j,i+2,25) {
			if (arr[j])
				ret = min(ret, solve(j, k-1));
		}
		dp[i][k] = i + 1 + ret;
	}
	return dp[i][k];
}

int main()
{
    fio;
    ll t=1, T;
    ll i, j, x, y, k, w, a, b, n, m, d;
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
	cin >> n >> k;
	string s;
	cin >> s;
	for (auto c: s) arr[c-'a'] = true;
	FOR(i,0,51) FOR(j,0,51) dp[i][j] = -1;
	ll best = INF;
	FOR(i,0,25) {
		if (arr[i]) best = min(best, solve(i,k));
	}
	if (best == INF) best = -1;
	cout << best;

    return 0;
}
