struct Trie {
  struct Node {
    static const int ALPHA = 26;
    int is;
    array<int,ALPHA> nxt;
    int depth;
    Node(): is(), nxt(), depth() {}
    int& operator [] (size_t idx) {
      return nxt[idx];
    }
  };
  vector<Node> nodes;
  int ptr;
  Trie(): nodes(1), ptr(1) {}
  void add(const string &s) {
    int cur = 0;
    for (const char &c: s) {
      int u = c - 'A';
      if (!nodes[cur][u]) {
        nodes[ptr].depth = 1 + nodes[cur].depth;
        nodes.emplace_back();
        nodes[cur][u] = ptr++;
      }
      cur = nodes[cur][u];
    }
    nodes[cur].is++;
  }
};
