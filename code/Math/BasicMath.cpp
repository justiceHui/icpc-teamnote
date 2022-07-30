// ll gcd(ll a, ll b), ll lcm(ll a, ll b), ll mod(ll a, ll b)
tuple<ll,ll,ll> ext_gcd(ll a, ll b){ // return [g,x,y] s.t. ax+by=gcd(a,b)=g
  if(b == 0) return {a, 1, 0};
  auto [g,x,y] = ext_gcd(b, a % b);
  return {g, y, x - a/b * y};
}
ll inv(ll a, ll m){ //return x when ax mod m = 1, fail -> -1
  auto [g,x,y] = ext_gcd(a, m);
  return g == 1 ? mod(x, m) : -1;
}
pair<ll,ll> crt(ll a1, ll m1, ll a2, ll m2){
  ll g = gcd(m1, m2), m = m1 / g * m2;
  if((a2 - a1) % g) return {-1, -1};
  ll md = m2/g, s = mod((a2-a1)/g, m2/g);
  ll t = mod(get<1>(ext_gcd(m1/g%md, m2/g)), md);
  return { a1 + s * t % md * m1, m };
}
pair<ll,ll> crt(const vector<ll> &a, const vector<ll> &m){
  ll ra = a[0], rm = m[0];
  for(int i=1; i<m.size(); i++){
    auto [aa,mm] = crt(ra, rm, a[i], m[i]);
    if(mm == -1) return {-1, -1}; else tie(ra,rm) = tie(aa,mm);
  }
  return {ra, rm};
}
struct Lucas{ // init : O(P), query : O(log P)
  const size_t P;
  vector<ll> fac, inv;
  ll Pow(ll a, ll b){
    ll ret = 1;
    for(; b; b>>=1, a=a*a%P) if(b&1) ret=ret*a%P;
    return ret;
  }
Lucas(size_t P) : P(P), fac(P), inv(P) {
    fac[0] = 1;
    for(int i=1; i<P; i++) fac[i] = fac[i-1] * i % P;
    inv[P-1] = Pow(fac[P-1], P-2);
    for(int i=P-2; ~i; i--) inv[i] = inv[i+1] * (i+1) % P;
  }
  ll small(ll n, ll r) const {
    if(n < r) return 0;
    return fac[n] * inv[r] % P * inv[n-r] % P;
  }
  ll calc(ll n, ll r) const {
    if(n < r || n < 0 || r < 0) return 0;
    if(!n || !r || n == r) return 1;
    return small(n%P, r%P) * calc(n/P, r/P) % P;
  }
};
template<ll p, ll e> struct CombinationPrimePower{ // init : O(p^e), query : O(log p)
  vector<ll> val; ll m;
  CombinationPrimePower(){
    m = 1; for(int i=0; i<e; i++) m *= p; val.resize(m); val[0] = 1;
    for(int i=1; i<m; i++) val[i] = val[i-1] * (i % p ? i : 1) % m;
  }
  pair<ll,ll> factorial(int n){
    if(n < p) return {0, val[n]};
    int k = n / p; auto v = factorial(k);
    int cnt = v.first + k, kp = n / m, rp = n % m;
    ll ret = v.second * Pow(val[m-1], kp % 2, m) % m * val[rp] % m;
    return {cnt, ret};
  }
  ll calc(int n, int r){
    if(n < 0 || r < 0 || n < r) return 0;
    auto v1 = factorial(n), v2 = factorial(r), v3 = factorial(n-r);
    ll cnt = v1.first - v2.first - v3.first;
    ll ret = v1.second * inv(v2.second, m) % m * inv(v3.second, m) % m;
    if(cnt >= e) return 0;
    for(int i=1; i<=cnt; i++) ret = ret * p % m;
    return ret;
  }
};