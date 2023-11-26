/**
 * Author: ?
 * License: 
 * Source: ?
 * Description: 
 * Problem: https://judge.yosupo.jp/problem/assignment
 * Code: https://judge.yosupo.jp/submission/173682
 */

// 1-based, only for min matching, max matching may get TLE
template<typename cost_t=int, cost_t _INF=0x3f3f3f3f>
struct Hungarian{
  int n; vector<vector<cost_t>> mat;
  Hungarian(int n) : n(n), mat(n+1, vector<cost_t>(n+1, _INF)) {}
  void addEdge(int s, int e, cost_t x){ mat[s][e] = min(mat[s][e], x); }
  pair<cost_t, vector<int>> run(){
    vector<cost_t> u(n+1), v(n+1), m(n+1);
    vector<int> p(n+1), w(n+1), c(n+1);
    for(int i=1,a,b; i<=n; i++){
      p[0] = i; b = 0; fill(m.begin(), m.end(), _INF); fill(c.begin(), c.end(), 0);
      do{
        int nxt; cost_t delta = _INF; c[b] = 1; a = p[b];
        for(int j=1; j<=n; j++){
          if(c[j]) continue;
          cost_t t = mat[a][j] - u[a] - v[j];
          if(t < m[j]) m[j] = t, w[j] = b;
          if(m[j] < delta) delta = m[j], nxt = j;
        }
        for(int j=0; j<=n; j++){
          if(c[j]) u[p[j]] += delta, v[j] -= delta; else m[j] -= delta;
        }
        b = nxt;
      }while(p[b] != 0);
      do{int nxt = w[b]; p[b] = p[nxt]; b = nxt;}while(b!=0);
    }
    vector<int> assign(n+1);for(int i=1;i<=n;i++)assign[p[i]]=i;
    return {-v[0], assign};
  }
};