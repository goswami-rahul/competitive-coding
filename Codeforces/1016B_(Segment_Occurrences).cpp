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
ll lps[100010];

int main()
{
    fio;
    ll t=1, T;
    ll i, j, x, y, k, w, n, m;
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    ll N, M;
    cin >> N >> M >> t;
    string txt, pat;
    cin >> txt;
    cin >> pat;

    ll len = 0;
    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0)
            {
                len = lps[len-1];

                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }

    i = 0;  // index for txt[]
    j = 0;  // index for pat[]
    vb b(N + 1, false);

    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            // printf(&quot;Found pattern at index %d n&quot;, i-j);
            b[i-j] = 1;
            j = lps[j-1];
        }

        // mismatch after j matches
        else if (i < N && pat[j] != txt[i])
        {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j-1];
            else
                i = i+1;
        }
    }
    // FOR(i,0,N) {
    //     error(i, b[i]);
    // }
    ll ans[N + 1] = {0};
    FOR(i,1,N) {
        ans[i] = ans[i - 1] + b[i - 1];
    }
    // FOR(i,0,N) {
    //     cerr << ans[i] << " ";
    // }
    // cerr << el;
    while (t--) {
        cin >> x >> y;
        if (y - M + 1 < x - 1) cout << "0\n";
        else cout << ans[y - M + 1] - ans[x - 1] << el;
    }
    return 0;
}
