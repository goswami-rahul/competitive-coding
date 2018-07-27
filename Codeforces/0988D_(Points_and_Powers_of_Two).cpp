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

int main()
{
    fio;
    ll t=1, T;
    ll n, m, i, j, x, y, k, w, l, p, qq, vx, vy, x1, x2, y1, y2, ax, ay;
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    cin >> n;
    vl arr(n);
    FOR(i,0,n-1) cin >> arr[i];
    ll ans[3], sz = 1;
    ans[0] = arr[0];
    sort(all(arr));
    m = 1;
    FOR(i,0,n - 1) {
        FOR(j,0,30) {
            ll d = 1 << j;
            x = arr[i] + d;
            auto a = lower_bound(arr.begin() + i, arr.end(), x);
            if (a != arr.end() && (ll)(*a) == x) {
                sz = 2;
                k = a - arr.begin();
                ans[0] = arr[i];
                ans[1] = arr[k];
                y = arr[i] + (d<<1);
                auto b = lower_bound(arr.begin() + k, arr.end(), y);
                if (b != arr.end() && (ll)(*b) == y) {
                    sz = 3;
                    cout << "3\n";
                    cout << ans[0] << " " << ans[1] << " " << (ll)(*b);
                    return 0;
                }
            }
        }
    }
    cout << sz << el;
    FOR(i,0,sz-1) {
        cout << ans[i] << " ";
    }

    return 0;
}
