struct Info{ // down a -> up b, a b >= 0
  ll a, b, idx; Info() : Info(0, 0, 0) {}
  Info(ll a, ll b, ll idx) : a(a), b(b), idx(idx) {}
  bool operator < (const Info &t) const {
    ll le = b - a, ri = t.b - t.a;
    if(le >= 0 && ri < 0) return false;
    if(le < 0 && ri >= 0) return true;
    if(le < 0 && b != t.b) return b < t.b;
    if(le >= 0 && a != t.a) return a > t.a;
    return idx < t.idx;
  }
  Info& operator += (const Info &v){
    ll aa = min(-a, -a+b-v.a), bb = -a+b-v.a+v.b;
    a = -aa; b = bb - aa; return *this;
  }
};
void MonsterHunter(int root=1){
  set<Info> T(A+1, A+N+1); T.erase(A[root]);
  while(!T.empty()){
    auto v = *T.rbegin(); T.erase(prev(T.end()));
    int now = v.idx, nxt = Find(Par[v.idx]); // @TODO
    UF[now] = nxt; T.erase(A[nxt]); A[nxt] += A[now];
    if(nxt != root) T.insert(A[nxt]);
  } // @TODO
}