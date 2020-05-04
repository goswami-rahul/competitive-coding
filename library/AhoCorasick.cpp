
struct AhoCorasick {
  static const int K = 26;
  struct Node {
    array<int, K> to, go;
    int link, up, pp;
    int clink;
    Node(int from = 0, int p = 0) : to(), go(), link(), up(from), pp(p), clink() {}
  };
  vector<Node> nodes;
  AhoCorasick() : nodes(2) { nodes[1].clink = 1; }
  void add_string (const string &s, int id) {
    int u = 1;
    for (const char &c : s) {
      int p = c - 'a';
      if (!nodes[u].to[p]) {
        nodes[u].to[p] = nodes[u].go[p] = (int) nodes.size();
        nodes.emplace_back(u, p);
      }
      u = nodes[u].to[p];
    }
    leafs[id] = u;
    nodes[u].clink = u;
  }
  int go(int u, int p) {
    if (nodes[u].go[p]) return nodes[u].go[p];
    if (u == 1) return nodes[u].go[p] = 1;
    return nodes[u].go[p] = go(link(u), p);
  }
  int link(int u) {
    if (nodes[u].link) return nodes[u].link;
    if (nodes[u].up == 1 or u == 1) return nodes[u].link = 1;
    return nodes[u].link = go(link(nodes[u].up), nodes[u].pp);
  }
  int exit_link(int u) {
    // closest link with leaf(s) (including self)
    if (nodes[u].clink) return nodes[u].clink;
    return nodes[u].clink = exit_link(link(u));
  }
  void build_tree() {
    tree.resize(nodes.size());
    for (int i = 2; i < SZ(tree); ++i) if (i == exit_link(i)) {
      tree[exit_link(link(i))].push_back(i);
    }
    timer = 1;
    dfs();
  }
  void dfs(int u = 1) {
    ent[u] = timer++;
    for (const int &v : tree[u]) dfs(v);
    ext[u] = timer;
  }
  int timer;
  vector<vector<int>> tree;
  vector<int> leafs;
};

/*********************************************/
int to[N][K], link[N], term[N], que[N];

void add_word(const string &s) {
  int u = 0;
  for (char c : s) {
    int p = code(c);
    if (!to[u][p]) to[u][p] = ctr++;
    u = to[u][p];
  }
  term[u] = 1;
}
void bfs() {
  int fp = 0, bp = 0;
  que[bp++] = 0;
  while (fp < bp) {
    int u = que[fp++];
    int w = link[u];
    term[u] |= term[w];
    for (int i = 0; i < K; ++i) {
      int &v = to[u][i];
      if (v) {
        link[v] = u ? to[w][i] : 0;
        que[bp++] = v;
      } else {
        v = to[w][i];
      }
    }
  }
}
