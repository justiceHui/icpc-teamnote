/**
 * Author: 
 * License: 
 * Source:
   * PrimitiveRoot: https://github.com/foreverbell/acm-icpc-cheat-sheet/blob/master/src/math/number-theory/ressol.cpp
   * DiscreteLog: JusticeHui
   * DiscreteSqrt: https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/ModSqrt.h
 * Problem(PrimitiveRoot): https://judge.yosupo.jp/problem/primitive_root
 * Code: https://judge.yosupo.jp/submission/184951
 * Problem(DiscreteLog): https://www.acmicpc.net/problem/4357
 * Code: http://boj.kr/0e0dd0b3c4454be4b7cb2677f7788b7d
 * Problem(DiscreteSqrt): https://judge.yosupo.jp/problem/sqrt_mod
 * Code: https://judge.yosupo.jp/submission/184952
 */

ll PrimitiveRoot(ll p){ // order p-1
  vector<pair<ll,ll>> v = Factorize(p-1);
  for(ll r=1; ; r++){
    bool flag = true; // Warning: 64bit Pow
    for(auto [d,e] : v) if(PowMod(r, (p-1)/d, p) == 1){ flag = false; break; }
    if(flag) return r;
  }
}
// Given A, B, P, solve A^x === B mod P, return smallest value
ll DiscreteLog(ll A, ll B, ll P){ // O(sqrt P) with hash set
  __gnu_pbds::gp_hash_table<ll,__gnu_pbds::null_type> st;
  ll t = ceil(sqrt(P)), k = 1; // use binary search?
  for(int i=0; i<t; i++) st.insert(k), k = k * A % P;
  ll inv = Pow(k, P-2, P);
  for(int i=0, s=1; i<t; i++, s=s*inv%P){
    ll x = B * s % P;
    if(st.find(x) == st.end()) continue;
    for(int j=0, f=1; j<t; j++, f=f*A%P){
      if(f == x) return i * t + j;
    }
  }
  return -1;
}
// Given A, P, solve X^2 === A mod P, return arbitrary
ll DiscreteSqrt(ll A, ll P){//O(log^2P), O(logP) in random data
  if(A == 0) return 0;
  if(Pow(A, (P-1)/2, P) != 1) return -1;
  if(P % 4 == 3) return Pow(A, (P+1)/4, P);
  ll s = P - 1, n = 2, r = 0, m;
  while(~s & 1) r++, s >>= 1;
  while(Pow(n, (P-1)/2, P) != P-1) n++;
  ll x = Pow(A, (s+1)/2, P), b = Pow(A, s, P), g = Pow(n, s, P);
  for(;; r=m){
    ll t = b; for(m=0; m<r && t!=1; m++) t = t * t % P;
    if(!m) return x;
    ll gs = Pow(g, 1LL << (r-m-1), P);
    g = gs * gs % P; x = x * gs % P; b = b * g % P;
  }
}