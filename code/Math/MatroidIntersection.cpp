struct Matroid{
  virtual bool check(int i) = 0; // O(R^2N), O(R^2N)
  virtual void insert(int i) = 0; // O(R^3), O(R^2N)
  virtual void clear() = 0; // O(R^2), O(RN)
};
template<typename cost_t>
vector<cost_t> MI(const vector<cost_t> &cost, Matroid *m1, Matroid *m2){
  int n = cost.size();
  vector<pair<cost_t, int>> dist(n+1);
  vector<vector<pair<int, cost_t>>> adj(n+1);
  vector<int> pv(n+1), inq(n+1), flag(n); deque<int> dq;
  auto augment = [&]() -> bool {
    fill(dist.begin(), dist.end(), pair(numeric_limits<cost_t>::max()/2, 0));
    fill(adj.begin(), adj.end(), vector<pair<int, cost_t>>());
    fill(pv.begin(), pv.end(), -1);
    fill(inq.begin(), inq.end(), 0);
    dq.clear(); m1->clear(); m2->clear();
    for(int i=0; i<n; i++) if(flag[i]) m1->insert(i), m2->insert(i);
    for(int i=0; i<n; i++){
      if(flag[i]) continue;
      if(m1->check(i)) dist[pv[i]=i] = {cost[i], 0}, dq.push_back(i), inq[i] = 1;
      if(m2->check(i)) adj[i].emplace_back(n, 0);
    }
    for(int i=0; i<n; i++){
      if(!flag[i]) continue;
      m1->clear(); m2->clear();
      for(int j=0; j<n; j++) if(i != j && flag[j]) m1->insert(j), m2->insert(j);
      for(int j=0; j<n; j++){
        if(flag[j]) continue;
        if(m1->check(j)) adj[i].emplace_back(j, cost[j]);
        if(m2->check(j)) adj[j].emplace_back(i, -cost[i]);
      }
    }
    while(dq.size()){
      int v = dq.front(); dq.pop_front(); inq[v] = 0;
      for(const auto &[i,w] : adj[v]){
        pair<cost_t, int> nxt{dist[v].first+w, dist[v].second+1};
        if(nxt < dist[i]){
          dist[i] = nxt; pv[i] = v;
          if(!inq[i]) dq.push_back(i), inq[i] = 1;
        }
      }
    }
    if(pv[n] == -1) return false;
    for(int i=pv[n]; ; i=pv[i]){
      flag[i] ^= 1; if(i == pv[i]) break;
    }
    return true;
  };
  vector<cost_t> res;
  while(augment()){
    cost_t now = cost_t(0);
    for(int i=0; i<n; i++) if(flag[i]) now += cost[i];
    res.push_back(now);
  }
  return res;
}