/**
 * Author: JusticeHui
 * License: CC BY-NC-SA
 * Source: JusticeHui
 * Description: represent friend/enemy relationships using union-find
 * Problem: https://www.acmicpc.net/problem/1765
 * Code: http://boj.kr/a33e3295cdc5402084be0982a3d10ac0
 */

int P[_Sz], E[_Sz];//Par,Enemy,iota(P,0),fill(E,-1)
int find(int v){} bool merge(int u, int v){}
int set_friend(int u, int v){ return merge(u, v); }
int set_enemy(int u, int v){ int ret = 0;
  if(E[u] == -1) E[u] = v; else ret += merge(E[u], v);
  if(E[v] == -1) E[v] = u; else ret += merge(u, E[v]);
  return ret;
}