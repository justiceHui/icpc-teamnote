template<bool UPPER=true> // O(log N)
Point GetPoint(const vector<Point> &hull, real_t slope){
    auto chk = [slope](real_t dx, real_t dy){ return UPPER ? dy >= slope * dx : dy <= slope * dx; };
    int l = -1, r = hull.size() - 1;
    while(l + 1 < r){
        int m = (l + r) / 2;
        if(chk(hull[m+1].x - hull[m].x, hull[m+1].y - hull[m].y)) l = m; else r = m;
    }
    return hull[r];
}
int ConvexTangent(const vector<Point> &v, const Point &pt, int up=1){ //given outer point, O(log N)
  auto sign = [&](ll c){ return c>0 ? up : c==0 ? 0 : -up; };
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
/////////
double polar(pdd x){ return atan2(x.second, x.first); }
int tangent(circle &A, circle &B, pdd des[4]){ // return angle
  int top = 0; // outer
  double d = size(A.O - B.O), a = polar(B.O - A.O), b = PI + a;
  double t = sq(d) - sq(A.r - B.r);
  if (t >= 0){
    t = sqrt(t); double p = atan2(B.r - A.r, t);
    des[top++] = pdd(a + p + PI / 2, b + p - PI / 2);
    des[top++] = pdd(a - p - PI / 2, b - p + PI / 2);
  }
  t = sq(d) - sq(A.r + B.r); // inner
  if (t >= 0){ t = sqrt(t);
    double p = atan2(B.r + A.r, t);
    des[top++] = pdd(a + p - PI / 2, b + p - PI / 2);
    des[top++] = pdd(a - p + PI / 2, b - p + PI / 2);
  }
  return top;
}
pair<T, T> CirclePointTangent(P o, double r, P p){
  T op=D1(p,o), u=atan2l(p.y-o.y, p.x-o.x), v=acosl(r/op);
  return {u + v, u - v};
} // COORD 1e4 EPS 1e-7 / COORD 1e3 EPS 1e-9 with circleLine