double Proj(Point a, Point b, Point c){
  ll t1 = (b - a) * (c - a), t2 = (a - b) * (c - b);
  if(t1 * t2 >= 0 && CCW(a, b, c) != 0)
    return abs(CCW(a, b, c)) / sqrt(Dist(a, b));
  else return 1e18;
}

double Dist(Point a[2], Point b[2]){
  double res = 1e18; // NOTE: need to check intersect
  for(int i=0; i<4; i++) res = min(res, sqrt(Dist(a[i/2], b[i%2])));
  for(int i=0; i<2; i++) res = min(res, Proj(a[0], a[1], b[i]));
  for(int i=0; i<2; i++) res = min(res, Proj(b[0], b[1], a[i]));
  return res;
}