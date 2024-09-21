ld NormAngle(ld v){while(v < -EPS) v += M_PI * 2;
  while(v > M_PI * 2 + EPS) v -= M_PI * 2;
  return v; }
ld TwoCircleUnion(const Circle &p, const Circle &q) {
  ld d = D1(p.o - q.o); if(d >= p.r+q.r-EPS) return 0;
  else if(d <= abs(p.r-q.r)+EPS) return pow(min(p.r,q.r),2)*PI;
  ld pc = (p.r*p.r + d*d - q.r*q.r) / (p.r*d*2), pa = acosl(pc);
  ld qc = (q.r*q.r + d*d - p.r*p.r) / (q.r*d*2), qa = acosl(qc);
  ld ps = p.r*p.r*pa - p.r*p.r*sin(pa*2)/2;
  ld qs = q.r*q.r*qa - q.r*q.r*sin(qa*2)/2;
  return ps + qs; }
ld TwoCircleIntersect(P p1, P p2, ld r1, ld r2){
  auto f = [](ld a, ld b, ld c){
    return acosl((a*a + b*b - c*c) / (2*a*b)); };
  ld d = D1(p1, p2); if(d + EPS > r1 + r2) return 0;
  if(d < abs(r1-r2) + EPS) return min(r1,r2)*min(r1,r2)*M_PI;
  ld t1 = f(r1, d, r2), t2 = f(r2, d, r1);
  return r1*r1*(t1-sinl(t1)*cosl(t1))
       + r2*r2*(t2-sinl(t2)*cosl(t2)); }
vector<pair<double, double>> CoverSegment(Cir a, Cir b) {
  double d = abs(a.o - b.o); vector<pair<double, double>> res;
  if(sign(a.r + b.r - d) == 0); /* skip */
  else if(d <= abs(a.r - b.r) + eps) {
    if (a.r < b.r) res.emplace_back(0, 2 * pi);
  } else if(d < abs(a.r + b.r) - eps) {
    double o = acos((a.r*a.r + d*d - b.r*b.r) / (2 * a.r * d));
    double z = NormAngle(atan2((b.o - a.o).y, (b.o - a.o).x));
    double l = NormAngle(z - o), r = NormAngle(z + o);
    if(l > r) res.emplace_back(l, 2*pi), res.emplace_back(0,r);
    else res.emplace_back(l, r);
  } return res;
}// circle should be identical
double CircleUnionArea(vector<Cir> c) {
  int n = c.size(); double a = 0, w;
  for (int i = 0; w = 0, i < n; ++i) {
    vector<pair<double, double>> s = {{2 * pi, 9}}, z;
    for (int j = 0; j < n; ++j) if (i != j) {
      z = CoverSegment(c[i], c[j]);
      for (auto &e : z) s.push_back(e); } /* for j */
    sort(s.begin(), s.end());
    auto F = [&] (double t) { return c[i].r * (c[i].r * t + c[i].o.x * sin(t) - c[i].o.y * cos(t)); };
    for (auto &e : s) {
      if (e.first > w) a += F(e.first) - F(w);
      w = max(w, e.second); } /* for e */
  } return a * 0.5; }