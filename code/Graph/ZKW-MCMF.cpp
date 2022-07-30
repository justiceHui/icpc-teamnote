const int SZ = 222;
struct MCMF{
  using FlowType = int;
  using CostType = int;
  const CostType cost_max = 1e9;
  int s, t;
  struct Edge{ int v, dual; FlowType c; CostType d; };
  vector<Edge> g[SZ];
  void addEdge(int s, int e, FlowType c, CostType d){
    g[s].push_back({e, (int)g[e].size(), c, d});
    g[e].push_back({s, (int)g[s].size()-1, 0, -d});
  }
  int inq[SZ]; CostType h[SZ];
  CostType dst[SZ];
  void init(int _s, int _t){
    s = _s, t = _t;
    fill(h, h+SZ, cost_max); fill(dst, dst+SZ, cost_max);
    queue<int> q; q.push(s); inq[s] = 1;
    while(q.size()){
      int now = q.front(); q.pop(); inq[now] = 0;
      for(auto i : g[now]) if(i.c && h[i.v] > h[now] + i.d) {
        h[i.v] = h[now] + i.d;
        if(!inq[i.v]) inq[i.v] = 1, q.push(i.v);
      }
    }
    for(int i=0; i<SZ; i++){
      for(auto &j : g[i]) if(j.c) j.d += h[i] - h[j.v];
    }
    priority_queue<pair<CostType, int>> pq; pq.emplace(0, s); dst[s] = 0;
    while(pq.size()){
      int now = pq.top().y;
      CostType cst = -pq.top().x;
      pq.pop();
      if(dst[now] != cst) continue;
      for(auto i : g[now]) if(i.c && dst[i.v] > dst[now] + i.d) {
        dst[i.v] = dst[now] + i.d; pq.emplace(-dst[i.v], i.v);
      }
    }
    for(int i=0; i<SZ; i++) dst[i] += h[t] - h[s];
  }
  int chk[SZ], work[SZ];
  bool update(){
    CostType mn = cost_max;
    for(int i=0; i<SZ; i++) if(chk[i]) {
      for(auto j : g[i]) if(j.c && !chk[j.v]) {
        mn = min(mn, dst[i] + j.d - dst[j.v]);
      }
    }
    if(mn == cost_max) return 0;
    for(int i=0; i<SZ; i++) if(!chk[i]) dst[i] += mn;
    return 1;
  }
  FlowType dfs(int now, FlowType fl){
    chk[now] = 1;
    if(now == t) return fl;
    for(; work[now] < g[now].size(); work[now]++){
      auto &i = g[now][work[now]];
      if(!chk[i.v] && dst[i.v] == dst[now] + i.d && i.c){
        FlowType ret = dfs(i.v, min(fl, i.c));
        if(ret > 0){
          i.c -= ret; g[i.v][i.dual].c += ret;
          return ret;
        }
      }
    }
    return 0;
  }
  pair<CostType, FlowType> run(int _s, int _t){ //{cost, flow}
    init(_s, _t);
    CostType cst = 0; FlowType fl = 0, now;
    do{
      memset(chk, 0, sizeof chk);
      memset(work, 0, sizeof work);
      while((now = dfs(s, 1e9)) > 0){
        cst += dst[t] * now; fl += now;
        memset(chk, 0, sizeof chk);
      }
    }while(update());
    return {cst, fl};
  }
};