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

int main()
{
    fio;
    int t=1, T;
    ll n, m, i, j, x, y, k, w, l, p, qq, ans;
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    cin >> n;
    ll arr[n+1];
    priority_queue<pll> intro, extro;
    FOR(i,1,n) {
        cin >> x;
        intro.push(mp(-x,i));
    }
    char c;
    FOR(i,1,(2*n)) {
        cin >> c;
        if (c == '0') {
            x = -intro.top().F;
            y = intro.top().S;
            intro.pop();
            extro.push(mp(x,y));
        }
        else if (c == '1') {
            y = extro.top().S;
            extro.pop();
        }
        cout << y << " ";
    }


    return 0;
}
