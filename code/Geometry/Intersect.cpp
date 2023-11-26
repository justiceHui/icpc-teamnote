// 0: not intersect, -1: infinity, 4: intersect
// 1/2/3: intersect first/second/both segment corner
// flag, xp, xq, yp, yq : (xp / xq, yp / yq)
using T = __int128_t; // T <= O(COORD^3)
tuple<int,T,T,T,T> SegmentIntersect(P s1, P e1, P s2, P e2){
  if(!Intersect(s1, e1, s2, e2)) return {0, 0, 0, 0, 0};
  auto det = (e1 - s1) / (e2 - s2);
  if(!det){
      if(s1 > e1) swap(s1, e1);
      if(s2 > e2) swap(s2, e2);
      if(e1 == s2) return {3, e1.x, 1, e1.y, 1};
      if(e2 == s1) return {3, e2.x, 1, e2.y, 1};
      return {-1, 0, 0, 0, 0};
  }
  T p = (s2 - s1) / (e2 - s2), q = det, flag = 0;
  T xp = s1.x * q + (e1.x - s1.x) * p, xq = q;
  T yp = s1.y * q + (e1.y - s1.y) * p, yq = q;
  if(xp%xq || yp%yq) return {4,xp,xq,yp,yq};//gcd?
  //if(xq < 0) xp=-xp, xq=-xq; if(yq < 0) yp=-yp, yq=-yq //gcd?
  xp /= xq; yp /= yq;
  if(s1.x == xp && s1.y == yp) flag |= 1;
  if(e1.x == xp && e1.y == yp) flag |= 1;
  if(s2.x == xp && s2.y == yp) flag |= 2;
  if(e2.x == xp && e2.y == yp) flag |= 2;
  return {flag ? flag : 4, xp, 1, yp, 1};
}
P perp() const { return P(-y, x); }
#define arg(p, q) atan2(p.cross(q), p.dot(q))
bool circleIntersect(P a,P b,double r1,double r2,pair<P, P>* out){
  if (a == b) { assert(r1 != r2); return false; }
  P vec = b-a; double d2 = vec.dist2(), sum = r1+r2, dif = r1-r2;
  double p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
  if (sum*sum < d2 || dif*dif > d2) return false; // use EPS plz...
  P mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
  *out = {mid + per, mid - per}; return true;
}
vector<P> circleLine(P c, double r, P a, P b) {
    P ab = b - a, p = a + ab * (c-a) * ab / D2(ab);
    T s = (b - a) / (c - a), h2 = r*r - s*s / D2(ab);
    if (abs(h2) < EPS) return {p}; if (h2 < 0) return {};
    P h = ab / D1(ab) * sqrtl(h2); return {p - h, p + h};
} // use circleLine if you use double...
int CircleLineIntersect(P o, T r, P p1, P p2, bool segment){
  P s = p1, d = p2 - p1; // line : s + kd, int support
  T a = d * d, b = (s - o) * d * 2, c = D2(s, o) - r * r;
  T det = b * b - 4 * a * c; // solve ak^2 + bk + c = 0, a > 0
  if(!segment) return Sign(det) + 1;
  if(det <= 0) return det ? 0 : 0 <= -b && -b <= a + a;
  bool f11 = b <= 0 || b * b <= det;
  bool f21 = b <= 0 && b * b >= det;
  bool f12 = a+a+b >= 0 && det <= (a+a+b) * (a+a+b);
  bool f22 = a+a+b >= 0 || det >= (a+a+b) * (a+a+b);
  return (f11 && f12) + (f21 && f22);
} // do not use this if you want to use double...
double circlePoly(P c, double r, vector<P> ps){ // return area
  auto tri = [&](P p, P q) { // ps must be ccw polygon
    auto r2 = r * r / 2; P d = q - p;
    auto a = d.dot(p)/d.dist2(), b = (p.dist2()-r*r)/d.dist2();
    auto det = a * a - b;
    if (det <= 0) return arg(p, q) * r2;
    auto s = max(0., -a-sqrt(det)), t = min(1., -a+sqrt(det));
    if (t < 0 || 1 <= s) return arg(p, q) * r2;
    P u = p + d * s, v = p + d * t;
    return arg(p,u) * r2 + u.cross(v)/2 + arg(v,q) * r2;
  };
  auto sum = 0.0;
  rep(i,0,sz(ps)) sum += tri(ps[i] - c, ps[(i+1)%sz(ps)] - c);
  return sum;
}
// extrVertex: point of hull, max projection onto line
#define cmp(i,j) sgn(dir.perp().cross(poly[(i)%n]-poly[(j)%n]))
#define extr(i) cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0
int extrVertex(vector<P>& poly, P dir) {
  int n = sz(poly), lo = 0, hi = n;
  if (extr(0)) return 0;
  while (lo + 1 < hi) {
    int m = (lo + hi) / 2; if (extr(m)) return m;
    int ls = cmp(lo + 1, lo), ms = cmp(m + 1, m);
    (ls < ms || (ls == ms && ls == cmp(lo, m)) ? hi : lo) = m;
  }
  return lo;
}
//(-1,-1): no collision
//(i,-1): touch corner
//(i,i): along side (i,i+1)
//(i,j): cross (i,i+1)and(j,j+1)
//(i,i+1): cross corner i
// O(log n), ccw no colinear point convex polygon
// P perp() const { return P(-y, x); }
#define cmpL(i) sgn(a.cross(poly[i], b))
array<int, 2> lineHull(P a, P b, vector<P>& poly) { // O(log N)
  int endA = extrVertex(poly, (a - b).perp());
  int endB = extrVertex(poly, (b - a).perp());
  if (cmpL(endA) < 0 || cmpL(endB) > 0) return {-1, -1};
  array<int, 2> res;
  rep(i,0,2) {
    int lo = endB, hi = endA, n = sz(poly);
    while ((lo + 1) % n != hi) {
      int m = ((lo + hi + (lo < hi ? 0 : n)) / 2) % n;
      (cmpL(m) == cmpL(endB) ? lo : hi) = m;
    }
    res[i] = (lo + !cmpL(hi)) % n;
    swap(endA, endB);
  }
  if (res[0] == res[1]) return {res[0], -1};
  if (!cmpL(res[0]) && !cmpL(res[1]))
    switch ((res[0] - res[1] + sz(poly) + 1) % sz(poly)) {
      case 0: return {res[0], res[0]};
      case 2: return {res[1], res[1]};
    }
  return res;
}