#define zer(x) memset(x, 0, sizeof x)
#define fu(x) memset(x, -1, sizeof x)
int n;
vector<int> g[SZ];
int match[SZ], par[SZ], chk[SZ], gid[SZ], color[SZ];
void addEdge(int s, int e){
  g[s].push_back(e); g[e].push_back(s);
}
int lca_chk[SZ], pv;
int lca(int rt, int u, int v){ pv++;
  while(u != rt) lca_chk[u] = pv, u = gid[par[match[u]]];
  while(v != rt){
    if(lca_chk[v] == pv) return v; v = gid[par[match[v]]];
  }
  return rt;
}
void group(int l, int u, int v){
  while(l != gid[u]){
    int vv = match[u], uu = par[vv];
    chk[vv] = 1; par[u] = v; gid[u] = gid[vv] = l;
    u = uu; v = vv;
  }
}
void add_match(int rt, int v){
  while(par[v] != rt){
    int p = par[v], vv = match[p];
    match[v] = p; match[p] = v; match[vv] = 0;
    v = vv;
  }
  match[v] = rt; match[rt] = v;
}
int arg(int st){
  zer(par); zer(chk); fu(color); iota(gid, gid+SZ, 0);
  queue<int> q; q.push(st); chk[st] = 1; color[st] = 0;
  while(q.size()){
    int v = q.front(); q.pop();
    for(auto i : g[v]){
      if(color[i] == -1){
        par[i] = v; color[i] = 1;
        if(!match[i]){ add_match(st, i); return 1; }
        color[match[i]] = 0; chk[match[i]] = 1;
        q.push(match[i]);
      }
      else if(!color[i] && gid[v] != gid[i]){
        int l = lca(gid[st], gid[v], gid[i]);
        group(l, v, i); group(l, i, v);
        for(int j=1; j<=n; j++) if(chk[j] && color[j])
          color[j] = 0, q.push(j);
      }
    }
  }
  return 0;
}
int run(int _n){
  n = _n; int ret = 0;
  for(int i=1; i<=n; i++) if(!match[i] && arg(i)) ret++;
  return ret;
}