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
    ll n, m, i, j, x, y, k, w, l, p, qq, vx, vy, x1, x2, y1, y2, ax, ay;
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    // string s;
    cin >> n >> m;
    bitset<2000> swt[n];
    FOR(i,0,n-1) {
        cin >> swt[i];
    }
    bool ok = false;
    FOR(i,0,n-1) {
        bitset<2000> temp;
        // cout << temp << el;
        FOR(j,0,n-1) {
            if (j == i) continue;
            temp |= swt[j];
            // cout << temp << " temp" << el;
            // cout << swt[i] << " swt[i]" << el;
        }
        // cout << temp << el;
        if (temp.count() == m) {
            ok = true;
            break;
        }
    }
    if (ok) cout << "YES";
    else cout << "NO";

    return 0;
}
