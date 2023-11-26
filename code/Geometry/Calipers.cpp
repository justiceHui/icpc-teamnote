pair<Point, Point> RotatingCalipers(const vector<Point> &H){
  ll mx = 0; Point a, b;
  for(int i=0, j=0; i<H.size(); i++){
    while(j+1<H.size() && CCW(O,H[i+1]-H[i],H[j+1]-H[j]) >= 0){
      if(ll now=D2(H[i],H[j]); mx<now) mx=now, a=H[i], b=H[j];
      j++;
    }
    if(ll now=D2(H[i],H[j]); mx<now) mx=now, a=H[i], b=H[j];
  }
  return {a, b};
}