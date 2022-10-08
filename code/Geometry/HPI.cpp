double CCW(p1, p2, p3); bool same(double a, double b); const Point o = Point(0, 0);
struct Line{
  double a, b, c; Line() : Line(0, 0, 0) {}
  Line(double a, double b, double c) : a(a), b(b), c(c) {}
  bool operator < (const Line &l) const {
    bool f1 = Point(a, b) > o, f2 = Point(l.a, l.b) > o;
    if(f1 != f2) return f1 > f2;
    double cw = CCW(o, Point(a, b), Point(l.a, l.b));
    return same(cw, 0) ? c * hypot(l.a, l.b) < l.c * hypot(a, b) : cw > 0;
  }
  Point slope() const { return Point(a, b); }
};
Point LineIntersect(Line a, Line b){
  double det = a.a*b.b - b.a*a.b, x = (a.c*b.b - a.b*b.c) / det, y = (a.a*b.c - a.c*b.a) / det;
  return Point(x, y);
}
bool CheckHPI(Line a, Line b, Line c){
  if(CCW(o, a.slope(), b.slope()) <= 0) return 0;
  Point v = LineIntersect(a, b); return v.x*c.a + v.y*c.b >= c.c;
}
vector<Point> HPI(vector<Line> v){
  sort(v.begin(), v.end());
  deque<Line> dq; vector<Point> ret;
  for(auto &i : v){
    if(dq.size() && same(CCW(o, dq.back().slope(), i.slope()), 0)) continue;
    while(dq.size() >= 2 && CheckHPI(dq[dq.size()-2], dq.back(), i)) dq.pop_back();
    while(dq.size() >= 2 && CheckHPI(i, dq[0], dq[1])) dq.pop_front();
    dq.push_back(i);
  }
  while(dq.size() > 2 && CheckHPI(dq[dq.size()-2], dq.back(), dq[0])) dq.pop_back();
  while(dq.size() > 2 && CheckHPI(dq.back(), dq[0], dq[1])) dq.pop_front();
  for(int i=0; i<dq.size(); i++){
    Line now = dq[i], nxt = dq[(i+1)%dq.size()];
    if(CCW(o, now.slope(), nxt.slope()) <= eps) return vector<Point>();
    ret.push_back(LineIntersect(now, nxt));
  }
  for(auto &[x,y] : ret) x = -x, y = -y;
  return ret;
}
template<bool GET_MAX=true> // max - upper hull, min - lower hull
Point GetPoint(const vector<Point> &hull, double dy, double dx){ // given slope
  if(hull.size() == 1) return hull.front();
  if(dx < 0) dx = -dx, dy = -dy;
  if(dx == 0) return GET_MAX == (dy > 0) ? hull.front() : hull.back();
  auto cmp = [&](double a, double b){ return GET_MAX ? a < b : a > b; };
  if(cmp((hull[1].y - hull[0].y) * dx, (hull[1].x - hull[0].x) * dy)) return hull.front();
  int l = 1, r = (int)hull.size() - 1;
  while(l < r){
    int m = (l + r + 1) / 2;
    if(cmp((hull[m].y - hull[m-1].y) * dx, (hull[m].x - hull[m-1].x) * dy)) r = m - 1;
    else l = m;
  }
  return hull[l];
}
int ConvexTangent(const vector<Point> &v, const Point &pt, int up=1){ //given outer point
  auto sign = [&](ll c){ return c > 0 ? up : c == 0 ? 0 : -up; };
  auto local = [&](Point p, Point a, Point b, Point c){
    return sign(CCW(p, a, b)) <= 0 && sign(CCW(p, b, c)) >= 0;
  }; // assert(v.size() >= 2);
  int n = v.size() - 1, s = 0, e = n, m;
  if(local(pt, v[1], v[0], v[n-1])) return 0;
  while(s + 1 < e){
    m = (s + e) / 2;
    if(local(pt, v[m-1], v[m], v[m+1])) return m;
    if(sign(CCW(pt, v[s], v[s+1])) < 0){ // up
      if(sign(CCW(pt, v[m], v[m+1])) > 0) e = m;
      else if(sign(CCW(pt, v[m], v[s])) > 0) s = m; else e = m;
    }
    else{ // down
      if(sign(CCW(pt, v[m], v[m+1])) < 0) s = m;
      else if(sign(CCW(pt, v[m], v[s])) < 0) s = m; else e = m;
    }
  }
  if(s && local(pt, v[s-1], v[s], v[s+1])) return s;
  if(e != n && local(pt, v[e-1], v[e], v[e+1])) return e;
  return -1;
}
int Closest(const vector<Point> &v, const Point &out, int now){
  int prv = now > 0 ? now-1 : v.size()-1, nxt = now+1 < v.size() ? now+1 : 0, res = now;
  if(CCW(out, v[now], v[prv]) == 0 && Dist(out, v[res]) > Dist(out, v[prv])) res = prv;
  if(CCW(out, v[now], v[nxt]) == 0 && Dist(out, v[res]) > Dist(out, v[nxt])) res = nxt;
  return res; // if parallel, return closest point to out
} // int point_idx =  Closest(convex_hull, pt, ConvexTangent(hull + hull[0], pt, +-1) % N);