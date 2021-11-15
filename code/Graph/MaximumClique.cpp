int N, M; ull G[40], MX, Clique; // 0-index, adj list with bitset, O(3^{N/3})
void get_clique(int R = 0, ull P = (1ULL<<N)-1, ull X = 0, ull V=0){
  if((P|X) == 0){ if(R > MX) MX = R, Clique = V; return; }
  int u = __builtin_ctzll(P|X); ll c = P&~G[u];
  while(c){
    int v = __builtin_ctzll(c);
    get_clique(R + 1, P&G[v], X&G[v], V | 1ULL << v);
    P ^= 1ULL << v; X |= 1ULL << v; c ^= 1ULL << v;
  }
}