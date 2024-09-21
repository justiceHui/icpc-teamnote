struct TDContainer{ // graph size, tree size, tree width, root
  int gn, tn, tw, root; vector<int> par; vector<vector<int>> bag;
};
TDContainer TreeWidth2(int n, const vector<pair<int,int>> &edges){
  assert(n > 0); // gp_hash_table is ~2x faster
  vector<unordered_set<int>> g(n); vector<int> fin(n);
  for(const auto &[u,v] : edges) g[u].insert(v), g[v].insert(u);
  queue<int> q; for(int i=0; i<n; i++) q.push(i);
  vector<tuple<int,int,int,int>> seq;
  while(!q.empty()){ int v = q.front(); q.pop();
    if(g[v].size() > 2  || fin[v]) continue; fin[v] = 1;
    for(auto i : g[v]) g[i].erase(v);
    if(g[v].size() == 0) seq.emplace_back(0, v, -1, -1);
    else if(g[v].size() == 1){
      int x = *g[v].begin(); q.push(x);
      seq.emplace_back(1, v, x, -1);
    }else{ int x = -1, y = -1;
      for(auto i : g[v]) (x == -1 ? x : y) = i;
      seq.emplace_back(2,v,x,y); q.push(x); q.push(y);
      g[x].insert(y); g[y].insert(x);
    }
  }
  if(seq.size() != n) return -1; // fail to decomposition
  int id = 0; reverse(seq.begin(), seq.end());
  vector<int> par(n, -1), first_bag_id(n, -1);
  vector<vector<int>> bag(n);
  gp_hash_table<long long, int> same_bag_id;
  auto group = [&same_bag_id,&n](int u, int v, int id) -> void {
    same_bag_id[1ll*u*n+v] = same_bag_id[1ll*v*n+u] = id;
  };
  for(auto [ch,v,x,y] : seq){
    if(ch == 0){ bag[id] = {v}; par[id] = id - 1; }
    else if(ch == 1){ bag[id] = {v, x};
      par[id] = first_bag_id[x]; group(v, x, id);
    }else{
      bag[id] = {v, x, y}; par[id] = same_bag_id[1ll*x*n+y];
      group(v, x, id); group(v, y, id); group(x, y, id);
    } first_bag_id[v] = id++;
  }
  return TDContainer(n, n, 2, 0, par, bag);
}