const int S = 333;
vector<int> g[S];
int dst[S], l[S], r[S], chk[S];
void clear(){ for(int i=0; i<S; i++) g[i].clear(); }
void addEdge(int s, int e){ g[s].push_back(e); }
int bfs(int n){
  queue<int> q; int ret = 0;
  memset(dst, 0, sizeof dst);
  for(int i=1; i<=n; i++) if(l[i] == -1 && !dst[i])
    q.push(i); dst[i] = 1;
  while(!q.empty()){
    int v = q.front(); q.pop();
    for(auto i : g[v]){
      if(r[i] == -1) ret = 1;
      else if(!dst[r[i]]) dst[r[i]] = dst[v] + 1, q.push(r[i]);
    }
  }
  return ret;
}
int dfs(int v){
  if(chk[v]) return 0; chk[v] = 1;
  for(auto i : g[v]){
    if(r[i] == -1 || !chk[r[i]] && dst[r[i]] == dst[v]+1 && dfs(r[i])){
      l[v] = i; r[i] = v; return 1;
    }
  }
  return 0;
}
int match(int n){
  memset(l, -1, sizeof l); memset(r, -1, sizeof r);
  int ret = 0;
  while(bfs(n)){
    memset(chk, 0, sizeof chk);
    for(int i=1; i<=n; i++) if(l[i] == -1 && dfs(i)) ret++;
  }
  return ret;
}
int track[S+S];
void rdfs(int v, int n){
  if(track[v]) return; track[v] = 1;
  for(auto i : g[v]) track[i+n] = 1, rdfs(r[i], n);
}
vector<int> getCover(int n, int m){
  match(n); memset(track, 0, sizeof track);
  for(int i=1; i<=n; i++) if(l[i] == -1) rdfs(i, n);
  vector<int> ret;
  for(int i=1; i<=n; i++) if(!track[i]) ret.push_back(i);
  for(int i=n+1; i<=n+m; i++) if(track[i]) ret.emplace_back(i);
  return ret;
}