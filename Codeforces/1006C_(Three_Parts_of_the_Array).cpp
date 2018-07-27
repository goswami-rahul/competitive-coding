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

ll arr[100010], dir[100010], par[100010], sizes[100010];
bool blocked[100010] = {false}, vis[100010] = {false};
vl adj[100010];

ll find(ll x) {
    while (x != par[x]) x = par[x];
    return x;
}

void uunion(ll x, ll y) {
    // x = find(x);
    // y = find(y);
    if (sizes[x] > sizes[y]) swap(x, y);
    par[x] = y;
    sizes[y] += sizes[x];
}

void dfs(ll s, ll p, ll d) {
	dir[s] = d;
	for (ll e: adj[s]) {
		if (e==p) continue;
		dfs(e, s, 1 - d);
	}
}

int main()
{
    fio;
    ll t=1, T;
    ll n, m, i, j, x, y, k, w, a, b;
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
	cin >> n;
	ll arr[n + 2];
	arr[0] = 0;
	arr[n + 1] = 0;
	FOR(i,1,n) cin >> arr[i];
	i = 0; j= n + 1;
	ll sl = 0, sr = 0;
	ll ans = 0;
	while (i < j) {
		if (sl == sr) {
			ans = sl;
			sl += arr[++i];
			sr += arr[--j];
		}
		else if (sl < sr) {
			sl += arr[++i];
		}
		else {
			sr += arr[--j];
		}
	}
	cout << ans;

    return 0;
}
