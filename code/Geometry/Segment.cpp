double Proj(Point a, Point b, Point c){
  ll t1 = (b - a) * (c - a), t2 = (a - b) * (c - b);
  if(t1 * t2 >= 0 && CCW(a, b, c) != 0)
    return abs(CCW(a, b, c)) / sqrt(Dist(a, b));
  else return 1e18; // INF
}
double SegmentDist(Point a[2], Point b[2]){
  double res = 1e18; // NOTE: need to check intersect
  for(int i=0; i<4; i++) res=min(res,sqrt(Dist(a[i/2],b[i%2])));
  for(int i=0; i<2; i++) res = min(res, Proj(a[0], a[1], b[i]));
  for(int i=0; i<2; i++) res = min(res, Proj(b[0], b[1], a[i]));
  return res;
}
P Reflect(P p1, P p2, P p3){ // line p1-p2, point p3
  auto [x1,y1] = p1; auto [x2,y2] = p2; auto [x3,y3] = p3;
  auto a = y1-y2, b = x2-x1, c = x1 * (y2-y1) + y1 * (x1-x2);
  auto d = a * y3 - b * x3;
  T x = -(a*c+b*d) / (a*a+b*b), y = (a*d-b*c) / (a*a+b*b);
  return 2 * P(x,y) - p3;
}