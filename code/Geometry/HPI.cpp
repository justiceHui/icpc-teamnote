const pdd o = pdd(0, 0);
ld ccw(pdd a, pdd b, pdd c){} // return cross product value
struct Line{
  ld a, b, c;
  Line() : Line(0, 0, 0) {}
  Line(ld a, ld b, ld c) : a(a), b(b), c(c) {}
  bool operator < (const Line &l) const {
    bool f1 = pdd(a, b) > o;
    bool f2 = pdd(l.a, l.b) > o;
    if(f1 != f2) return f1 > f2;
    ld cw = ccw(o, pdd(a, b), pdd(l.a, l.b));
    return same(cw, 0) ? c * hypot(l.a, l.b) < l.c * hypot(a, b) : cw > 0;
  }
  pdd slope() const { return pdd(a, b); }
};
pdd lineCross(Line a, Line b){
  ld det = a.a*b.b - b.a*a.b;
  ld x = (a.c*b.b - a.b*b.c) / det, y = (a.a*b.c - a.c*b.a) / det;
  return pdd(x, y);
}
bool hpi_chk(Line a, Line b, Line c){
  if(ccw(o, a.slope(), b.slope()) <= 0) return 0;
  pdd v = lineCross(a, b);
  return v.x*c.a + v.y*c.b >= c.c;
}
vector<pdd> hpi(vector<Line> v){
  sort(v.begin(), v.end());
  deque<Line> dq; vector<pdd> ret;
  for(auto &i : v){
    if(dq.size() && same(ccw(o, dq.back().slope(), i.slope()), 0)) continue;
    while(dq.size() >= 2 && hpi_chk(dq[dq.size()-2], dq.back(), i)) dq.pop_back();
    while(dq.size() >= 2 && hpi_chk(i, dq[0], dq[1])) dq.pop_front();
    dq.push_back(i);
  }
  while(dq.size() > 2 && hpi_chk(dq[dq.size()-2], dq.back(), dq[0])) dq.pop_back();
  while(dq.size() > 2 && hpi_chk(dq.back(), dq[0], dq[1])) dq.pop_front();
  for(int i=0; i<dq.size(); i++){
    Line now = dq[i], nxt = dq[(i+1)%dq.size()];
    if(ccw(o, now.slope(), nxt.slope()) <= eps) return vector<pdd>();
    ret.push_back(lineCross(now, nxt));
  }
  return ret;
}