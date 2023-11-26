pt getCenter(pt a, pt b){ return pt((a.x+b.x)/2, (a.y+b.y)/2); }
pt getCenter(pt a, pt b, pt c){
  pt aa = b - a, bb = c - a;
  auto c1 = aa*aa * 0.5, c2 = bb*bb * 0.5, d = aa / bb;
  auto x = a.x + (c1 * bb.y - c2 * aa.y) / d;
  auto y = a.y + (c2 * aa.x - c1 * bb.x) / d;
  return pt(x, y); }
Circle solve(vector<pt> v){
  pt p = {0, 0};
  double r = 0; int n = v.size();
  for(int i=0; i<n; i++) if(dst(p, v[i]) > r + EPS){
    p = v[i]; r = 0;
    for(int j=0; j<i; j++) if(dst(p, v[j]) > r + EPS){
      p = getCenter(v[i], v[j]); r = dst(p, v[i]);
      for(int k=0; k<j; k++) if(dst(p, v[k]) > r + EPS){
        p = getCenter(v[i], v[j], v[k]); r = dst(v[k], p);
  }}}
  return {p, r}; }