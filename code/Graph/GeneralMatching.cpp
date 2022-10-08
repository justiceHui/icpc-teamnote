int N, M, R, Match[555], Par[555], Chk[555], Prv[555], Vis[555];
vector<int> G[555];
int Find(int x){ return x == Par[x] ? x : Par[x] = Find(Par[x]); }
int LCA(int u, int v){ static int cnt = 0;
  for(cnt++; Vis[u]!=cnt; swap(u, v)) if(u) Vis[u] = cnt, u = Find(Prv[Match[u]]);
  return u;
}
void Blossom(int u, int v, int rt, queue<int> &q){
  for(; Find(u)!=rt; u=Prv[v]){
    Prv[u] = v; Par[u] = Par[v=Match[u]] = rt; if(Chk[v] & 1) q.push(v), Chk[v] = 2;
  }
}
bool Augment(int u){
  iota(Par, Par+555, 0); memset(Chk, 0, sizeof Chk); queue<int> Q; Q.push(u); Chk[u] = 2;
  while(!Q.empty()){
    u = Q.front(); Q.pop();
    for(auto v : G[u]){
      if(Chk[v] == 0){
        Prv[v] = u; Chk[v] = 1; Q.push(Match[v]); Chk[Match[v]] = 2;
        if(!Match[v]){ for(; u; v=u) u = Match[Prv[v]], Match[Match[v]=Prv[v]] = v; return true; }
      }
      else if(Chk[v] == 2){ int l = LCA(u, v); Blossom(u, v, l, Q), Blossom(v, u, l, Q); }
    }
  }
  return 0;
}
void Run(){ for(int i=1; i<=N; i++) if(!Match[i]) R += Augment(i); }