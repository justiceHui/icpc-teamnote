struct Line{
  ll i, j, dx, dy; // dx >= 0
  Line(int i, int j, const Point &pi, const Point &pj)
    : i(i), j(j), dx(pj.x-pi.x), dy(pj.y-pi.y) {}
  bool operator < (const Line &l) const {
    return make_tuple(dy*l.dx, i, j) < make_tuple(l.dy*dx, l.i, l.j); }
  bool operator == (const Line &l) const {
    return dy * l.dx == l.dy * dx; }
};
void Solve(){ // V.reserve(N*(N-1)/2)
  sort(A+1, A+N+1); iota(P+1, P+N+1, 1); vector<Line> V;
  for(int i=1; i<=N; i++) for(int j=i+1; j<=N; j++)
    V.emplace_back(i, j, A[i], A[j]);
  sort(V.begin(), V.end());
  for(int i=0, j=0; i<V.size(); i=j){
    while(j < V.size() && V[i] == V[j]) j++;
    for(int k=i; k<j; k++){
      int u = V[k].i, v = V[k].j; // point id, index -> Pos[id]
      swap(Pos[u], Pos[v]); swap(A[Pos[u]], A[Pos[v]]);
      if(Pos[u] > Pos[v]) swap(u, v);
      // @TODO
    }
  }
}