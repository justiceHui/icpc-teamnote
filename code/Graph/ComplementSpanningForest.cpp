vector<pair<int,int>> ComplementSpanningForest(int n, const vector<pair<int,int>> &edges){ // V+ElgV
  vector<vector<int>> g(n);
  for(const auto &[u,v] : edges) g[u].push_back(v), g[v].push_back(u);
  for(int i=0; i<n; i++) sort(g[i].begin(), g[i].end());
  set<int> alive;
  for(int i=0; i<n; i++) alive.insert(i);
  vector<pair<int,int>> res;
  while(!alive.empty()){
    int u = *alive.begin(); alive.erase(alive.begin());
    queue<int> que; que.push(u);
    while(!que.empty()){
      int v = que.front(); que.pop();
      for(auto it=alive.begin(); it!=alive.end(); ){
        if(auto t=lower_bound(g[v].begin(), g[v].end(), *it); t != g[v].end() && *it == *t) ++it;
        else que.push(*it), res.emplace_back(u, *it), it = alive.erase(it);
  }}}return res;
}