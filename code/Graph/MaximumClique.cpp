/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm, https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/MaximalCliques.h
 * Description: callback for all maximal cliques in a graph
 * Problem: https://judge.yosupo.jp/problem/maximum_independent_set
 * Code: https://judge.yosupo.jp/submission/62943
 */

using B = bitset<128>; template<typename F> //0-based
void maximal_cliques(vector<B>&g,F f,B P=~B(),B X={},B R={}){
  if(!P.any()){ if(!X.any()) f(R); return; }
  auto q = (P|X)._Find_first(); auto c = P & ~g[q];
  for(int i=0; i<g.size(); i++) if(c[i]) {
    R[i] = 1; cliques(g, f, P&g[i], X&g[i], R);
    R[i]=P[i]=0; X[i] = 1; } // faster for sparse gph
} // undirected, self loop not allowed, O(3^{n/3})
B max_independent_set(vector<vector<int>> g){ //g=adj matrix
  int n = g.size(), i, j; vector<B> G(n); B res{};
  auto chk_mx = [&](B a){ if(a.count()>res.count()) res=a; };
  for(i=0; i<n; i++) for(int j=0; j<n; j++)
    if(i!=j && !g[i][j])G[i][j]=1;
  cliques(G, chk_mx); return res; }