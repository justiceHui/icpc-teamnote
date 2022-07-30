double CCW(Point p1, Point p2, Point p3){
  return (p2.x-p1.x) * (p3.y-p2.y) - (p3.x-p2.x) * (p2.y-p1.y);
}
bool same(double a, double b){ return abs(a - b) < eps; }
const Point o = Point(0, 0);
struct Line{
  double a, b, c;
  Line() : Line(0, 0, 0) {}
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
Point GetMaximumPoint(const vector<Point> &up, double dy, double dx){
  if(up.size() == 1) return up.front();
  if(dx < 0) dx = -dx, dy = -dy;
  if(dx == 0) return dy > 0 ? up.front() : up.back();
  if((up[1].y - up[0].y) * dx < (up[1].x - up[0].x) * dy) return up.front();
  int l = 1, r = up.size() - 1;
  while(l < r){
    int m = l + r + 1 >> 1;
    if((up[m].y - up[m-1].y) * dx >= (up[m].x - up[m-1].x) * dy) l = m;
    else r = m - 1;
  }
  return up[l];
}
Point GetMinimumPoint(const vector<Point> &lo, double dy, double dx){
  if(lo.size() == 1) return lo.front();
  if(dx < 0) dx = -dx, dy = -dy;
  if(dx == 0) return dy > 0 ? lo.back() : lo.front();
  if((lo[1].y - lo[0].y) * dx > (lo[1].x - lo[0].x) * dy) return lo.front();
  int l = 1, r = lo.size() - 1;
  while(l < r){
    int m = l + r + 1 >> 1;
    if((lo[m].y - lo[m-1].y) * dx <= (lo[m].x - lo[m-1].x) * dy) l = m;
    else r = m - 1;
  }
  return lo[l];
}