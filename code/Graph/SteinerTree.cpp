/**
https://github.com/tzupengwang/PECaveros/blob/master/codebook/graph/MinimumSteinerTree.cpp
*/

struct SteinerTree{ // O(E + V^3 + V 3^T + V^2 2^T)
  constexpr static int V = 33, T = 8;
  int n, G[V][V], D[1<<T][V], tmp[V];
  void init(int _n){ n = _n;
    memset(G, 0x3f, sizeof G); for(int i=0; i<n; i++) G[i][i]=0;
  } void shortest_path(){ /*floyd 0..n-1*/ }
  void add_edge(int u, int v, int w){
    G[u][v] = G[v][u] = min(G[v][u], w); }
  int solve(const vector<int>& ter){
    int t = (int)ter.size(); memset(D, 0x3f, sizeof D);
    for(int i=0; i<n; i++) D[0][i] = 0;
    for(int msk=1; msk<(1 << t); msk++){
      if(msk == (msk & (-msk))){ int who = __lg(msk);
        for(int i=0; i<n; i++) D[msk][i] = G[ter[who]][i];
        continue;
      }
      for(int i=0; i<n; i++)
        for(int sub=(msk-1)&msk; sub; sub=(sub-1)&msk)
          D[msk][i] = min(D[msk][i], D[sub][i] + D[msk^sub][i]);
      memset(tmp, 0x3f, sizeof tmp);
      for(int i=0; i<n; i++) for(int j=0; j<n; j++)
        tmp[i] = min(tmp[i], D[msk][j] + G[j][i]);
      for(int i=0; i<n; i++) D[msk][i] = tmp[i];
    }
    return *min_element(D[(1<<t)-1], D[(1<<t)-1]+n);
  }
};