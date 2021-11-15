ull mul(ull a, ull b, ull mod){ return (__uint128_t)a * b % mod; }
bool isp[10101010];
vector<int> prime;
void sieve(){
  memset(isp, 1, sizeof isp);
  isp[0] = isp[1] = 0;
  for(ll i=2; i<=10000000; i++){
    if(isp[i]) prime.push_back(i);
    for(auto j : prime){
      if(i*j > 10000000) break;
      isp[i*j] = 0;
      if(i % j == 0) break;
    }
  }
}
// 32bit : 2, 7, 61
// 64bit : 2, 325, 9375, 28178, 450775, 9780504, 1795265022
bool MR(ull n, ull a){ // Miller Rabin
  if(a % n == 0) return 1;
  int cnt = __builtin_ctzll(n-1);
  ull d = n >> cnt;
  ull p = pw(a, d, n);
  if(p == 1 || p == n - 1) return 1;
  while(cnt--){
    p = mul(p, p, n);
    if(p == n-1) return 1;
  }
  return 0;
}
bool isPrime(ll n){
  if(n < 10000001) return isp[n];
  if(n <= 2) return n == 2;
  if(!(n & 1)) return 0;
  if(n%3 == 0 || n%5 == 0 || n%7 == 0 || n%11 == 0) return 0;
  for(int p : {2,325,9375,28178,450775,9780504,1795265022}){
    if(!MR(n, p)) return 0;
  }
  return 1;
}
ll rho(ll n){
  while(1){
    ll x = rand() % (n - 2) + 2;
    ll y = x, c = rand() % (n-1) + 1;
    while(1){
      x = (mul(x, x, n) + c) % n;
      y = (mul(y, y, n) + c) % n;
      y = (mul(y, y, n) + c) % n;
      ll d = __gcd(abs(x - y), n);
      if(d == 1) continue;
      if(!isPrime(d)){ n = d; break; }
      else return d;
    }
  }
}
vector<ll> pollard_rho(ll n){
  vector<ll> v;
  while(~n & 1) n >>= 1, v.push_back(2);
  if(n == 1) return move(v);
  while(!isPrime(n)){
    ll d = rho(n);
    while(n % d == 0) v.push_back(d), n /= d;
    if(n == 1) break;
  }
  if(n != 1) v.push_back(n);
  return move(v);
}