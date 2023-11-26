bool Check(const vector<Point> &v, const Point &pt){
  if(CCW(v[0], v[1], pt) < 0) return false;
  int l = 1, r = v.size() - 1;
  while(l < r){
    int m = l + r + 1 >> 1;
    if(CCW(v[0], v[m], pt) >= 0) l = m; else r = m - 1;
  }
  if(l == v.size() - 1) return CCW(v[0], v.back(), pt) == 0 && v[0] <= pt && pt <= v.back();
  return CCW(v[0], v[l], pt) >= 0 && CCW(v[l], v[l+1], pt) >= 0 && CCW(v[l+1], v[0], pt) >= 0;
}