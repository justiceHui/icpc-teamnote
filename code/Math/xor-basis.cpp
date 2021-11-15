// can use greedy maximize
//((staircase basis, basis coefficient),selected basis indices)
// staircase basis: has some good property
// basis coefficient and selected basis indices: for reconstruct
pair<Arr<pint>, Arr<int>> xor_basis(const Arr<int>& a) {
  Arr<pint> r(64, {-1, -1});  // descending
  Arr<int> bi;
  for(int i = 0; i < sz(a); i++) {
    int x = a[i], xc = 0;
    for(auto [b, bc] : r)
      if(~b and x > (x ^ b)) x ^= b, xc ^= bc;
    if(x) r[63 - lg2f(x)] = {x, xc ^ (1ll << sz(bi))}, bi.pushb(i);
  }
  return {move(r), move(bi)};
}