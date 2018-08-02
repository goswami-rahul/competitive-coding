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
    cin >> n >> m;
    char arr[n + 1][m + 1], b[n + 1][m + 1];
    FOR(i,1,n) FOR(j,1,m) {
        cin >> arr[i][j];
        b[i][j] = '.';
    }
    vector< tuple<ll,ll,ll> > ans;
    FOR(i,2,n-1) FOR(j,2,m-1) {
        if (arr[i][j]=='*') {
            ll sz = 0, l = j, r = j, u = i, d = i;
            while (--l >= 1 && ++r <= m && --u >= 1 && ++d <= n &&
                (arr[i][l]=='*' && arr[i][r]=='*' && arr[u][j]=='*' && arr[d][j]=='*')) {
                    sz++;
                    b[i][j] = b[i][l] = b[i][r] = b[u][j] = b[d][j] = '*';
                }
            if (sz) {
                ans.pb(make_tuple(i, j, sz));
            }
        }
    }
    FOR(i,1,n) FOR(j,1,m) cerr << b[i][j] << " \n"[j==m];
    FOR(i,1,n) FOR(j,1,m) if (arr[i][j]!=b[i][j]) {
        cout << "-1";
        return 0;
    }
    cout << ans.size() << el;
    for (auto e: ans) {
        tie(x,y,k) = e;
        cout << x << " " << y << " " << k << el;
    }
    return 0;
}
