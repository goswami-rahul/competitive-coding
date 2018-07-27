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
#define RFOR(i, b, a) for(i=b; i<=a; i--)
const ll MOD = 1e9+7;
const ll INF = 1e18;
const double E=1e-6;

vl adj[100010];
ll subtree[100010];
ll ans;

void dfs(ll s, ll p) {
    subtree[s] = 1;
    for (ll c: adj[s]) {
        if (c == p) continue;
        dfs(c, s);
        subtree[s] += subtree[c];
    }
    if (subtree[s] % 2 == 0) ans++;
}

int main()
{
    fio;
    int t=1, T;
    ll n, m, i, j, x, y, k, w, l, p, qq;
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    cin >> n;
    FOR(i,1,n-1) {
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    if (n & 1) {
        cout << -1;
        return 0;
    }
    ans = -1;
    dfs(1, 0);
    cout << ans;

    return 0;
}
