struct Tree{ // (M1,M2)=(1e9+7, 1e9+9), P1,P2 = random int array(sz >= N+2)
  int N; vector<vector<int>> G; vector<pair<int,int>> H; vector<int> S, C; // size,centroid
  Tree(int N) : N(N), G(N+2), S(N+2), H(N+2) {}
  void addEdge(int s, int e){ G[s].push_back(e); G[e].push_back(s); }
  int getCentroid(int v, int b=-1){
    S[v] = 1; // do not merge if
    for(auto i : G[v]) if(i!=b) if(int now=getCentroid(i,v); now<=N/2) S[v]+=now; else break;
    if(N - S[v] <= N/2) C.push_back(v); return S[v] = S[v];
  }
  int init(){
    getCentroid(1); if(C.size() == 1) return C[0];
    int u = C[0], v = C[1], add = ++N;
    G[u].erase(find(G[u].begin(), G[u].end(), v)); G[v].erase(find(G[v].begin(), G[v].end(), u));
    G[add].push_back(u); G[u].push_back(add); G[add].push_back(v); G[v].push_back(add);
    return add;
  }
  pair<int,int> build(const vector<ll> &P1, const vector<ll> &P2, int v, int b=-1){
    vector<pair<int,int>> ch; for(auto i : G[v]) if(i != b) ch.push_back(build(P1, P2, i, v));
    ll h1 = 0, h2 = 0; sort(ch.begin(), ch.end()); if(ch.empty()){ return {1, 1}; }
    for(int i=0; i<ch.size(); i++) h1=(h1+ch[i].first*P1[i])%M1, h2=(h2+ch[i].second*P2[i])%M2;
    return H[v] = {h1, h2};
  }
  int build(const vector<ll> &P1, const vector<ll> &P2){
    int rt = init(); build(P1, P2, rt); return rt;
  }
};