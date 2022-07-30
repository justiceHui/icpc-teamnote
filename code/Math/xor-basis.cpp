// can use greedy maximize
//((staircase basis, basis coefficient),selected basis indices)
// staircase basis: has some good property
// basis coefficient and selected basis indices: for reconstruct
pair<vector<pair<ll,ll>>, vector<ll>> xor_basis(const vector<ll> &a) {
  vector<pair<ll,ll>> r(64, {-1, -1});  // descending
  vector<ll> bi;
  for(int i = 0; i < a.size(); i++) {
    ll x = a[i], xc = 0;
    for(auto [b, bc] : r)
      if(~b and x > (x ^ b)) x ^= b, xc ^= bc;
    if(x) r[63 - __lg(x)] = {x, xc ^ (1ll << bi.size())}, bi.push_back(i);
  }
  return {move(r), move(bi)};
} // for(auto i : r) mx = max(mx, mx ^ i.first);