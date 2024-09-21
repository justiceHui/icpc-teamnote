/**
 * Author: JusticeHui
 * License: CC BY-NC-SA
 * Source: JusticeHui
 * Description: 
 * Problem: https://www.acmicpc.net/problem/16216
 * Code: http://boj.kr/2994513f8637462ba4ac2b8d696d8d7b
 */

void Go(int v, const vector<int> vertex, vector<tuple<int,int,int>> &edge){
  static int pv = 1; // vertex is sorted by dfs order
  while(pv < vertex.size() && In[vertex[pv]] <= Out[v]){
    int nxt = vertex[pv++];
    edge.emplace_back(v, nxt, D[nxt]-D[v]);
    Go(nxt, vertex, edge);
  }}