template<typename FlowType, size_t _Sz, FlowType _Inf=1'000'000'007>
struct Dinic{
  struct Edge{ int v, dual; FlowType c; };
  int Level[_Sz], Work[_Sz];
  vector<Edge> G[_Sz];
  void clear(){ for(int i=0; i<_Sz; i++) G[i].clear(); }
  void AddEdge(int s, int e, FlowType x){
    G[s].push_back({e, (int)G[e].size(), x});
    G[e].push_back({s, (int)G[s].size()-1, 0});
  }
  bool BFS(int S, int T){
    memset(Level, 0, sizeof Level);
    queue<int> Q; Q.push(S); Level[S] = 1;
    while(Q.size()){
      int v = Q.front(); Q.pop();
      for(const auto &i : G[v]){
        if(!Level[i.v] && i.c) Q.push(i.v), Level[i.v] = Level[v] + 1;
      }
    }
    return Level[T];
  }
  FlowType DFS(int v, int T, FlowType tot){
    if(v == T) return tot;
    for(int &_i=Work[v]; _i<G[v].size(); _i++){
      Edge &i = G[v][_i];
      if(Level[i.v] != Level[v] + 1 || !i.c) continue;
      FlowType fl = DFS(i.v, T, min(tot, i.c));
      if(!fl) continue;
      i.c -= fl; G[i.v][i.dual].c += fl;
      return fl;
    }
    return 0;
  }
  FlowType MaxFlow(int S, int T){
    FlowType ret = 0, tmp;
    while(BFS(S, T)){
      memset(Work, 0, sizeof Work);
      while((tmp = DFS(S, T, _Inf))) ret += tmp;
    }
    return ret;
  }
  tuple<FlowType, vector<int>, vector<int>> MinCut(int S, int T){
    FlowType fl = MaxFlow(S, T);
    vector<int> a, b;
    const int Bias = 1e9;
    queue<int> Q; Q.push(S); Level[S] += Bias;
    while(Q.size()){
      int v = Q.front(); Q.pop();
      for(const auto &i : G[v]){
        if(Level[i.v] < Bias) Q.push(i.v), Level[i.v] += Bias;
      }
    }
    for(int i=0; i<_Sz; i++){
      if(Level[i]) a.push_back(i);
      else b.push_back(i);
    }
    return make_tuple(fl, a, b);
  }
};