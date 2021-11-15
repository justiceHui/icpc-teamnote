int P[_Sz], E[_Sz]; // Parent, Enemy
void clear(){ iota(P, P+_Sz, 0); memset(E, -1, sizeof E); }
int find(int v){}
bool merge(int u, int v){}
int set_friend(int u, int v){ return merge(u, v); }
int set_enemy(int u, int v){
  int ret = 0;
  if(E[u] == -1) E[u] = v;
  else ret += merge(E[u], v);
  if(E[v] == -1) E[v] = u;
  else ret += merge(u, E[v]);
  return ret;
}