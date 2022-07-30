vector<int> G[SzL]; void AddEdge(int s, int e){ G[s].push_back(e); }
int D[SzL], L[SzL], R[SzR];
bitset<SzL> Visit; bitset<SzL+SzR> Track;
void clear(){ for(int i=0; i<SzL; i++) G[i].clear(); Track.reset(); }
bool BFS(int N){
  bool ret = false;
  queue<int> Q; memset(D, 0, sizeof D);
  for(int i=1; i<=N; i++) if(L[i] == -1 && !D[i]) Q.push(i), D[i] = 1;
  while(Q.size()){
    int v = Q.front(); Q.pop();
    for(const auto &i : G[v]){
      if(R[i] == -1) ret = true;
      else if(!D[R[i]]) D[R[i]] = D[v] + 1, Q.push(R[i]);
    }
  }
  return ret;
}
bool DFS(int v){
  if(Visit[v]) return false; Visit[v] = true;
  for(const auto &i : G[v]){
    if(R[i] == -1 || !Visit[R[i]] && D[R[i]] == D[v] + 1 && DFS(R[i])){ L[v] = i; R[i] = v; return true; }
  }
  return false;
}
int Match(int N){
  int ret = 0; memset(L, -1, sizeof L); memset(R, -1, sizeof R);
  while(BFS(N)){
    Visit.reset(); for(int i=1; i<=N; i++) if(L[i] == -1 && DFS(i)) ret++;
  }
  return ret;
}
void DFS2(int v, int N){
  if(Track[v]) return; Track[v] = true;
  for(const auto &i : G[v]) Track[i+N] = true, DFS2(R[i], N);
}
pair<vector<int>, vector<int>> MinVertexCover(int N, int M){
  Match(N); for(int i=1; i<=N; i++) if(L[i] == -1) DFS2(i, N);
  vector<int> a, b;
  for(int i=1; i<=N; i++) if(!Track[i]) a.push_back(i);
  for(int i=N+1; i<=N+M; i++) if(Track[i]) b.push_back(i-N);
  return make_pair(a, b);
}