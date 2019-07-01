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

#define mk make_tuple

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
vl adj[200010];
ll need[200010];
set<ll> sts[200010];
ll ans;

void dfs(ll s) {
    // error(s);
    sts[s].insert(s);
    for (ll e: adj[s]) {
        dfs(e);
        if (sts[e].size() > sts[s].size()) swap(sts[e], sts[s]);
        for (ll x: sts[e]) {
            sts[s].insert(x);
        }
        sts[e].clear();
    }
    set<ll>::iterator it;
    // error(s);for (ll e: st) cerr << e << " "; cerr << el;
    while (!sts[s].empty() && need[s] > 0) {
        it = sts[s].end();
        it--;
        ans += *it;
        sts[s].erase(it);
        need[s]--;
    }
    // for (ll e: st) cerr << e << " "; cerr << el;
}

void solve() {
    ll i, j, x, y, k, w, n, m, A, B;
    cin >> n >> m >> A >> B;
    FOR(i,0,200000) {
        adj[i].clear();
        sts[i].clear();
        need[i] = 0LL;
    }
    ans = 0;
    FOR(i,0,m-1) {
        x = (A * i + B) % n;
        need[x]++;
    }
    FOR(i,1,n-1) {
        cin >> x;
        adj[x].pb(i);
    }
    dfs(0);
    cout << ans << endl;
    // cerr << ans << el;
}

int main()
{
    fio;
    ll t=1, T;
    freopen("jacks_candy_shop.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    cin >> T;
    FOR(t,1,T) {
        cout << "Case #" << t << ": ";
        solve();
        // if (t == 8) break;
    }

    return 0;
}
