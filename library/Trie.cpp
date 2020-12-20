struct trie {
  int n;
  vector<array<int,2>> go;
  trie() : n(1) { 
    go.resize(n);
  };
  void put(int x) {
    int cur = 0;
    for (int i = 29; i >= 0; --i) {
      int b = x >> i & 1;
      if (!go[cur][b]) {
        go[cur][b] = n++;
        go.emplace_back();
      }
      cur = go[cur][b];
    }
  }
  int ask(int x) {
    // minimum ai ^ x
    int cur = 0, res = 0;
    for (int i = 29; i >= 0; --i) {
      int b = x >> i & 1;
      if (go[cur][b]) {
        cur = go[cur][b];
      } else {
        cur = go[cur][!b];
        res += 1 << i;
      }
    }
    return res;
  }
};
