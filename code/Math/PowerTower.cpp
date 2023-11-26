bool PowOverflow(ll a, ll b, ll c){
  __int128_t res = 1;
  bool flag = false;
  for(; b; b >>= 1, a = a * a){
    if(a >= c) flag = true, a %= c;
    if(b & 1){
      res *= a; if(flag || res >= c) return true;
    }
  }
  return false;
}
ll Recursion(int idx, ll mod, const vector<ll> &vec){
  if(mod == 1) return 1;
  if(idx + 1 == vec.size()) return vec[idx];
  ll nxt = Recursion(idx+1, phi[mod], vec);
  if(PowOverflow(vec[idx], nxt, mod)) return Pow(vec[idx], nxt, mod) + mod; else return Pow(vec[idx], nxt, mod);
}
ll PowerTower(const vector<ll> &vec, ll mod){ // vec[0]^(vec[1]^(vec[2]^(...)))
  if(vec.size() == 1) return vec[0] % mod;
  else return Pow(vec[0], Recursion(1, phi[mod], vec), mod);
}