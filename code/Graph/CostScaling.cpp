/**
 * Author: koosaga
 * License: 
 * Source: https://judge.yosupo.jp/submission/86332
 * Description: 
 * Problem 1: https://judge.yosupo.jp/problem/min_cost_b_flow
 * Code 1: https://judge.yosupo.jp/submission/190223
 */

template <class T> struct MinCostCirculation {
  const int SCALE = 3; // scale by 1/(1 << SCALE)
  const T INF = numeric_limits<T>::max() / 2;
  struct EdgeStack { int s, e; T l, r, cost; };
  struct Edge { int pos, rev; T rem, cap, cost; };
  int n; vector<vector<Edge>> g; vector<EdgeStack> estk;
  LR_Flow<T, 1LL<<60> circ; vector<T> p;
  MinCostCirculation(int k) : n(k), g(k), circ(k), p(k) {}
  void add_edge(int s, int e, T l, T r, T cost){
    estk.push_back({s, e, l, r, cost}); }
  pair<bool, T> solve(){
    for(auto &i:estk)if(i.s!=i.e)circ.add_edge(i.s,i.e,i.l,i.r);
    if(!circ.solve(-1, -1)) return make_pair(false, T(0));
    vector<int> cnt(n); T eps = 0;
    for(auto &i : estk){ T curFlow;
      auto &edge = circ.F.g[i.s+2][cnt[i.s]];
      if(i.s != i.e) curFlow = i.r - (edge.c - edge.f);
      else curFlow = i.r;
      int srev = sz(g[i.e]), erev = sz(g[i.s]);
      if(i.s == i.e) srev++;
    g[i.s].push_back(i.e,srev,+i.r-curFlow,+i.r,+i.cost*(n+1));
    g[i.e].push_back(i.s,erev,-i.l+curFlow,-i.l,-i.cost*(n+1));
      eps = max(eps, abs(i.cost) * (n+1));
      if(i.s != i.e) cnt[i.s] += 2, cnt[i.e] += 2;
    }
    while(true){ eps=0; auto cost=[&](Edge &e, int s, int t){
        return e.cost + p[s] - p[t]; };
      for(int i = 0; i < n; i++) for(auto &e : g[i])
        if(e.rem > 0) eps = max(eps, -cost(e, i, e.pos));
      if(eps <= T(1)) break;
      eps = max(T(1), eps >> SCALE);
      vector<T> excess(n); queue<int> que;
      auto push = [&](Edge &e, int src, T flow){
        e.rem -= flow; g[e.pos][e.rev].rem += flow;
        excess[src] -= flow; excess[e.pos] += flow;
        if(excess[e.pos] <= flow && excess[e.pos] > 0) que.push(e.pos);
      }; vector<int> ptr(n);
      auto relabel = [&](int v){
        ptr[v] = 0; p[v] = -INF;
        for(auto &e : g[v])
          if(e.rem>0) p[v] = max(p[v], p[e.pos]-e.cost-eps);
      };
      for(int i = 0; i < n; i++) for(auto &j : g[i])
        if(j.rem>0 && cost(j, i, j.pos)<0) push(j, i, j.rem);
      while(sz(que)){
        int x = que.front(); que.pop();
        while(excess[x] > 0){
          for(; ptr[x] < sz(g[x]); ptr[x]++){
            Edge &e = g[x][ptr[x]];
            if(e.rem > 0 && cost(e, x, e.pos) < 0){
              push(e, x, min(e.rem, excess[x]));
              if(excess[x] == 0) break;
          } /* if end */ } /* for end*/
          if(excess[x] == 0) break; relabel(x);
      } /* excess end */  } /* que end */
    } /* while true end */ T ans = 0;
    for(int i=0; i<n; i++) for(auto &j : g[i])
      j.cost /= n + 1, ans += j.cost * (j.cap - j.rem);
    return make_pair(true, ans / 2);
  }
  void bellmanFord(){
    fill(p.begin(), p.end(), T(0)); bool upd = 1;
    while(upd){ upd = 0;
      for(int i = 0; i < n; i++) for(auto &j : g[i])
        if(j.rem > 0 && p[j.pos] > p[i] + j.cost) p[j.pos] = p[i] + j.cost, upd = 1;
    }
  }
};