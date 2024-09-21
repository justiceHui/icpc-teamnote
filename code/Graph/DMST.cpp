/**
 * Author: std_abs
 * License: 
 * Source: https://github.com/abc864197532/std_abs/blob/main/codebook/Graph/DirectedMST.cpp
 * Description: 
 * Problem: https://judge.yosupo.jp/problem/directedmst
 * Code: https://judge.yosupo.jp/submission/184786
 */

using D = int; struct edge { int u, v; D w; };
vector<int> DirectedMST(vector<edge> &e, int n, int root){
  using T = pair<D, int>;  // 0-based, return index of edges
  using PQ = pair<priority_queue <T,vector<T>,greater<T>>, D>;
  auto push = [](PQ &pq, T v){ pq.first.emplace(v.first-pq.second, v.second); };
  auto top = [](const PQ &pq) -> T {
    auto r = pq.first.top(); return {r.first + pq.second, r.second}; };
  auto join = [&push, &top](PQ &a, PQ &b) {
    if(a.first.size() < b.first.size()) swap(a, b);
    while(!b.first.empty()) push(a, top(b)), b.first.pop(); };
  vector<PQ> h(n * 2);
  for(int i=0; i<e.size(); i++) push(h[e[i].v], {e[i].w, i});
  vector<int> a(n*2), v(n*2, -1), pa(n*2, -1), r(n*2);
  iota(a.begin(), a.end(), 0);
  auto o = [&](int x) { int y; for(y=x; a[y]!=y; y=a[y]);;;
    for(int ox=x; x!=y; ox=x) x = a[x], a[ox] = y;
    return y; };
  v[root] = n + 1; int pc = n;
  for(int i=0; i<n; i++) if(v[i] == -1) {
    for(int p=i; v[p]==-1 || v[p]==i; p=o(e[r[p]].u)){
      if(v[p] == i){ int q = p; p = pc++;
        do{ h[q].second = -h[q].first.top().first;
          join(h[pa[q]=a[q]=p], h[q]);
        }while((q=o(e[r[q]].u)) != p);
      } v[p] = i;
      while(!h[p].first.empty() && o(e[top(h[p]).second].u) == p) h[p].first.pop();
      r[p] = top(h[p]).second;
    }
  }
  vector<int> ans;
  for(int i=pc-1; i>=0; i--) if(i != root && v[i] != n) {
    for(int f=e[r[i]].v; f!=-1 && v[f]!=n; f=pa[f]) v[f] = n;;;
    ans.push_back(r[i]);
  }
  return ans;
}