struct Line{
  static ll CUR_X; ll x1, y1, x2, y2, id;
  Line(Point p1, Point p2, int id) : id(id) {
    if(p1 > p2) swap(p1, p2);
    tie(x1,y1) = p1; tie(x2,y2) = p2;
  } Line() = default;
  int get_k() const { return y1 != y2 ? (x2-x1)/(y1-y2) : -1; }
  void convert_k(int k){ // x1,y1,x2,y2 = O(COORD^2), use i128 in ccw
    Line res;
    res.x1 = x1 + y1 * k; res.y1 = -x1 * k + y1;
    res.x2 = x2 + y2 * k; res.y2 = -x2 * k + y2;
    x1 = res.x1; y1 = res.y1; x2 = res.x2; y2 = res.y2;
    if(x1 > x2) swap(x1, x2), swap(y1, y2);
  }
  ld get_y(ll offset=0) const { // OVERFLOW
    ld t = ld(CUR_X-x1+offset) / (x2-x1);
    return t * (y2 - y1) + y1; }
  bool operator < (const Line &l) const {
    return get_y() < l.get_y(); }
  // strict
  /* bool operator < (const Line &l) const {
    auto le = get_y(), ri = l.get_y();
    if(abs(le-ri) > 1e-7) return le < ri;
    if(CUR_X==x1 || CUR_X==l.x1) return get_y(1)<l.get_y(1);
    else return get_y(-1) < l.get_y(-1);
  } */
}; ll Line::CUR_X = 0;
struct Event{ // f=0 st, f=1 ed
  ll x, y, i, f; Event() = default;
  Event(Line l, ll i, ll f) : i(i), f(f) {
    if(f==0) tie(x,y) = tie(l.x1,l.y1);
    else tie(x,y) = tie(l.x2,l.y2);
  }
  bool operator < (const Event &e) const {
    return tie(x,f,y) < tie(e.x,e.f,e.y);
    // strict
    // return make_tuple(x,-f,y) < make_tuple(e.x,-e.f,e.y);
  }
};
tuple<bool,int,int> ShamosHoey(vector<array<Point,2>> v){
  int n = v.size(); vector<int> use(n+1);
  vector<Line> lines; vector<Event> E; multiset<Line> T;
  for(int i=0; i<n; i++){
    lines.emplace_back(v[i][0], v[i][1], i);
    if(int t=lines[i].get_k(); 0<=t && t<=n) use[t] = 1;
  }
  int k = find(use.begin(), use.end(), 0) - use.begin();
  for(int i=0; i<n; i++){ lines[i].convert_k(k);
    E.emplace_back(lines[i], i, 0); E.emplace_back(lines[i], i, 1);
  } sort(E.begin(), E.end());
  for(auto &e : E){ Line::CUR_X = e.x;
    if(e.f == 0){
      auto it = T.insert(lines[e.i]);
      if(next(it) != T.end() && Intersect(lines[e.i], *next(it))) return {true, e.i, next(it)->id};
      if(it != T.begin() && Intersect(lines[e.i], *prev(it)))
        return {true, e.i, prev(it)->id};
    }
    else{
      auto it = T.lower_bound(lines[e.i]);
      if(it != T.begin() && next(it) != T.end() && Intersect(*prev(it), *next(it)))
        return {true, prev(it)->id, next(it)->id};
      T.erase(it);
    }
  }
  return {false, -1, -1};
}