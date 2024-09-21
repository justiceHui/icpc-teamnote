// find the indices of row maxima, smallest index when tie
template <class F, class T=long long>
vector<int> SMAWK(F f, int n, int m){
  vector<int> ans(n, -1);
  auto rec = [&](auto self, int*const rs, int x, int*const cs, int y){
    const int t = 8;
    if(x <= t || y <= t){
      for(int i=0; i<x; i++){ int r = rs[i]; T mx;
        for(int j=0; j<y; j++){
          int c = cs[j]; T w = f(r, c);
          if(ans[r] == -1 || w > mx) ans[r] = c, mx = w;
    }} /* for j i */ return; } /* base case */
    if(x < y){ int s = 0;
      for(int i=0; i<y; i++){ int c = cs[i];
        while(s && f(rs[s-1], cs[s-1]) < f(rs[s-1], c)) s--;
        if(s < x) cs[s++] = c;
      } y = s;
    }
    int z=0, k=0, *a=rs+x, *b=cs+y;
    for(int i=1; i<x; i+=2) a[z++] = rs[i];
    for(int i=0; i<y; i++) b[i] = cs[i];
    self(self, a, z, b, y);
    for(int i=0; i<x; i+=2){
      int to = i+1 < x ? ans[rs[i+1]] : cs[y-1]; T mx;
      while(true){
        T w = f(rs[i], cs[k]);
        if(ans[rs[i]] == -1 || w > mx) ans[rs[i]]=cs[k], mx=w;
        if(cs[k] == to) break; k++;
    }}
  };
  int *rs = new int[n*2]; iota(rs,rs+n,0);
  int *cs = new int[max(m, n*2)]; iota(cs,cs+m,0);
  rec(rec,rs,n,cs,m);delete[]rs;delete[]cs;return ans;
}
// A: convex, B: arbitrary, O((N+M) log M)
int N, M, A[1<<19], B[1<<19], C[1<<20];
void DnC(int s, int e, int l, int r){
  if(s > e) return;
  int m = (s+e)/2, opt = -1, &mn = C[m];
  for(int i=l; i<=min(m,r); i++){
    if(m - i >= N) continue;
    if(opt == -1 || A[m-i] + B[i] < mn) mn=A[m-i]+B[i], opt=i;
  } DnC(s, m-1, l, opt); DnC(m+1, e, opt, r);
} // or...
int f(int r, int c){//O(N+M) but not fast
  if(0 <= r-c && r-c < N) return -(A[r-c] + B[c]);
  else return -21e8 - (r - c); // min
} SMAWK(f, N+M-1, M); // DnC opt 163ms SMAWK 179ms N,M=2^19