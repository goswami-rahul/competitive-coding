#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mod=1e9+7;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n;
    cin >> n;
    vector<int>V;
    for (int i=0;i<n;i++){
        int a;
        cin >> a;
        if (a==0){
            vector<int>J=V;
            sort(J.begin(), J.end());
            if (J.size()==0)
                cout << "0\n";
            else if (J.size()==1){
                cout << "pushStack\n";
                cout << "1 popStack\n";
            }
            else if (J.size()==2){
                cout << "pushStack\n";
                cout << "pushQueue\n";
                cout << "2 popStack popQueue\n";
            }
            else{
                bool J1=false, J2=false, J3=false;
                for (int i=0;i<V.size();i++){
                    if (V[i]==J[J.size()-1] and !J1){
                        cout << "pushStack\n";J1=true;
                    }
                    else if (V[i]==J[J.size()-2] and !J2){
                        cout << "pushQueue\n";J2=true;
                    }
                    else if (V[i]==J[J.size()-3] and !J3){
                        cout << "pushBack\n";J3=true;
                    }
                    else{
                        cout << "pushFront\n";
                    }
                }
                cout << "3 popStack popQueue popBack\n";
            }
            V.resize(0);
        }
        else
            V.push_back(a);
    }
    while(V.size()>0){
        cout << "pushStack\n";V.pop_back();
    }
    return 0;
}