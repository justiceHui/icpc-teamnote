const int MV = 101010, ME = 101010; // MAX_V, MAX_E
p pt[MV]; // vertex's coord
vector<p> g[MV]; // g[s].emplace_back(e, edge_id);
vector<int> dual_pt; // coord compress
int par[ME * 2]; // Union Find
void uf_init(){ iota(par, par+ME*2, 0); }
int find(int v){return v == par[v] ? v : par[v] = find(par[v]);}
void merge(int u, int v){ u = find(u); v = find(v); if(u != v)par[u] = v; }
p base; // sort by angle
bool cmp_angle(const p &_a, const p &_b){
  p a = pt[_a.x], b = pt[_b.x];
  if((a > base) != (b > base)) return a > b;
  return ccw(a, base, b) > 0;
}
void addEdge(int s, int e, int id){
  g[s].emplace_back(e, id); g[e].emplace_back(s, id);
}
int out; //outer face
void getDual(int n, int m){
  uf_init();
  for(int i=1; i<=n; i++){
    base = pt[i]; sort(all(g[i]), cmp_angle);
    // up, left : *2+1 / down, right : *2
    for(int j=0; j<g[i].size(); j++){
      int k = j ? j - 1 : g[i].size()-1;
      int u = g[i][k].y << 1 | 1, v = g[i][j].y << 1;
      p p1 = pt[g[i][k].x], p2 = pt[g[i][j].x];
      if(p1 > base) u ^= 1;
      if(p2 > base) v ^= 1;
      merge(u, v);
    }
  }
  int mn_idx = min_element(pt+1, pt+n+1) - pt;
  out = find(g[mn_idx][0].y << 1 | 1);
  for(int i=1; i<=m; i++){
    dual_pt.push_back(find(i << 1));
    dual_pt.push_back(find(i << 1 | 1));
  }
  compress(dual_pt);
  // @TODO coord compress
}