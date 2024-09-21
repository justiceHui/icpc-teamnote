template<typename flow_t> struct Edge {
  int u, v, r; flow_t c, f; Edge() = default;
  Edge(int u, int v, flow_t c, int r) : u(u), v(v), r(r), c(c), f(0) {}
};
template<typename flow_t, size_t _Sz> struct PushRelabel {
  using edge_t = Edge<flow_t>;
  int n, b, dist[_Sz], count[_Sz+1];
  flow_t excess[_Sz]; bool active[_Sz];
  vector<edge_t> g[_Sz]; vector<int> bucket[_Sz];
  void clear(){ for(int i=0; i<_Sz; i++) g[i].clear(); }
  void addEdge(int s, int e, flow_t x){
    g[s].emplace_back(s, e, x, (int)g[e].size());
    if(s == e) g[s].back().r++;
    g[e].emplace_back(e, s, 0, (int)g[s].size()-1);
  }
  void enqueue(int v){
    if(!active[v] && excess[v] > 0 && dist[v] < n){
      active[v] = true; bucket[dist[v]].push_back(v); b = max(b, dist[v]); }
  }
  void push(edge_t &e){
    flow_t fl = min(excess[e.u], e.c - e.f);
    if(dist[e.u] == dist[e.v] + 1 && fl > flow_t(0)){
      e.f += fl; g[e.v][e.r].f -= fl; excess[e.u] -= fl; excess[e.v] += fl; enqueue(e.v); }
  }
  void gap(int k){
    for(int i=0; i<n; i++){
      if(dist[i] >= k) count[dist[i]]--, dist[i] = max(dist[i], n), count[dist[i]]++;
      enqueue(i); }
  }
  void relabel(int v){
    count[dist[v]]--; dist[v] = n;
    for(const auto &e : g[v]) if(e.c - e.f > 0) dist[v] = min(dist[v], dist[e.v] + 1);
    count[dist[v]]++; enqueue(v);
  }
  void discharge(int v){
    for(auto &e : g[v]) if(excess[v] > 0) push(e); else break;
    if(excess[v] > 0) if(count[dist[v]] == 1) gap(dist[v]);
    else relabel(v);
  }
  flow_t maximumFlow(int _n, int s, int t){
    // memset dist, excess, count, active 0
    n = _n; b = 0; for(auto &e : g[s]) excess[s] += e.c;
    count[s] = n; enqueue(s); active[t] = true;
    while(b >= 0){
      if(bucket[b].empty()) b--;
      else{
        int v = bucket[b].back(); bucket[b].pop_back();
        active[v] = false; discharge(v);
    } /*else*/ } /*while*/ return excess[t];
  }
};