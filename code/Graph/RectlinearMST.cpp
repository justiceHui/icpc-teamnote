/**
 * Author: aeren
 * License: 
 * Source: https://github.com/Aeren1564/Algorithms/blob/master/Algorithm_Implementations_Cpp/Geometry/Norm/rectilinear_minimum_spanning_tree.sublime-snippet
 * Description: 
 * Problem: https://judge.yosupo.jp/problem/manhattanmst
 * Code: https://judge.yosupo.jp/submission/173686
 */

template<class T> vector<tuple<T, int, int>>
rectilinear_minimum_spanning_tree(vector<point<T>> a){
  int n = a.size(); vector<int> ind(n);
  iota(ind.begin(),ind.end(),0); vector<tuple<T,int,int>> edge;
  for(int k=0; k<4; k++){ map<T, int> mp;
    sort(ind.begin(), ind.end(), [&](int i,int j){
      return a[i].x-a[j].x < a[j].y-a[i].y;});
    for(auto i: ind){
      for(auto it=mp.lower_bound(-a[i].y); it!=mp.end(); it=mp.erase(it)){
        int j = it->second; point<T> d = a[i] - a[j];
        if(d.y > d.x) break; edge.push_back({d.x+d.y,i,j});
      }
      mp.insert({-a[i].y, i});
    }
    for(auto &p: a) if(k & 1) p.x = -p.x; else swap(p.x, p.y);
  } /*for-k end*/ sort(edge.begin(), edge.end());
  disjoint_set dsu(n); vector<tuple<T, int, int>> res;
  for(auto [x, i, j]: edge) if(dsu.merge(i, j))
    res.push_back({x, i, j});
  return res; }