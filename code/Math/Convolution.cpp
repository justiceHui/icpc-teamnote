// 104,857,601   =  25 * 2^22 + 1, w = 3 | 998,244,353   = 119 * 2^23 + 1, w = 3
// 2,281,701,377 =  17 * 2^27 + 1, w = 3 | 2,483,027,969 =  37 * 2^26 + 1, w = 3
// 2,113,929,217 =  63 * 2^25 + 1, w = 5 | 1,092,616,193 = 521 * 2^21 + 1, w = 3
using real_t = double; using cpx = complex<real_t>;
void FFT(vector<cpx> &a, bool inv_fft=false){
  int N = a.size(); vector<cpx> root(N/2);
  for(int i=1, j=0; i<N; i++){
    int bit = N / 2;
    while(j >= bit) j -= bit, bit >>= 1;
    if(i < (j += bit)) swap(a[i], a[j]);
  }
  long double ang = 2 * acosl(-1) / N * (inv_fft ? -1 : 1);
  for(int i=0; i<N/2; i++) root[i] = cpx(cosl(ang*i), sinl(ang*i));
  /*
  NTT : ang = pow(w, (mod-1)/n) % mod, inv_fft -> ang^{-1}, root[i] = root[i-1] * ang
  XOR Convolution : set roots[*] = 1, a[j+k] = u+v, a[j+k+i/2] = u-v
   OR Convolution : set roots[*] = 1, a[j+k+i/2] += inv_fft ? -u : u;
  AND Convolution : set roots[*] = 1, a[j+k  ] += inv_fft ? -v : v;
  */
  for(int i=2; i<=N; i<<=1){
    int step = N / i;
    for(int j=0; j<N; j+=i) for(int k=0; k<i/2; k++){
      cpx u = a[j+k], v = a[j+k+i/2] * root[step * k];
      a[j+k] = u+v; a[j+k+i/2] = u-v;
    }
  }
  if(inv_fft) for(int i=0; i<N; i++) a[i] /= N; // skip for AND/OR convolution.
}
vector<ll> multiply(const vector<ll> &_a, const vector<ll> &_b){
  vector<cpx> a(all(_a)), b(all(_b));
  int N = 2; while(N < a.size() + b.size()) N <<= 1;
  a.resize(N); b.resize(N); FFT(a); FFT(b);
  for(int i=0; i<N; i++) a[i] *= b[i];
  vector<ll> ret(N); FFT(a, 1); // NTT : just return a
  for(int i=0; i<N; i++) ret[i] = llround(a[i].real());
  while(ret.size() > 1 && ret.back() == 0) ret.pop_back();
  return ret;
}
vector<ll> multiply_mod(const vector<ll> &a, const vector<ll> &b, const ull mod){
  int N = 2; while(N < a.size() + b.size()) N <<= 1;
  vector<cpx> v1(N), v2(N), r1(N), r2(N);
  for(int i=0; i<a.size(); i++) v1[i] = cpx(a[i] >> 15, a[i] & 32767);
  for(int i=0; i<b.size(); i++) v2[i] = cpx(b[i] >> 15, b[i] & 32767);
  FFT(v1); FFT(v2);
  for(int i=0; i<N; i++){
    int j = i ? N-i : i;
    cpx ans1 = (v1[i] + conj(v1[j])) * cpx(0.5, 0);
    cpx ans2 = (v1[i] - conj(v1[j])) * cpx(0, -0.5);
    cpx ans3 = (v2[i] + conj(v2[j])) * cpx(0.5, 0);
    cpx ans4 = (v2[i] - conj(v2[j])) * cpx(0, -0.5);
    r1[i] = (ans1 * ans3) + (ans1 * ans4) * cpx(0, 1);
    r2[i] = (ans2 * ans3) + (ans2 * ans4) * cpx(0, 1);
  }
  vector<ll> ret(N); FFT(r1, true); FFT(r2, true);
  for(int i=0; i<N; i++){
    ll av = llround(r1[i].real()) % mod;
    ll bv = ( llround(r1[i].imag()) + llround(r2[i].real()) ) % mod;
    ll cv = llround(r2[i].imag()) % mod;
    ret[i] = (av << 30) + (bv << 15) + cv;
    ret[i] %= mod; ret[i] += mod; ret[i] %= mod;
  }
  while(ret.size() > 1 && ret.back() == 0) ret.pop_back();
  return ret;
}
template<char op> vector<ll> FWHT_Conv(vector<ll> a, vector<ll> b){
  int n = max({(int)a.size(), (int)b.size() - 1, 1});
  if(__builtin_popcount(n) != 1) n = 1 << (__lg(n) + 1);
  a.resize(n); b.resize(n); FWHT<op>(a); FWHT<op>(b);
  for(int i=0; i<n; i++) a[i] = a[i] * b[i] % M;
  FWHT<op>(a, true); return a;
}
vector<ll> SubsetConvolution(vector<ll> p, vector<ll> q){ // N log^2 N
  int n = max({(int)p.size(), (int)q.size() - 1, 1}), w = __lg(n);
  if(__builtin_popcount(n) != 1) n = 1 << (w + 1);
  p.resize(n); q.resize(n); vector<ll> res(n);
  vector<vector<ll>> a(w+1, vector<ll>(n)), b(a);
  for(int i=0; i<n; i++) a[__builtin_popcount(i)][i] = p[i];
  for(int i=0; i<n; i++) b[__builtin_popcount(i)][i] = q[i];
  for(int bit=0; bit<=w; bit++) FWHT<'|'>(a[bit]), FWHT<'|'>(b[bit]);
  for(int bit=0; bit<=w; bit++){
    vector<ll> c(n); // Warning : MOD
    for(int i=0; i<=bit; i++) for(int j=0; j<n; j++) c[j] += a[i][j] * b[bit-i][j] % M;
    for(auto &i : c) i %= M;
    FWHT<'|'>(c, true);
    for(int i=0; i<n; i++) if(__builtin_popcount(i) == bit) res[i] = c[i];
  }
  return res;
}
vector<ll> Trim(vector<ll> a, size_t sz){ a.resize(min(a.size(), sz)); return a; }
vector<ll> Inv(vector<ll> a, size_t sz){
  vector<ll> q(1, Pow(a[0], M-2, M)); // 1/a[0]
  for(int i=1; i<sz; i<<=1){
    auto p = vector<ll>{2} - Multiply(q, Trim(a, i*2)); // polynomial minus
    q = Trim(Multiply(p, q), i*2);
  }
  return Trim(q, sz);
}
vector<ll> Division(vector<ll> a, vector<ll> b){
  if(a.size() < b.size()) return {};
  size_t sz = a.size() - b.size() + 1; auto ra = a, rb = b;
  reverse(ra.begin(), ra.end()); ra = Trim(ra, sz);
  reverse(rb.begin(), rb.end()); rb = Inv(Trim(rb, sz), sz);
  auto res = Trim(Multiply(ra, rb), sz);
  for(int i=sz-(int)a.size(); i>0; i--) res.push_back(0);
  reverse(res.begin(), res.end()); while(!res.empty() && !res.back()) res.pop_back();
  return res;
}
vector<ll> Modular(vector<ll> a, vector<ll> b){ return a - Multiply(b, Division(a, b)); }
ll Evaluate(const vector<ll> &a, ll x){
  ll res = 0;
  for(int i=(int)a.size()-1; i>=0; i--) res = (res * x + a[i]) % M;
  return res >= 0 ? res : res + M;
}
vector<ll> Derivative(const vector<ll> &a){
  if(a.size() <= 1) return {};
  vector<ll> res(a.size() - 1);
  for(int i=0; i+1<a.size(); i++) res[i] = (i+1) * a[i+1] % M;
  return res;
}
vector<vector<ll>> PolynomialTree(const vector<ll> &x){
  int n = x.size(); vector<vector<ll>> tree(n*2-1);
  function<void(int,int,int)> build = [&](int node, int s, int e){
    if(e-s == 1){ tree[node] = vector<ll>{-x[s], 1}; return; }
    int m = s + (e-s)/2, v = node + (m-s)*2;
    build(node+1, s, m); build(v, m, e);
    tree[node] = Multiply(tree[node+1], tree[v]);
  }; build(0, 0, n); return tree;
}
vector<ll> MultipointEvaluation(const vector<ll> &a, const vector<ll> &x){ // n log^2 n
  if(x.empty()) return {}; if(a.empty()) return vector<ll>(x.size(), 0);
  int n = x.size(); auto tree = PolynomialTree(x); vector<ll> res(n);
  function<void(int,int,int,vector<ll>)> eval = [&](int node, int s, int e, vector<ll> f){
    f = Modular(f, tree[node]);
    if(e-s == 1){ res[s] = f[0]; return; }
    if(f.size() < 150){ for(int i=s; i<e; i++) res[i] = Evaluate(f, x[i]); return; }
    int m = s + (e-s)/2, v = node + (m-s)*2;
    eval(node+1, s, m, f); eval(v, m, e, f);
  }; eval(0, 0, n, a);
  return res;
}
vector<ll> Interpolation(const vector<ll> &x, const vector<ll> &y){ // n log^2 n
  assert(x.size() == y.size()); if(x.empty()) return {};
  int n = x.size(); auto tree = PolynomialTree(x);
  auto res = MultipointEvaluation(Derivative(tree[0]), x);
  for(int i=0; i<n; i++) res[i] = y[i] * Pow(res[i], M-2, M) % M; // y[i] / res[i]
  function<vector<ll>(int,int,int)> calc = [&](int node, int s, int e){
    if(e-s == 1) return vector<ll>{res[s]};
    int m = s + (e-s)/2, v = node + (m-s)*2;
    return Multiply(calc(node+1, s, m), tree[v]) + Multiply(calc(v, m, e), tree[node+1]);
  };
  return calc(0, 0, n);
}
vector<double> interpolate(vector<double> x, vector<double> y, int n){ // n^2
  vector<double> res(n), temp(n);
  for(int k=0; k<n-1; k++) for(int i=k+1; i<n; i++) y[i] = (y[i] - y[k]) / (x[i] - x[k]);
  double last = 0; temp[0] = 1;
  for(int k=0; k<n; k++){
  for(int i=0; i<n; i++) res[i] += y[k] * temp[i], swap(last, temp[i]), temp[i] -= last * x[k];
  }
  return res;
}//for numerical precision, x[k]=c*cos(k*pi/(n-1))
vector<ll> Interpolation_0_to_n(vector<ll> y){ // n^2
  int n = y.size();
  vector<ll> res(n), tmp(n), x; // x[i] = i / (i+1)
  for(int i=0; i<n; i++) x.push_back(Pow(i+1, M-2));
  for(int k=0; k+1<n; k++) for(int i=k+1; i<n; i++)
    y[i] = (y[i] - y[k] + M) * x[i-k-1] % M;
  ll lst = 0; tmp[0] = 1;
  for(int k=0; k<n; k++) for(int i=0; i<n; i++) {
    res[i] = (res[i] + y[k] * tmp[i]) % M;
    swap(lst, tmp[i]);
    tmp[i] = (tmp[i] - lst * k) % M;
    if(tmp[i] < 0) tmp[i] += M;
  }
  return res;
}
vector<ll> Shift(const vector<ll> &f, ll c){ // O(n log n)
  if(f.size() <= 1 || c == 0) return f; // return f(x+c)
  ll n = f.size(), pw = 1; c = (c % M + M) % M;
  vector<ll> fac(n,1), inv(n,1), a(n), b(n);
  for(int i=2; i<n; i++) fac[i] = fac[i-1] * i % M;
  inv[n-1] = Pow(fac[n-1], M-2);
  for(int i=n-2; i>=2; i--) inv[i] = inv[i+1] * (i+1) % M;
  for(int i=0; i<n; i++, pw=pw*c%M)
    a[i] = f[i] * fac[i] % M, b[i] = pw * inv[i] % M;
  reverse(b.begin(), b.end()); a = Multiply(a, b);
  a = vector<ll>(a.begin()+n-1, a.begin()+n+n-1);
  for(int i=0; i<n; i++) a[i] = a[i] * inv[i] % M;
  return a;
}