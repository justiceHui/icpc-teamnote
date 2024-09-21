/**
 * Author:
 * License:
 * Source:
   * FFT/Mul/MulMod: https://github.com/koosaga/DeobureoMinkyuParty/blob/master/teamnote.pdf
   * MultiEval/FastInterpolation: https://github.com/abc864197532/std_abs/blob/main/codebook/Polynomial/Operation.cpp
   * Log/Exp: https://github.com/koosaga/olympiad/blob/master/Library/codes/math/algebra.cpp
 * NTT/Mul: https://judge.yosupo.jp/submission/193488
 * FFT/MulMod: https://judge.yosupo.jp/submission/193507
 * FWHT-AND: https://judge.yosupo.jp/submission/193489
 * FWHT-XOR: https://judge.yosupo.jp/submission/193490
 * FWHT-OR/SubsetConv: https://judge.yosupo.jp/submission/193491
 * 
 * Inv: https://judge.yosupo.jp/submission/193492
 * Div/Mod: https://judge.yosupo.jp/submission/193493
 * MultiEval: https://judge.yosupo.jp/submission/193494
 * FastInterpolation: https://judge.yosupo.jp/submission/193495
 * 
 * Log: https://judge.yosupo.jp/submission/193505
 * Exp: https://judge.yosupo.jp/submission/193506
 * Sqrt: https://judge.yosupo.jp/submission/193499
 * Pow: https://judge.yosupo.jp/submission/193500
 * TaylorShift: https://judge.yosupo.jp/submission/193501
 * SamplingShift: https://judge.yosupo.jp/submission/193502
 * 
 * SlowInterpolation: ???
 */


// 998,244,353 = 119 23, w 3 | 2,281,701,377 = 17 27, w 3
// 167,772,161 =  10 25, w 3 | 2,483,027,969 = 37 26, w 3
// 469,762,049 =  26 26, w 3 | 2,013,265,921 = 15 27, w 31
using real_t = double; using cpx = complex<real_t>;
void FFT(vector<cpx> &a, bool inv_fft=false){
  int N = a.size(); vector<cpx> root(N/2);//root[0]=1
  for(int i=1, j=0; i<N; i++){ int bit = N / 2;
    while(j >= bit) j -= bit, bit >>= 1;
    if(i < (j += bit)) swap(a[i], a[j]);
  } long double ang = 2 * acosl(-1) / N * (inv_fft ? -1 : 1);
  for(int i=0; i<N/2; i++)root[i]=cpx(cosl(ang*i),sinl(ang*i));
/* NTT : ang = pow(w, (mod-1)/n) % mod, inv_fft -> ang^{-1}, root[i] = root[i-1] * ang
XOR Convolution: roots[*]=1, a[j+k] = u+v, a[j+k+i/2] = u-v
 OR Convolution: roots[*]=1, a[j+k+i/2] += inv_fft ? -u : u;
AND Convolution: roots[*]=1, a[j+k    ] += inv_fft ? -v : v; */
  for(int i=2; i<=N; i<<=1){ int step = N / i;
    for(int j=0; j<N; j+=i) for(int k=0; k<i/2; k++){
        cpx u = a[j+k], v = a[j+k+i/2] * root[step * k];
        a[j+k] = u+v; a[j+k+i/2] = u-v;
  } } // inv_fft: skip for AND/OR convolution.
  if(inv_fft) for(int i=0; i<N; i++) a[i] /= N;
}
vector<ll> Mul(const vector<ll> &_a, const vector<ll> &_b){
  vector<cpx> a(all(_a)), b(all(_b)); // (NTT) 2^19 700ms
  int N = 2; while(N < a.size() + b.size()) N <<= 1;
  a.resize(N); b.resize(N); FFT(a); FFT(b);
  for(int i=0; i<N; i++) a[i] *= b[i]; // mod?
  vector<ll> ret(N); FFT(a, 1); // NTT : just return a
  for(int i=0; i<N; i++) ret[i] = llround(a[i].real());
  while(ret.size() > 1 && ret.back() == 0) ret.pop_back();
  return ret; }
vector<ll> MulMod(const vector<ll> &a, const vector<ll> &b, const unsigned long long mod){ // (FFT) 2^19 1000ms
  int N = 2; while(N < a.size() + b.size()) N <<= 1;
  vector<cpx> v1(N), v2(N), r1(N), r2(N);
  for(int i=0;i<a.size();i++)v1[i] = cpx(a[i]>>15, a[i]&32767);
  for(int i=0;i<b.size();i++)v2[i] = cpx(b[i]>>15, b[i]&32767);
  FFT(v1); FFT(v2);
  for(int i=0; i<N; i++){ int j = i ? N-i : i;
    cpx ans1 = (v1[i] + conj(v1[j])) * cpx(0.5, 0);
    cpx ans2 = (v1[i] - conj(v1[j])) * cpx(0, -0.5);
    cpx ans3 = (v2[i] + conj(v2[j])) * cpx(0.5, 0);
    cpx ans4 = (v2[i] - conj(v2[j])) * cpx(0, -0.5);
    r1[i] = (ans1 * ans3) + (ans1 * ans4) * cpx(0, 1);
    r2[i] = (ans2 * ans3) + (ans2 * ans4) * cpx(0, 1);
  } vector<ll> ret(N); FFT(r1, true); FFT(r2, true);
  for(int i=0; i<N; i++){
    ll av = llround(r1[i].real()) % mod;
    ll bv = (llround(r1[i].imag()) + llround(r2[i].real()))%mod;
    ll cv = llround(r2[i].imag()) % mod;
    ret[i] = (av << 30) + (bv << 15) + cv;
    ret[i] %= mod; ret[i] += mod; ret[i] %= mod;
  } while(ret.size() > 1 && ret.back() == 0) ret.pop_back();
  return ret; }
template<char op>vector<ll>FWHT_Conv(vector<ll> a,vector<ll> b){
  int n = max({(int)a.size(), (int)b.size()-1, 1});//2^20 700ms
  if(__builtin_popcount(n) != 1) n = 1 << (__lg(n) + 1);
  a.resize(n); b.resize(n); FWHT<op>(a); FWHT<op>(b);
  for(int i=0; i<n; i++) a[i] = a[i] * b[i] % M;
  FWHT<op>(a, true); return a;
} // subset: C[k] = sum_{i and j = 0, i or j = k} A[i] * B[j]
vector<ll> SubsetConvolution(vector<ll> p,vector<ll> q){//Nlog2N
  int n = max({(int)p.size(), (int)q.size()-1, 1}), w=__lg(n);
  if(__builtin_popcount(n) != 1) n = 1 << (w + 1); // 2^20 4s
  p.resize(n); q.resize(n); vector<ll> res(n); // SOS DP: 2.5s
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
  } return res; }
vector<ll> Trim(vector<ll> a, size_t sz){ a.resize(min(a.size(), sz)); return a; }
vector<ll> Inv(const vector<ll> &a, size_t sz){ // 5e5 2s
  vector<ll> q(1, Pow(a[0], M-2)); // 1/a[0], a[0] != 0
  for(int i=1; i<sz; i<<=1){ // - : polynomial minus
    auto p = vector<ll>{2} - Mul(q, Trim(a, i*2));
    q = Trim(Mul(p, q), i*2);
  } return Trim(q, sz); }
vector<ll> Div(const vector<ll> &a, const vector<ll> &b){
  if(a.size() < b.size()) return {}; // 5e5 4s
  size_t sz = a.size() - b.size() + 1; auto ra = a, rb = b;
  reverse(ra.begin(), ra.end()); ra = Trim(ra, sz);
  reverse(rb.begin(), rb.end()); rb = Inv(Trim(rb,sz), sz);
  auto res = Trim(Mul(ra, rb), sz); res.resize(sz);
  reverse(res.begin(), res.end());
  while(!res.empty() && !res.back()) res.pop_back();
  return res; }
vector<ll> Mod(const vector<ll> &a, const vector<ll> &b){ return a - Mul(b, Div(a, b)); }
ll Evaluate(const vector<ll> &a, ll x){ ll res = 0;
  for(int i=(int)a.size()-1; i>=0; i--) res = (res*x+a[i]) % M;
  return res >= 0 ? res : res + M; }
vector<ll> Derivative(const vector<ll> &a){
  if(a.size() <= 1) return {}; vector<ll> res(a.size()-1);
  for(int i=0; i+1<a.size(); i++) res[i] = (i+1) * a[i+1] % M;
  return res; }
vector<ll> Integrate(const vector<ll> &a){
  int n = a.size(); vector<ll> res(n+1);
  for(int i=0; i<n; i++) res[i+1] = a[i] * Pow(i+1, M-2) % M;
  return res; }
vector<ll> MultipointEvaluation(vector<ll> a, vector<ll> x){
  if(x.empty()) return {}; int n = x.size(); // 2^17 7s
  vector<vector<ll>> up(n*2), dw(n*2);
  for(int i=0; i<n; i++) up[i+n] = {x[i]?M-x[i]:0, 1};
  for(int i=n-1; i; i--) up[i] = Mul(up[i*2], up[i*2+1]);
  dw[1] = Mod(a, up[1]);
  for(int i=2; i<n*2; i++) dw[i] = Mod(dw[i/2], up[i]);
  vector<ll> y(n); for(int i=0; i<n; i++) y[i] = dw[i+n][0];
  return y; }
vector<ll> Interpolation(vector<ll> x, vector<ll> y){//2^17 10s
  int n = x.size(); vector<vector<ll>> up(n*2), dw(n*2);
  for(int i=0; i<n; i++) up[i+n] = {x[i]?M-x[i]:0, 1};
  for(int i=n-1; i; i--) up[i] = Mul(up[i*2], up[i*2+1]);
  vector<ll> a = MultipointEvaluation(Derivative(up[1]), x);
  for(int i=0; i<n; i++) a[i] = y[i] * Pow(a[i], M-2) % M;
  for(int i=0; i<n; i++) dw[i+n] = {a[i]};
  for(int i=n-1; i; i--){
    auto l = Mul(dw[i*2],up[i*2+1]), r = Mul(dw[i*2+1],up[i*2]);
    dw[i].resize(l.size());
    for(int j=0; j<l.size(); j++) dw[i][j] = (l[j] + r[j]) % M;
  } return dw[1]; }
vector<ll> Log(const vector<ll> &a, size_t sz){ // 5e5 3.5s
  assert(a.size() > 0 && a[0] == 1); // int f'(x)/f(x), resize!
  return Trim(Integrate(Mul(Derivative(a), Inv(a,sz))), sz); }
vector<ll> Exp(const vector<ll> &a, size_t sz){ // 5e5 5s
  vector<ll> res = {1}; if(a.empty()) return {1};
  assert(a.size() > 0 && a[0] == 0);
  for(int i=1; i<sz; i<<=1){
    auto t = Trim(a, i*2) - Log(res, i*2);
    if(++t[0] == M) t[0] = 0; // t[0] += 1, mod
    res = Trim(Mul(res, t), i*2);
  } return Trim(res, sz); } // need resize
vector<ll> Pow(const vector<ll> f, ll e, int sz){ // 5e5 8s
  if(e == 0){ vector<ll> res(sz); res[0] = 1; return res; }
  ll p = 0; while(p < f.size() && f[p] == 0 && p*e < sz) p++;
  if(p == f.size() || p*e >= sz) return vector<ll>(sz, 0);
  vector<ll> a(f.begin()+p, f.end()); ll k = a[0]; // not f[0]
  for(auto &i : a) i = mul(i, Pow(k, M-2));
  a = Log(a, sz); for(auto &i : a) i = mul(i, e%M);
  a = Exp(a, sz); for(auto &i : a) i = mul(i, Pow(k, e));
  vector<ll> res(p*e); res.insert(res.end(), a.begin(), a.end());
  res.resize(sz); return res; }
vector<ll> SqrtImpl(vector<ll> a){
  if (a.empty()) return {0}; int inv2=(M+1)/2;
  int z = DiscreteSqrt(a[0], M), n = a.size();
  if (z == -1) return {-1}; vector<ll> q(1, z);
  for(int m=1; m<n; m<<=1){
    if(n < m*2) a.resize(m*2);;; q.resize(m*2);
    auto f2 = Mul(q, q); f2.resize(m*2);
    for(int i=0; i<m*2; i++) f2[i] = sub(f2[i], a[i]);
    f2 = Mul(f2, Inv(q, q.size())); f2.resize(m*2);
    for(int i=0; i<m*2; i++) q[i] = sub(q[i], mul(f2[i], inv2));
  } q.resize(n); return q; }
vector <ll> Sqrt(vector <ll> a){ // nlgn, fail -> -1, 5e5 5.5s
  int n = a.size(), m = 0; while(m < n && a[m] == 0) m++;
  if(m == n) return vector<ll>(n); if(m & 1) return {-1};
  auto s = SqrtImpl(vector<ll>(a.begin()+m, a.end()));
  if(s[0] == -1) return {-1}; vector<ll> res(n);
  for(int i=0; i<s.size(); i++) res[i+m/2] = s[i];
  return res; }
vector<ll> TaylorShift(vector<ll> a, ll c){//f(x+c), 2^19 700ms
  int n = a.size(); // fac[i] = i!, ifc[i] = inv(i!)
  for(int i=0; i<n; i++) a[i] = mul(a[i], fac[i]);
  reverse(all(a)); vector<ll> b(n); ll w = 1;
  for(int i=0; i<n; i++) b[i] = mul(ifc[i], w), w = mul(w, c);
  a = Mul(a, b); a.resize(n); reverse(all(a));
  for(int i=0; i<n; i++) a[i] = mul(a[i], ifc[i]);
  return a; }
vector<ll> SamplingShift(vector<ll> a, ll c, int m){ // 2^19 ~2s
  // given f(0), f(1), ..., f(n - 1), warning: fac size
  // return f(c), f(c + 1), ..., f(c + m - 1)
  int n = a.size(); vector<ll> b(ifc.begin(), ifc.begin()+n);
  for(int i=0; i<n; i++) a[i] = mul(a[i],ifc[i]);
  for(int i=1; i<n; i+=2) b[i] = sub(0, b[i]);
  a = Mul(a, b); a.resize(n); ll w = 1;
  for(int i=0; i<n; i++) a[i] = mul(a[i], fac[i]);; reverse(all(a));
  for(int i=0; i<n; w=mul(w, sub(c,i++))) b[i] = mul(ifc[i],w);
  a = Mul(a, b); a.resize(n); reverse(all(a)); //warning: N->M
  for(int i=0; i<n; i++) a[i] = mul(a[i], ifc[i]);; a.resize(m);
  b = vector<ll>(ifc.begin(), ifc.begin()+m);
  a = Mul(a, b); a.resize(m);
  for(int i=0; i<m; i++) a[i] = mul(a[i], fac[i]);
  return a; }
vector<double> interpolate(vector<double> x, vector<double> y, int n){ // n^2
  vector<double> res(n), temp(n);
  for(int k=0; k<n-1; k++) for(int i=k+1; i<n; i++) y[i] = (y[i] - y[k]) / (x[i] - x[k]);
  double last = 0; temp[0] = 1;
  for(int k=0; k<n; k++){
  for(int i=0; i<n; i++) res[i] += y[k] * temp[i], swap(last, temp[i]), temp[i] -= last * x[k];
  }
  return res; }//for numerical precision, x[k]=c*cos(k*pi/(n-1))
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
  } return res; }