vector<int> Toposort(const vector<vector<int>> &g)  { 
  //~ std::priority_queue<int, vector<int>, greater<int>> leaves;
  vector<int> leaves; 
  int n = g.size();
  vector<int> in(n);
  for (auto &adj: g) for (int &v: g) in[v]++;
  for (int i = 0; i < n; i++) if (in[i] == 0) {
    leaves.push(i);
  }
  vector<int> topo;
  while (!leaves.empty()) {
    //~ int u = leaves.top(); leaves.pop();
    int u = leaves.back(); leaves.pop_back();
    topo.push_back(u);
    for (int &v: g[u]) {
      in[v]--;
      if (in[v] == 0)
        leaves.push_back(v);
    }
  }
  if((int) topo.size() < n) {
    // cycle
    throw;
  } 
  return topo;
}
