int vertex, g[S][S], dst[S], chk[S], del[S];
void init(){
  memset(g, 0, sizeof g); memset(del, 0, sizeof del);
}
void addEdge(int s, int e, int x){ g[s][e] = g[e][s] = x; }
int minCutPhase(int &s, int &t){
  memset(dst, 0, sizeof dst);
  memset(chk, 0, sizeof chk);
  int mincut = 0;
  for(int i=1; i<=vertex; i++){
    int k = -1, mx = -1;
    for(int j=1; j<=vertex; j++) if(!del[j] && !chk[j])
      if(dst[j] > mx) k = j, mx = dst[j];
    if(k == -1) return mincut;
    s = t, t = k;
    mincut = mx, chk[k] = 1;
    for(int j=1; j<=vertex; j++){
      if(!del[j] && !chk[j]) dst[j] += g[k][j];
    }
  }
  return mincut;
}
int getMinCut(int n){
  vertex = n; int mincut = 1e9+7;
  for(int i=1; i<vertex; i++){
    int s, t;
    int now = minCutPhase(s, t);
    mincut = min(mincut, now); del[t] = 1;
    if(mincut == 0) return 0;
    for(int j=1; j<=vertex; j++){
      if(!del[j]) g[s][j] = (g[j][s] += g[j][t]);
    }
  }
  return mincut;
}