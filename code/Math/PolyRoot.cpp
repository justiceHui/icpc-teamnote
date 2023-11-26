/**
 * Author: Per Austrin
 * License: CC0
 * Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/PolyRoots.h
 */

vector<double> poly_root(vector<double> p, double xmin, double xmax){
  if(p.size() == 2){ return {-p[0] / p[1]}; }
  vector<double> ret, der(p.size()-1);
  for(int i=0; i<der.size(); i++) der[i] = p[i+1] * (i + 1);
  auto dr = poly_root(der, xmin, xmax);
  dr.push_back(xmin-1); dr.push_back(xmax+1);
  sort(dr.begin(), dr.end());
  for(int i=0; i+1<dr.size(); i++){
    double l = dr[i], h = dr[i+1]; bool sign = calc(p, l) > 0;
    if (sign ^ (calc(p, h) > 0)){
      for(int it=0; it<60; it++){ // while(h-l > 1e-8)
        double m = (l + h) / 2, f = calc(p, m);
        if ((f <= 0) ^ sign) l = m; else h = m;
      }
      ret.push_back((l + h) / 2);
    }
  }
  return ret;
}