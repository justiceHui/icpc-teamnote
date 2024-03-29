pair<ll,ll> Solve(ld l, ld r){//find l<p/q<r -> min q -> min p
  auto g=[](ll v,pair<ll,ll>a,pair<ll,ll>b)->pair<ll,ll>{
    return { v * a.first + b.first, v * a.second + b.second }; };
  auto f = [g](ll v, pair<ll,ll> a, pair<ll,ll> b) -> ld {
    auto [p,q] = g(v, a, b); return ld(p) / q; };
  pair<ll,ll> s(0, 1), e(1, 0);
  while(true){
    pair<ll,ll> m(s.first+e.first, s.second+e.second);
    ld v = 1.L * m.first / m.second;
    if(v >= r){
      ll ks = 1, ke = 1; while(f(ke, s, e) >= r) ke *= 2;
      while(ks <= ke){
        ll km = (ks + ke) / 2;
        if(f(km, s, e) >= r) ks = km + 1; else ke = km - 1;
      } e = g(ke, s, e);
    }
    else if(v <= l){
      ll ks = 1, ke = 1; while(f(ke, e, s) <= l) ke *= 2;
      while (ks <= ke){
        ll km = (ks + ke) / 2;
        if(f(km, e, s) <= l) ks = km + 1; else ke = km - 1;
      } s = g(ke, e, s);
    }
    else return m;
  }
}
struct Frac { ll p, q; };//find smallest 0 <= p/q <= 1 (p,q<=N)
template<class F> Frac fracBS(F f, ll N) { // s.t. f(p/q) true
  bool dir = 1, A = 1, B = 1; // O(log N)
  Frac lo{0, 1}, hi{1, 1}; // Set hi to 1/0 to search (0, N]
  if(f(lo)) return lo; assert(f(hi));
  while(A != 0 || B != 0){
    ll adv = 0, step = 1; // move hi if dir, else lo
    for(int si=0; step; (step*=2)>>=si){ adv += step;
      Frac mid{lo.p * adv + hi.p, lo.q * adv + hi.q};
      if(abs(mid.p)>N || mid.q>N || dir != f(mid))
        adv -= step, si = 2;
    }
    hi.p += lo.p * adv; hi.q += lo.q * adv;
    dir = !dir; swap(lo, hi); A = B; B = adv != 0;
  }
  return dir ? hi : lo;
}