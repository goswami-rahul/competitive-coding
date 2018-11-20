/*
Problem required counting permutations with considering mirror images as the same.
Just count total permutations, and the palindrome permutations,
answer is their sum divided by 2.
*/
#include<bits/stdc++.h>
using namespace std;

class TinSoldiers {

    long long ways(vector<int> a) {
        int tot = accumulate(a.begin(), a.end(), 0);
        long long ans = 1;
        for (int i = 2; i <= tot; ++i) {
            ans *= i;
            for (int &e: a) {
                while (e > 0 && ans % e == 0) {
                    ans /= e;
                    --e;
                }
            }
        }
        return ans;
    }
    public:
    int lineUps(vector<int> a) {
        long long tot = ways(a);
        int odd = 0;
        for (int e: a) odd += (e & 1);
        if (odd <= 1) {
            for (int &e: a) e /= 2;
            tot += ways(a);
        }
        return tot >> 1;
    }
};
