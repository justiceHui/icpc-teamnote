struct LR_Flow{ LR_Flow(int n) : F(n+2), S(0) {}
  void add_edge(int s, int e, flow_t l, flow_t r){
    S += abs(l); F.add_edge(s+2, e+2, r-l);
    if(l > 0) F.add_edge(s+2, 1, l), F.add_edge(0, e+2, l);
    else F.add_edge(0, s+2, -l), F.add_edge(e+2, 1, -l);
  } Dinic<flow_t, MAX_U> F; flow_t S;
  bool solve(int s, int t){//maxflow: run F.maximum_flow(s, t)
    if(s != -1) F.add_edge(t+2, s+2, MAX_U); //min cost circ
    return F.maximum_flow(0,1) == S; }
  flow_t get_flow(int s, int e) const { s += 2; e += 2;
    for(auto i : F.g[s]) if(i.c > 0 && i.v == e) return i.f; }
}; struct Circulation{ // demand[i] = in[i] - out[i]
  Circulation(int n, const vector<flow_t> &demand) : F(n+2) {
    // demand[i] > 0: add_edge(0, i+2, demand[i], demand[i])
    // demand[i] <= 0: add_edge(i+2, 1, -demand[i], demand[i])
  } LR_Flow<flow_t, MAX_U> F;
  void add_edge(int s, int e, flow_t l, flow_t r){
    F.add_edge(s+2, e+2, l, r); }
  bool feasible(){ return F.feasible(0, 1); } };