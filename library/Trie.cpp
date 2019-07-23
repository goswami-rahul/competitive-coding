struct Trie {
  struct Node {
    static const int ALPHA = 2;
    bool is;
    array<int,ALPHA> nxt;
    int depth;
    Node(): is(), nxt(), depth() {}
    int& operator [] (size_t idx) {
      return nxt[idx];
    }
  };
  vector<Node> nodes;
  int ptr = 1;
  Trie(const int nax = 2e5): nodes(nax) {}
  bool add(const string &s) {
    int cur = 0;
    for (const char &c: s) {
      int u = c - '0';
      if (!nodes[cur][u]) {
        nodes[ptr].depth = 1 + nodes[cur].depth;
        nodes[cur][u] = ptr++;
      }
      cur = nodes[cur][u];
    }
    if (nodes[cur].is) return false;
    return nodes[cur].is = true;
  }
};
