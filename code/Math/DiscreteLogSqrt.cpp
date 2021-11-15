// Given A, B, P, solve A^x === B mod P
ll DiscreteLog(ll A, ll B, ll P){
  __gnu_pbds::gp_hash_table<ll,__gnu_pbds::null_type> st;
  ll t = ceil(sqrt(P)), k = 1; // use binary search?
  for(int i=0; i<t; i++) st.insert(k), k = k * A % P;
  ll inv = Pow(k, P-2, P);
  for(int i=0, k=1; i<t; i++, k=k*inv%P){
    ll x = B * k % P;
    if(st.find(x) == st.end()) continue;
    for(int j=0, k=1; j<t; j++, k=k*A%P){
      if(k == x) return i * t + j;
    }
  }
  return -1;
}
// Given A, P, solve X^2 === A mod P
ll DiscreteSqrt(ll A, ll P){
  if(A == 0) return 0;
  if(Pow(A, (P-1)/2, P) != 1) return -1;
  if(P % 4 == 3) return Pow(A, (P+1)/4, P);
  ll s = P - 1, n = 2, r = 0, m;
  while(~s & 1) r++, s >>= 1;
  while(Pow(n, (P-1)/2, P) != P-1) n++;
  ll x = Pow(A, (s+1)/2, P), b = Pow(A, s, P), g = Pow(n, s, P);
  for(;; r=m){
    ll t = b;
    for(m=0; m<r && t!=1; m++) t = t * t % P;
    if(!m) return x;
    ll gs = Pow(g, 1LL << (r-m-1), P);
    g = gs * gs % P;
    x = x * gs % P;
    b = b * g % P;
  }
}