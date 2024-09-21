// 32bit : 2, 7, 61 / ull MulMod, PowMod (cast __uint128_t)
// 64bit : 2, 325, 9375, 28178, 450775, 9780504, 1795265022
bool MillerRabin(ull n, ull a){
  if(a % n == 0) return true; int cnt = __builtin_ctzll(n - 1);
  ull p=PowMod(a, n>>cnt, n); if(p==1 || p+1==n) return true;
  while(cnt--) if((p=MulMod(p,p,n)) == n - 1) return true;
  return false;
}
bool IsPrime(ll n){
  if(n <= 11) return hard_coding;
  if(n % 2 == 0 || ... 3 5 7 11) return false;
  for(int p : {comments}) if(!MillerRabin(n, p)) return false;
  return true;
}
ull Rho(ull n){
  ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
  auto f = [&](ull x) { return MulMod(x, x, n) + i; };
  while(t++ % 40 || __gcd(prd, n) == 1){
    if(x == y) x = ++i, y = f(x);
    if((q = MulMod(prd, max(x,y) - min(x,y), n))) prd = q;
    x = f(x), y = f(f(y));
  } return __gcd(prd, n);
}
vector<ull> Factorize(ull n){ // sort?
  if(n == 1) return {}; if(IsPrime(n)) return {n};
  auto x = Rho(n); auto l=Factorize(x), r=Factorize(n/x);
  l.insert(l.end(), r.begin(), r.end()); return l; }