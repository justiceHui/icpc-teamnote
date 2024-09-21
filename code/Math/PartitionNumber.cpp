for(int j=1; j*(3*j-1)/2<=i; j++) P[i] += (j%2?1:-1)*P[i-j*(3*j-1)/2], P[i] %= MOD;
for(int j=1; j*(3*j+1)/2<=i; j++) P[i] += (j%2?1:-1)*P[i-j*(3*j+1)/2], P[i] %= MOD;
vector<ModInt> res(sz+1); res[0] = 1; int sq=sqrt(sz);
vector<vector<ModInt>> p(2, vector<ModInt>(sz+1)), d=p;
for(int k=1; k<sq; k++){ p[0][0] = k == 1; // calc p[k][n]
  for(int n=1; n<=sz; n++){
    p[k&1][n] = p[k-1&1][n-1] + (n-k>=0 ? p[k&1][n-k] : 0);
    res[n] += p[k&1][n]; }}
for(int a=sq; a>=0; a--) for(int b=sq; b<=sz; b++){
  d[a&1][b] = d[a+1&1][b-sq] + p[sq-1&1][b-1] + (b-a-1>=0 ? d[a&1][b-a-1] : 0);
  if(a == 0) res[b] += d[a&1][b];
}