ll MoneyForNothing(vector<Point> lo, vector<Point> hi){
  sort(lo.begin(), lo.end()); sort(hi.rbegin(), hi.rend());//rev
  vector<Point> a, b; ll res = 0;
  for(auto p:lo)if(a.empty() || a.back().y > p.y)a.push_back(p);
  for(auto p:hi)if(b.empty() || b.back().y < p.y)b.push_back(p);
  reverse(b.begin(),b.end()); if(a.empty()||b.empty()) return 0;
  queue<tuple<int,int,int,int>> que;
  que.emplace(0, (int)a.size()-1, 0, (int)b.size()-1);
  while(!que.empty()){
    auto [s,e,l,r] = que.front(); que.pop();
    int m = (s + e) / 2, pos = l; ll mx = -4e18;
    for(int i=l; i<=r; i++){
      ll dx = b[i].x - a[m].x, dy = b[i].y - a[m].y;
      ll now = (dx < 0 && dy < 0) ? 0 : dx * dy;
      if(now > mx) mx = now, pos = i;
    } res = max(res, mx);
    if(s < m) que.emplace(s, m-1, l, pos);
    if(m < e) que.emplace(m+1, e, pos, r);
  } return res;
}