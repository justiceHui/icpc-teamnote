vector<int> DominatorTree(const vector<vector<int>> &g, int src){ // // 0-based
  int n = g.size();
  vector<vector<int>> rg(n), buf(n);
  vector<int> r(n), val(n), idom(n, -1), sdom(n, -1), o, p(n), u(n);
  iota(all(r), 0); iota(all(val), 0);
  for(int i=0; i<n; i++) for(auto j : g[i]) rg[j].push_back(i);
  function<int(int)> find = [&](int v){
    if(v == r[v]) return v;
    int ret = find(r[v]);
    if(sdom[val[v]] > sdom[val[r[v]]]) val[v] = val[r[v]];
    return r[v] = ret;
  };
  function<void(int)> dfs = [&](int v){
    sdom[v] = o.size(); o.push_back(v);
    for(auto i : g[v]) if(sdom[i] == -1) p[i] = v, dfs(i);
  };
  dfs(src); reverse(all(o));
  for(auto &i : o){
    if(sdom[i] == -1) continue;
    for(auto j : rg[i]){
      if(sdom[j] == -1) continue;
      int x = val[find(j), j];
      if(sdom[i] > sdom[x]) sdom[i] = sdom[x];
    }
    buf[o[o.size() - sdom[i] - 1]].push_back(i);
    for(auto j : buf[p[i]]) u[j] = val[find(j), j];
    buf[p[i]].clear();
    r[i] = p[i];
  }
  reverse(all(o)); idom[src] = src;
  for(auto i : o){ // WARNING : if different, takes idom
    if(i != src) idom[i] = sdom[i] == sdom[u[i]] ? sdom[i] : idom[u[i]];
  }
  for(auto i : o) if(i != src) idom[i] = o[idom[i]];
  return idom; // unreachable -> ret[i] = -1
}