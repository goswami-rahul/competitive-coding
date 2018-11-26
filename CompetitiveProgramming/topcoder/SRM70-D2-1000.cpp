/*
Problem was to count number of subtrees in the given tree.
We can root the tree, and calculate the no. of subtrees with
the current root. Finally, add ways for nodes and return the answer.
*/
#include<bits/stdc++.h>
using namespace std;
using i64 = long long int;

class CentaurCompanyDiv2 {
    public:
    i64 count(vector<int> a, vector<int> b) {
        int n = 1 + (int) a.size();
        vector<vector<int>> tree(n);
        for (int i = 0; i < n - 1; ++i) {
            tree[a[i] - 1].push_back(b[i] - 1);
            tree[b[i] - 1].push_back(a[i] - 1);
        }
        i64 ans = 0;
        function<i64(int,int)> dfs = [&] (int u, int pa) {
            i64 ways = 1;
            for (int v: tree[u]) {
                if (v == pa) continue;
                ways *= (1 + dfs(v, u));
            }
            ans += ways;
            return ways;
        };
        dfs(0, -1);
        return 1 + ans;
    }
};
