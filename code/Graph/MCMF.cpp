template<typename FlowType, typename CostType, int _Sz, FlowType _Inf_flow, CostType _Inf_cost>
struct MCMF{
  struct Edge{ int nxt; FlowType cap; CostType cst; int rev; };
  vector<Edge> G[_Sz];
  bitset<_Sz> Visit;
  CostType Dist[_Sz];
  int Used[_Sz];
  void AddEdge(int s, int e, FlowType cap, CostType cst){
    G[s].push_back({e, cap, cst, SZ(G[e])});
    G[e].push_back({s, 0, -cst, SZ(G[s])-1});
  }
  void Init(const int S, const int T){
    fill(Dist, Dist+_Sz, _Inf_cost);
    queue<int> Q;
    bitset<_Sz> InQ;
    Q.push(S); InQ[S] = true; Dist[S] = 0;
    while(!Q.empty()){
      int now = Q.front(); Q.pop(); InQ[now] = false;
      for(const auto &i : G[now]){
        if(i.cap > 0 && Dist[i.nxt] > Dist[now] + i.cst){
          Dist[i.nxt] = Dist[now] + i.cst;
          if(!InQ[i.nxt]) InQ[i.nxt] = true, Q.push(i.nxt);
        }
      }
    }
  }
  bool Update(){
    CostType fix = _Inf_cost;
    for(int i=0; i<_Sz; i++){
      if(!Visit[i]) continue;
      for(const auto &j : G[i]){
        if(j.cap && !Visit[j.nxt]) fix = min(fix, Dist[i] + j.cst - Dist[j.nxt]);
      }
    }
    if(fix == _Inf_cost) return false;
    for(int i=0; i<_Sz; i++) if(!Visit[i]) Dist[i] += fix;
    return true;
  }
  FlowType DFS(int now, int sink, FlowType fl){
    Visit[now] = true;
    if(now == sink) return fl;
    for(; Used[now] < G[now].size(); Used[now]++){
      auto &i = G[now][Used[now]];
      if(!Visit[i.nxt] && i.cap > 0 && Dist[i.nxt] == Dist[now] + i.cst){
        FlowType ret = DFS(i.nxt, sink, min(fl, i.cap));
        if(ret > 0){
          i.cap -= ret;
          G[i.nxt][i.rev].cap += ret;
          return ret;
        }
      }
    }
    return 0;
  }
  pair<FlowType, CostType> MinCostFlow(int S, int T){
    FlowType flow = 0, tmp;
    CostType cost = 0;
    Init(S, T);
    do{
      Visit.reset();
      memset(Used, 0, sizeof Used);
      while((tmp = DFS(S, T, _Inf_flow))){
        flow += tmp;
        cost += tmp * Dist[T];
        Visit.reset();
      }
    }while(Update());
    return make_pair(flow, cost);
  }
};