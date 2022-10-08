// 점화식에 min이 들어가는 경우: 구간을 쪼갤 때마다 +lambda
while(l <= r){
  ll m = l + r >> 1; [dp,cnt] = Solve(m);
  res = max(res, dp - k*m);
  if(cnt <= k) r = m - 1; else l = m + 1;
}
// 점화식에 max가 들어가는 경우: 구간을 쪼갤 때마다 +lambda
while(l <= r){
  ll m = l + r >> 1; [dp,cnt] = Solve(m);
  res = min(res, dp - k*m);
  if(cnt <= k) l = m + 1; else r = m - 1;
}