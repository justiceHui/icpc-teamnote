constexpr int SZ = 10'000'000; bool PrimeCheck[SZ+1]; vector<int> Primes;
void Sieve(){ memset(PrimeCheck, true, sizeof PrimeCheck); /* Sieve */ }
ull MulMod(ull a, ull b, ull c){ return (__uint128_t)a * b % c; }
// 32bit : 2, 7, 61
// 64bit : 2, 325, 9375, 28178, 450775, 9780504, 1795265022
bool MillerRabin(ull n, ull a){
  if(a % n == 0) return true;
  int cnt = __builtin_ctzll(n - 1);
  ull p = PowMod(a, n >> cnt, n);
  if(p == 1 || p == n - 1) return true;
  while(cnt--) if((p=MulMod(p,p,n)) == n - 1) return true;
  return false;
}
bool IsPrime(ll n){
  if(n <= SZ) return PrimeCheck[n];
  if(n <= 2) return n == 2;
  if(n % 2 == 0 || n % 3 == 0 || n % 5 == 0 || n % 7 == 0 || n % 11 == 0) return false;
  for(int p : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) if(!MillerRabin(n, p)) return false;
  return true;
}
ll Rho(ll n){
  while(true){
    ll x = rand() % (n - 2) + 2, y = x, c = rand() % (n - 1) + 1;
    while(true){
      x = (MulMod(x,x,n)+c) % n; y = (MulMod(y,y,n)+c) % n; y = (MulMod(y,y,n)+c) % n;
      ll d = __gcd(abs(x - y), n); if(d == 1) continue;
      if(IsPrime(d)) return d; else{ n = d; break; }
    }
  }
}
vector<pair<ll,ll>> Factorize(ll n){
  vector<pair<ll,ll>> v;
  int two = __builtin_ctzll(n);
  if(two > 0) v.emplace_back(2, two), n >>= two;
  if(n == 1) return v;
  while(!IsPrime(n)){
    ll d = Rho(n), cnt = 0; while(n % d == 0) cnt++, n /= d;
    v.emplace_back(d, cnt); if(n == 1) break;
  }
  if(n != 1) v.emplace_back(n, 1); return v;
}