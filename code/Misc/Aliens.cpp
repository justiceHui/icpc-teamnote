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
// given partition p, q (p.size() >= q.size()), return k partition
// 1-based, p[0] = q[0] = 0, range : ( v[i-1], v[i] ]
// cost function should multiply by 2
// ex. D[n] = max(A[i]A[n] - A[i]^2 + D[i]) => D[n] = max(2A[i]A[n] - 2A[i]^2 + D[i])
// (APIO 2014 Sequence)                     => cht.insert(2A[i], -2A[i]^2 + D[i])
// parametric search by 2m+1, track 2l+1, 2l+3
vector<int> AliensTrack(int k, vector<int> p, vector<int> q){
    if(p.size() == k + 1) return p; if(q.size() == k + 1) return q;
    vector<int> ret;
    for(int i=1, j=1; i<p.size(); i++){
        while(j < q.size() && p[i-1] > q[j]) j++;
        if(p[i] <= q[j] && i - j == k - (int)q.size() + 1){
            ret.insert(ret.end(), p.begin(), p.begin()+i);
            ret.insert(ret.end(), q.begin()+j, q.end());
            return ret;
        }
    }
    assert(false);
}