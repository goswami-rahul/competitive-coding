/*
Create a dp table win[h][t]
is +ve, if winning state and denotes minimum number of moves
is -ve, if losing state and denotes maximum number of moves to lose
is 0, for draw
initially (0, 0) is winning state
update all the winning states by a single bfs
to update all losing states, for each 0 state, keep checking if it can
be a losing state, until no more such states are left
*/
#include<bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

template<typename T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>; // find_by_order(), order_of_key()
using ll = long long int;
using i64 = long long int;
#define all(vec) (vec).begin(),(vec).end()
template <typename T> inline void ckmax(T &x, T y) {if (y > x) x = y; }
template <typename T> inline void ckmin(T &x, T y) {if (y < x) x = y; }
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " =: " << a << endl;
	err(++it, args...);
}
template <typename T1, typename T2>
inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& buf) {
    return os << "(" << buf.first << ": " << buf.second << ")";
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const std::vector<T>& v) {
    bool first = true;
    os << "[";
    for(unsigned int i = 0; i < v.size(); i++) {
        if(!first) os << ", ";
        os << v[i];
        first = false;
    }
    return os << "]";
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const std::set<T>& v) {
    bool first = true;
    os << "{";
    for (typename std::set<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii;
        first = false;
    }
    return os << "}";
}
template<typename T1, typename T2>
inline std::ostream &operator << (std::ostream & os,const std::map<T1, T2>& v) {
    bool first = true;
    os << "{";
    for (typename std::map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii ;
        first = false;
    }
    return os << "}";
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const std::unordered_set<T>& v) {
    return os << std::set<T>(v.begin(), v.end());
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const std::multiset<T,greater<T>>& v) {
    return os << std::vector<T>(v.begin(), v.end());
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const ordered_set<T>& v) {
    return os << std::set<T>(v.begin(), v.end());
}
template<typename T1, typename T2>
inline std::ostream &operator << (std::ostream & os,const std::unordered_map<T1, T2>& v) {
    return os << std::map<T1, T2>(v.begin(), v.end());
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const vector<vector<T>>& v) {
    os << '\n';
    for (auto &u: v) os << u << '\n';
    return os;
}
const int MOD = 1e9 + 7;
const long long INF = 1e18;
const double EPS = 1e-6;
/***********************************************************************/
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int h, t, R;
    cin >> h >> t >> R;
    vector<pair<int,int>> H, T;
    int n, m;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        H.emplace_back(x, y);
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        T.emplace_back(x, y);
    }
    vector<vector<int>> win(R + 1, vector<int>(R + 1, 0));
    for (int i = 0; i <= R; ++i) {
        for (int j = 0; j <= R; ++j) {
            if (i + j > R) win[i][j] = -1;
        }
    }
    win[0][0] = 1;
    queue<pair<int,int>> que;
    que.emplace(0, 0);
    while (!que.empty()) {
        int x, y;
        tie(x, y) = que.front();
        que.pop();
        int w = win[x][y];
        for (int i = 0; i < n; ++i) {
            int x1, y1;
            tie(x1, y1) = H[i];
            if (x - x1 >= 0 && y - y1 >= 0) {
                x1 = x - x1 + i + 1;
                y1 = y - y1;
                if (x1 + y1 <= R && win[x1][y1] == 0) {
                    win[x1][y1] = w + 1;
                    que.emplace(x1, y1);
                }
            }
        }
        for (int i = 0; i < m; ++i) {
            int x1, y1;
            tie(x1, y1) = T[i];
            if (x - x1 >= 0 && y - y1 >= 0) {
                x1 = x - x1;
                y1 = y - y1 + i + 1;
                if (x1 + y1 <= R && win[x1][y1] == 0) {
                    win[x1][y1] = w + 1;
                    que.emplace(x1, y1);
                }
            }
        }
    }
    bool relax = true;
    while (relax) {
        relax = false;
        for (int x = 0; x <= R; ++x) {
            for (int y = 0; y <= R; ++y) {
                if (win[x][y] != 0) {
                    continue;
                }
                int mn = 0;
                bool ok = true;
                for (int i = 0; i < n && ok && i < x; ++i) {
                    int x1, y1;
                    tie(x1, y1) = H[i];
                    x1 = x + x1 - (i + 1);
                    y1 = y + y1;
                    if (x1 + y1 > R) {
                        mn = min(mn, -2);
                    } else if (win[x1][y1] < 0) {
                        mn = min(mn, win[x1][y1] - 1);
                    } else {
                        ok = false;
                    }
                }
                for (int i = 0; i < m && ok && i < y; ++i) {
                    int x1, y1;
                    tie(x1, y1) = T[i];
                    x1 = x + x1;
                    y1 = y + y1 - (i + 1);
                    if (x1 + y1 > R) {
                        mn = min(mn, -2);
                    } else if (win[x1][y1] < 0) {
                        mn = min(mn, win[x1][y1] - 1);
                    } else {
                        ok = false;
                    }
                }
                if (ok) {
                    relax = true;
                    win[x][y] = mn;
                }
            }
        }
    }
    if (win[h][t] == 0) {
        cout << "Draw\n";
    } else if (win[h][t] > 0) {
        cout << "Ivan\n" << win[h][t] - 1 << '\n';
    } else if (win[h][t] < 0) {
        cout << "Zmey\n" << -win[h][t] - 1 << '\n';
    }

    return 0;
}
