#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int INF = 1e9 + 1;

ll gcd(ll a, ll b) { 
    if (b == 0) return a; 
    return gcd(b, a % b);  
} 

pair<ll, ll> simplify(ll num, ll den){
    ll g = gcd(num, den);
    return make_pair(num / g, den / g);
}

ll abso(ll a){
    if(a < 0) return -a;
    return a; 
}

pair<ll, ll> selMin(pair<ll, ll> a, pair<ll, ll> b){
    double x = (double)a.first / a.second;
    double y = (double)b.first / b.second;
    if(x < y) return a;
    return b;
}

pair<ll, ll> selMax(pair<ll, ll> a, pair<ll, ll> b){
    double x = (double)a.first / a.second;
    double y = (double)b.first / b.second;
    if(x > y) return a;
    return b;
}

bool valid(pair<ll, ll> a, pair<ll, ll> b){
    double x = (double)a.first / a.second;
    double y = (double)b.first / b.second;
    if(x < y) return true;
    return false;
}

ll bestY(ll a, ll b, ll c, ll d, ll l = 1, ll r = 1e18){
    if(l == r) return l;
    ll y = (l + r) / 2;
    ll x = (a * y) / x + 1;
    double f2 = (double)c / d;
    double f = (double)x / y;
    if(f < f2) return (bestY(a, b, c, d, l, y));
    return bestY(a, b, c, d, y + 1, r);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    for(int tt = 1; tt <= t; tt++){
        int n;
        cin >> n;
        vector<pair<int, int> > mol;
        for(int i = 0; i < n; i++){
            int c, j;
            cin >> c >> j;
            mol.emplace_back(c, j);
        }
        pair<ll, ll> minRatio = make_pair(INF, 1);
        pair<ll, ll> maxRatio = make_pair(-1, 1);
        bool possible = true;
        for(int i = 0; i < n && possible; i++){
            for(int j = i + 1; j < n; j++){
                if(mol[i].first == mol[j].first){
                    if(mol[i].second < mol[j].second) continue;
                    possible = false;
                    break;
                }
                if(mol[i].second == mol[j].second){
                    if(mol[i].first < mol[j].first) continue;
                    possible = false;
                    break;
                }
                if(mol[i].first < mol[j].first && mol[i].second < mol[j].second){
                    continue;
                }
                if(mol[i].first > mol[j].first && mol[i].second > mol[j].second){
                    possible = false;
                    break;
                }
                ll num = mol[j].second - mol[i].second;
                ll den = mol[i].first - mol[j].first;
                pair<ll, ll> rat = simplify(abs(num), abs(den));
                if(den > 0) maxRatio = selMax(maxRatio, rat);
                else minRatio = selMin(minRatio, rat);
            }
        }
        pair<ll, ll> mn = make_pair(INF, 1);
        pair<ll, ll> mx = make_pair(-1, 1);
        if(minRatio != mn && maxRatio != mx && !valid(minRatio, maxRatio)) possible = false; 
        cout << "Case #" << tt << ": ";
        if(!possible) cout << "IMPOSSIBLE\n";
        else{
            if(minRatio == mn && maxRatio == mx){
                cout << "1 1\n";
            }
            else if(minRatio == mn){
                cout << "1 " << maxRatio.second / maxRatio.first + 1 << endl;
            }
            else if(maxRatio == mx){
                cout << minRatio.first / minRatio.second + 1 << " 1" << endl;
            }
            else{
                ll d = bestY(minRatio.first, minRatio.second, maxRatio.first, maxRatio.second);
                ll n = (minRatio.first * d) / minRatio.second + 1;
                cout << n << " " << d << endl;
            }
        }
    }
}