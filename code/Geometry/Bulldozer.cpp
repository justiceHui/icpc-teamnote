Point v[2020];
struct Line{
  ll i, j, dx, dy;
  Line(int i, int j) : i(i), j(j) {
    dx = v[i].x - v[j].x; dy = v[i].y - v[j].y;
  }
  bool operator < (const Line &t) const {
    ll a = dy * t.dx, b = t.dy * dx;
    return tie(a, i, j) < tie(b, t.i, t.j);
  }
};
int ccw(Point a, Point b, Point c){}
int ccw(Line a, Line b){
  ll res = a.dx*b.dy - b.dx*a.dy;
  if(!res) return 0; return res > 0 ? 1 : -1;
}
int idx[2020]; vector<Line> line;
void bulldozer(int n){
  sort(v+1, v+n+1); for(int i=1; i<=n; i++) idx[i] = i;
  for(int i=1; i<=n; i++) for(int j=1; j<i; j++) line.emplace_back(i, j);
  for(int i=0, j=0; i<line.size(); ){
    int ed = i;
    while(ed < line.size() && !ccw(line[i], line[ed])) ed++;
    for(int j=i; j<ed; j++){
      int a = line[j].i, b = line[j].j;
      swap(idx[a], idx[b]); swap(v[idx[a]], v[idx[b]]);
      update(idx[a]); update(idx[b]);
    }
    ans = merge(ans, query()); i = ed;
  }
}