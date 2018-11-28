/*
I stored all the edges in the complete graph of n vertices.
then randomly shuffle it for each step, and add edges until
the graph gets connected. Finally, take the average of all the
answers, and return the answer.
*/
#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randint(int a, int b) {
    return uniform_int_distribution<int>(a, b)(rng);
}
auto gettime() {
    return std::chrono::high_resolution_clock::now();
}
auto duration(auto d) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(gettime() - d).count();
}
// Complete the solve function below.
int solve(int n) {
    auto starttime = gettime();
    auto dur = duration(starttime);
    vector<pair<int,int>> edges;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            edges.emplace_back(i, j);
    vector<int> par(n);

    function<int(int)> find = [&] (int u) {
        return par[u] = (u == par[u] ? u : find(par[u]));
    };
    auto join = [&] (int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        par[v] = u;
        return true;
    };
    int m = (int) edges.size();
    const int EP = 50;
    int steps = 0;
    int acc = 0;
    while (dur < 1000 - EP) {
        shuffle(edges.begin(), edges.end(), rng);
        for (int i = 0; i < n; ++i) {
            par[i] = i;
        }
        int cnt = n;
        for (int i = 0; i < m; ++i) {
            cnt -= join(edges[i].first, edges[i].second);
            if (cnt == 1) {
                acc += i + 1;
                break;
            }
        }
        steps++;
        dur = duration(starttime);
    }
    return acc / steps;


}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int result = solve(n);

    fout << result << "\n";

    fout.close();

    return 0;
}
