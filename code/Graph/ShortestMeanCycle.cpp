/**
 * Author: Aeren
 * License: 
 * Source: https://github.com/Aeren1564/Algorithms/blob/master/Algorithm_Implementations_Cpp/Graph_Theory/Shortest_Path_Algorithms/Minimum_Mean_Weight_Cycle/minimum_mean_weight_cycle.sublime-snippet
 * Problem: https://www.acmicpc.net/problem/14747
 * Code: http://boj.kr/1ffe0669a9014a61b7002d04330304f7
 */

template<typename T, T INF> vector<int> // T = V*E*max(C)
min_mean_cycle(int n, const vector<tuple<int,int,T>> &edges){
  vector<vector<T>>dp(n+1,vector<T>(n,INF)); // int support!
  vector<vector<int>>pe(n+1,vector<int>(n,-1));
  fill(dp[0].begin(),dp[0].end(),0); //0-based,directed
  for(int x=1; x<=n; x++){ int id=0; // bellman
    for(auto [u,v,w] : edges){
      if(dp[x-1][u] != INF && dp[x-1][u] + w < dp[x][v])
        dp[x][v] = dp[x-1][u] + w, pe[x][v] = id;
    id++; } // range based for end!
  } T p=1; int q=0, src=-1; //fraction
  for(auto u=0; u<n; u++){ if(dp[n][u] == INF) continue;
    T cp=-1, cq=0; // ↓ overflow!!!
    for(int x=0;x<=n;x++)if(cp*(n-x) < (dp[n][u]-dp[x][u])*cq)
      cp = dp[n][u] - dp[x][u], cq = n - x;
    if(p * cq > cp * q) src = u, p = cp, q = cq;
  } if(src == -1) return {};
  vector<int> res, po(n, -1);
  for(int u=src, x = n; ; u=get<0>(edges[pe[x--][u]])){
    if(po[u] != -1)return vector<int>{res.rbegin(),res.rend()-po[u]};
    po[u] = res.size(); res.push_back(pe[x][u]);
  } assert(false);
} // return edge index