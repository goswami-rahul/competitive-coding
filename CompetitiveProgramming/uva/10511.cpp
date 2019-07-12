/**
 * Consider a network flow with source connected to all clubs with cap 1
 * all clubs connected to each person with capacity 1
 * and, all person connected to their party with capacity 1.
 * Finally connect all party to sink with capacity floor((n - 1) / 2)
 * where n = no. of clubs
 * because, more than n/2 of same party are not allowed.
 * Now, run max flow algorithm. If the flow if less than n, 
 * there's no answer.
 * Else, print all the edges between clubs and persons which have flow = 1.
**/
#include <bits/stdc++.h>
using namespace std;
#define SZ(v) int((v).size())
#define ALL(vec) (vec).begin(),(vec).end()
typedef long long i64;
template<typename T> inline bool uax(T &x, T y) {return (y > x) ? x = y, true : false;}
template<typename T> inline bool uin(T &x, T y) {return (y < x) ? x = y, true : false;}
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); \
  stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
string to_string(char c) { return "'" + string(1, c) + "'";}
string to_string(string s) { return '"' + s + '"';}
string to_string(const char* s) { return to_string((string) s);}
template<typename A> string to_string(A);
template<typename A, typename B> string to_string(pair<A, B> p){
  return "(" + to_string(p.first) + ": " + to_string(p.second) + ")";}
template<typename A> string to_string(A v) {bool f = false; string r = "{"; 
  for (auto x: v) {if (f) r += ", "; r += to_string(x); f = true;} return r += "}";}
void err(istream_iterator<string>) {}
template<typename T,typename... Args> void err(istream_iterator<string> it, T a, Args... args) {
  cerr << *it << " =: " << to_string(a) << endl; err(++it, args...); }
template<typename T> void kek(T ans) {cout << ans << endl; exit(0);}
int const MOD = 1e9 + 7;
long long const INF = 1e18;
/***********************************************************************/
namespace Dinic {
  
typedef int flow_t;
const int MAXN = 10000;
const int MAXE = MAXN * MAXN;
const flow_t INF = 2e9;
const flow_t EPS = 1;

const bool SCALING = false;
flow_t MAXCAP = 1000;
flow_t LIM = SCALING ? MAXCAP : EPS;

struct Edge {
  int u, v;
  flow_t cap, flow;
};
Edge edges[MAXE];
vector<int> adj[MAXN];
int lev[MAXN];
int ptr[MAXN];
int que[MAXN];
int N = MAXN, E = 0;
int source, sink;

bool bfs() {
  int fp = 0, bp = 0;
  fill(lev, lev + N, -1);
  lev[source] = 0; que[bp++] = source;
  while (fp < bp) {
    int u = que[fp++];
    for (const int id : adj[u]) {
      if (edges[id].cap - edges[id].flow < LIM) continue;
      if (lev[edges[id].v] != -1) continue;
      lev[edges[id].v] = lev[u] + 1;
      que[bp++] = edges[id].v;
    }
  }
  return lev[sink] != -1;
}
flow_t dfs(int u, flow_t pushed) {
  if (pushed == 0) return 0;
  if (u == sink) return pushed;
  for (int& cid = ptr[u]; cid < (int) adj[u].size(); cid++) {
    int id = adj[u][cid];
    int v = edges[id].v;
    if (lev[u] + 1 != lev[v]) continue;
    if (edges[id].cap - edges[id].flow < LIM) continue;
    flow_t flow = dfs(v, min(pushed, edges[id].cap - edges[id].flow));
    if (flow == 0) continue;
    edges[id].flow += flow;
    edges[id ^ 1].flow -= flow;
    return flow;
  }
  return 0;
}
flow_t max_flow(int s, int t) {
  source = s, sink = t;
  flow_t flow = 0, pushed;
  for (; LIM >= EPS; LIM >>= 1) {
    while (bfs()) {
      fill(ptr, ptr + N, 0);
      while ((pushed = dfs(source, INF)) >= EPS) 
        flow += pushed;
    }
  }
  return flow;
}
inline void reset(int n = MAXN, int maxcap = MAXCAP) {
  N = n; E = 0; LIM = SCALING ? maxcap : EPS;
  for (int i = 0; i < N; ++i) adj[i].clear();
}
inline void set_edge(int u, int v, flow_t cap = 1) /*directed edge*/ {
  adj[u].push_back(E);
  edges[E++] = {u, v, cap, 0};
  adj[v].push_back(E);
  edges[E++] = {v, u, 0, 0};
}

} // namespace Dinic

struct relation {
  string name, party;
  vector<string> clubs; 
};
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int tt;
  cin >> tt;
  while (tt--) {
    string buf;
    map<string,int> NameId;
    map<string,int> ClubId;
    map<string,int> PartyId;
    vector<string> IdStr;
    vector<relation> rel;
    bool done = false;
    while (true) {
      getline(cin, buf);
      if (buf.empty()) {
        if (done) break;
        else continue;
      }
      done = true;
      stringstream ss(buf);
      relation r;
      ss >> r.name >> r.party;
      string club;
      while (ss >> club) {
        r.clubs.push_back(club);
        ClubId[club];
      }
      if (r.clubs.empty()) continue;
      NameId[r.name];
      PartyId[r.party];
      rel.push_back(std::move(r));
    }
    int n = SZ(ClubId);
    int k = SZ(NameId);
    int m = SZ(PartyId);
    IdStr.resize(n + m + k);
    int ctr = 0;
    for (auto &pr: ClubId) 
      IdStr[pr.second = ctr++] = pr.first;
    for (auto &pr: NameId) 
      IdStr[pr.second = ctr++] = pr.first;
    for (auto &pr: PartyId) 
      IdStr[pr.second = ctr++] = pr.first;
    
    if (n <= 2) {
      cout << "Impossible.\n";
      if (tt) cout << "\n";
      continue;
    }
    int s = ctr++;
    int t = ctr++;
    Dinic::reset(ctr);
    for (int i = 0; i < n; ++i) 
      Dinic::set_edge(s, i, 1);
    for (int i = 0; i < m; ++i) 
      Dinic::set_edge(i + n + k, t, (n - 1) / 2);
    for (const relation &r: rel) {
      Dinic::set_edge(NameId[r.name], PartyId[r.party], 1);
      for (const string &club: r.clubs) {
        Dinic::set_edge(ClubId[club], NameId[r.name], 1);
      }
    }
    int flow = Dinic::max_flow(s, t);
    if (flow < n) {
      cout << "Impossible.\n";
    } else {
      int cnt = 0, ecnt = 0;
      for (const Dinic::Edge& edge: Dinic::edges) if (ecnt++ < Dinic::E) {
        if (edge.u < n && edge.flow == 1) {
          cout << IdStr[edge.v] << " " << IdStr[edge.u] << "\n";
          cnt++;
        }
      }
      assert (cnt == n);
    }
    if (tt) cout << "\n";
  }
  
  return 0;
}
