// Not Directed / Cycle
constexpr int SZ = 1010;
int N, G[SZ][SZ], Deg[SZ], Work[SZ];
void DFS(int v){
  for(int &i=Work[v]; i<=N; i++) while(G[v][I]) G[v][i]--, G[i][v]--, DFS(i);
  cout << v << " ";
}
// Directed / Path
void DFS(int v){
  for(int i=1; i<=pv; i++) while(G[v][i]) G[v][i]--, DFS(i);
  Path.push_back(v);
}
void Get(){
  for(int i=1; i<=pv; i++) if(In[i] < Out[i]){ DFS(i); return; }
  for(int i=1; i<=pv; i++) if(Out[i]){ DFS(i); return; }
}// WARNING: path.size() == M + 1 && not trail