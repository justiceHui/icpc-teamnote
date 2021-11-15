vector<int> G[MAX_V];
int In[MAX_V], Low[MAX_V], P[MAX_V];
void addEdge(int s, int e){
  G[s].push_back(e); G[e].push_back(s);
}
void tarjan(int n){ /// Pre-Process
  int pv = 0;
  function<void(int,int)> dfs = [&pv,&dfs](int v, int b){
    In[v] = Low[v] = ++pv; P[v] = b;
    for(auto i : G[v]){
      if(i == b) continue;
      if(!In[i]) dfs(i, v), Low[v] = min(Low[v], Low[i]);
      else Low[v] = min(Low[v], In[i]);
    }
  };
  for(int i=1; i<=n; i++) if(!In[i]) dfs(i, -1);
}
vector<int> cutVertex(int n){
  vector<int> res;
  array<char,MAX_V> isCut;
  function<void(int)> dfs = [&dfs,&isCut](int v){
    int ch = 0;
    for(auto i : G[v]){
      if(P[i] != v) continue;
      dfs(i); ch++;
      if(P[v] == -1 && ch > 1) isCut[v] = 1;
      else if(P[v] != -1 && Low[i] >= In[v]) isCut[v] = 1;
    }
  };
  for(int i=1; i<=n; i++) if(P[i] == -1) dfs(i);
  for(int i=1; i<=n; i++) if(isCut[i]) res.push_back(i);
  return move(res);
}
vector<PII> cutEdge(int n){
  vector<PII> res;
  function<void(int)> dfs = [&dfs,&res](int v){
    for(auto i : G[v]){
      if(P[i] != v) continue;
      dfs(i);
      if(Low[i] > In[v]) res.emplace_back(min(v,i), max(v,i));
    }
  };
  for(int i=1; i<=n; i++) if(P[i] == -1) dfs(i);
  return move(res); // sort(all(res));
}
vector<int> BCC[MAX_V]; // BCC[v] = components which contains v
void vertexDisjointBCC(int n){
  int cnt = 0;
  array<char,MAX_V> vis;
  function<void(int,int)> dfs = [&dfs,&vis,&cnt](int v, int c){
    if(c > 0) BCC[v].push_back(c);
    vis[v] = 1;
    for(auto i : G[v]){
      if(vis[i]) continue;
      if(In[v] < In[i]) BCC[v].push_back(++cnt), dfs(i, cnt);
      else dfs(i, c);
    }
  };
  for(int i=1; i<=n; i++) if(!vis[i]) dfs(i, ++cnt);
}
void edgeDisjointBCC(int n){} // remove cut edge, do flood fill