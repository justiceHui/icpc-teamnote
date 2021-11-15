bool pip_convex(const vector<p> &v, p pt){
  int i = lower_bound(v.begin()+1, v.end(), pt, [&](const p &a, const p &b){
    int cw = ccw(v[0], a, b);
    if(cw) return cw > 0;
    return dst(v[0], a) < dst(v[0], b);
  }) - v.begin();
  if(i == v.size()) return 0;
  if(i == 1) return ccw(v[0], pt, v[1]) == 0 && v[0] <= pt && pt <= v[1];
  int t1 = ccw(v[0], pt, v[i]) * ccw(v[0], pt, v[i-1]);
  int t2 = ccw(v[i], v[i-1], v[0]) * ccw(v[i], v[i-1], pt);
  if(t1 == -1 && t2 == -1) return 0;
  return ccw(v[0], pt, v[i-1]) != 0;
}