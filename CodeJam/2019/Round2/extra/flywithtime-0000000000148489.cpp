#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

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
        set<pair<ll, ll> > ratio;
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                ll num = mol[j].second - mol[i].second;
                ll den = mol[i].first - mol[j].first;
                if(num == 0 || den == 0) continue;
                if(num*den < 0) continue;
                ratio.insert(simplify(abso(num), abso(den)));
            }
        }
        cout << "Case #" << tt << ": " << ratio.size() + 1 << endl;
    }
}