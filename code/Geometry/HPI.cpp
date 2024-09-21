double CCW(p1, p2, p3); bool same(double a, double b); const Point o = Point(0, 0);
struct Line{ // ax+by leq c
  double a, b, c; Line() : Line(0, 0, 0) {}
  Line(double a, double b, double c) : a(a), b(b), c(c) {}
  bool operator < (const Line &l) const {
    bool f1 = Point(a, b) > o, f2 = Point(l.a, l.b) > o;
    if(f1 != f2) return f1 > f2;
    double cw = CCW(o, Point(a, b), Point(l.a, l.b));
    return same(cw, 0) ? c * hypot(l.a, l.b) < l.c * hypot(a, b) : cw > 0;
  } Point slope() const { return Point(a, b); }
};
Point LineIntersect(Line a, Line b){
  double det = a.a*b.b - b.a*a.b, x = (a.c*b.b - a.b*b.c) / det, y = (a.a*b.c - a.c*b.a) / det; return Point(x, y);
}
bool CheckHPI(Line a, Line b, Line c){
  if(CCW(o, a.slope(), b.slope()) <= 0) return 0;
  Point v=LineIntersect(a,b); return v.x*c.a+v.y*c.b>=c.c;
}
vector<Point> HPI(vector<Line> v){
  sort(v.begin(), v.end()); deque<Line> dq; vector<Point> ret;
  for(auto &i : v){
    if(dq.size() && same(CCW(o, dq.back().slope(), i.slope()), 0)) continue;
    while(dq.size() >= 2 && CheckHPI(dq[dq.size()-2], dq.back(), i)) dq.pop_back();
    while(dq.size()>=2&&CheckHPI(i,dq[0],dq[1]))dq.pop_front();
    dq.push_back(i);
  }
  while(dq.size() > 2 && CheckHPI(dq[dq.size()-2], dq.back(), dq[0])) dq.pop_back();
  while(dq.size() > 2 && CheckHPI(dq.back(), dq[0], dq[1])) dq.pop_front();
  for(int i=0; i<dq.size(); i++){
    Line now = dq[i], nxt = dq[(i+1)%dq.size()];
    if(CCW(o, now.slope(), nxt.slope()) <= eps) return vector<Point>();
    ret.push_back(LineIntersect(now, nxt));
  } //for(auto &[x,y] : ret) x = -x, y = -y;
  return ret;
} // MakeLine: left side of ray (x1,y1) -> (x2,y2)
Line MakeLine(T x1, T y1, T x2, T y2){
  T a = y2-y1, b = x1-x2, c = x1*a + y1*b; return {a,b,c}; }