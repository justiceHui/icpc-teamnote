/**
 * Author: JusticeHui
 * License: CC BY-NC-SA
 * Source: JusticeHui
 * Description: convert tree to binary tree
 * Problem: https://www.acmicpc.net/problem/16121
 * Code: http://boj.kr/be6512eb39b940f7aadf1d12b97137fe
 */

void make_binary(int v=1, int real=1, int b=-1, int idx=0){
  for(int t=idx; t<Inp[v].size(); t++){
    auto i = Inp[v][t]; if(i.first == b) continue;
    if(G[real].empty() || t+1 == Inp[v].size()
       || t+2 == Inp[v].size() && Inp[v][t+1].first == b){
      G[real].push_back(i);//do not change order!!!
      make_binary(i.first, i.first, v);
      G[i.first].emplace_back(real, i.second);
      continue;
    } int nxt = N + ++pv;;//do not change order!!!
    G[real].emplace_back(nxt, 0);
    make_binary(v, nxt, b, t);
    G[nxt].emplace_back(real, 0);
    break;
  }
}