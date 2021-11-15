template<int M>
struct MINT{
  int v;
  MINT() : v(0) {}
  MINT(ll val){
    v = (-M <= val && val < M) ? val : val % M;
    if(v < 0) v += M;
  }
  // @TODO : pw, operator >> << == != + - * /
  friend MINT pw(MINT a, ll b){
    MINT ret= 1;
    while(b){
      if(b & 1) ret *= a;
      b >>= 1; a *= a;
    }
    return ret;
  }
  friend MINT inv(const MINT a) { return pw(a, M-2); }
};
namespace fft{
  using real_t = double; using cpx = complex<real_t>;
  void FFT(vector<cpx> &a, bool inv_fft = false){
    int N = a.size();
    vector<cpx> root(N/2);
    for(int i=1, j=0; i<N; i++){
      int bit = (N >> 1);
      while(j >= bit) j -= bit, bit >>= 1;
      j += bit;
      if(i < j) swap(a[i], a[j]);
    }
    real_t ang = 2 * acos(-1) / N * (inv_fft ? -1 : 1);
    for(int i=0; i<N/2; i++) root[i] = cpx(cos(ang * i), sin(ang * i));
    /*
    XOR Convolution : set roots[*] = 1.
    OR Convolution : set roots[*] = 1, and do following:
    if (!inv) a[j + k] = u + v, a[j + k + i/2] = u;
    else a[j + k] = v, a[j + k + i/2] = u - v;
    */
    for(int i=2; i<=N; i<<=1){
      int step = N / i;
      for(int j=0; j<N; j+=i) for(int k=0; k<i/2; k++){
        cpx u = a[j+k], v = a[j+k+i/2] * root[step * k];
        a[j+k] = u+v; a[j+k+i/2] = u-v;
      }
    }
    if(inv_fft) for(int i=0; i<N; i++) a[i] /= N; // skip for OR convolution.
  }
  vector<ll> multiply(const vector<ll> &_a, const vector<ll> &_b){
    vector<cpx> a(all(_a)), b(all(_b));
    int N = 2; while(N < a.size() + b.size()) N <<= 1;
    a.resize(N); b.resize(N);
    FFT(a); FFT(b);
    for(int i=0; i<N; i++) a[i] *= b[i];
    FFT(a, 1);
    vector<ll> ret(N);
    for(int i=0; i<N; i++) ret[i] = llround(a[i].real());
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
    FFT(r1, true); FFT(r2, true);
    vector<ll> ret(N);
    for(int i=0; i<N; i++){
      ll av = llround(r1[i].real()) % mod;
      ll bv = ( llround(r1[i].imag()) + llround(r2[i].real()) ) % mod;
      ll cv = llround(r2[i].imag()) % mod;
      ret[i] = (av << 30) + (bv << 15) + cv;
      ret[i] %= mod; ret[i] += mod; ret[i] %= mod;
    }
    return ret;
  }
  // 104,857,601   =  25 * 2^22 + 1, w = 3
  // 998,244,353   = 119 * 2^23 + 1, w = 3
  // 2,281,701,377 =  17 * 2^27 + 1, w = 3
  // 2,483,027,969 =  37 * 2^26 + 1, w = 3
  // 2,113,929,217 =  63 * 2^25 + 1, w = 5
  // 1,092,616,193 = 521 * 2^21 + 1, w = 3
  template<int W, int M>
  static void NTT(vector<MINT<M>> &f, bool inv_fft = false){
    using T = MINT<M>;
    int N = f.size();
    vector<T> root(N >> 1);
    for(int i=1, j=0; i<N; i++){
      int bit = N >> 1;
      while(j >= bit) j -= bit, bit >>= 1;
      j += bit;
      if(i < j) swap(f[i], f[j]);
    }
    T ang = pw(T(W), (M-1)/N); if(inv_fft) ang = inv(ang);
    root[0] = 1; for(int i=1; i<N>>1; i++) root[i] = root[i-1] * ang;
    for(int i=2; i<=N; i<<=1){
      int step = N / i;
      for(int j=0; j<N; j+=i) for(int k=0; k<i/2; k++){
        T u = f[j+k], v = f[j+k+(i>>1)] * root[k*step];
        f[j+k] = u + v; f[j+k+(i>>1)] = u - v;
      }
    }
    if(inv_fft){
      T rev = inv(T(N));
      for(int i=0; i<N; i++) f[i] *= rev;
    }
  }
  template<int W, int M>
  vector<MINT<M>> multiply_ntt(vector<MINT<M>> a, vector<MINT<M>> b){
    int N = 2; while(N < a.size() + b.size()) N <<= 1;
    a.resize(N); b.resize(N);
    NTT<W, M>(a); NTT<W, M>(b);
    for(int i=0; i<N; i++) a[i] *= b[i];
    NTT<W, M>(a, true);
    return a;
  }
}
template<int W, int M>
struct PolyMod{
  using T = MINT<M>;
  vector<T> a;
  PolyMod(){}
  PolyMod(T a0) : a(1, a0) { normalize(); }
  PolyMod(const vector<T> a) : a(a) { normalize(); }
  int size() const { return a.size(); }
  int deg() const { return a.size() - 1; }
  void normalize(){ while(a.size() && a.back() == T(0)) a.pop_back(); }
  T operator [] (int idx) const { return a[idx]; }
  typename vector<T>::const_iterator begin() const { return a.begin(); }
  typename vector<T>::const_iterator end() const { return a.end(); }
  void push_back(const T val) { a.push_back(val); }
  void pop_back() { a.pop_back(); }
  T evaluate(T x) const {
    T ret = T(0);
    for(int i=deg(); i>=0; i--) ret = ret * x + a[i];
    return ret;
  }
  PolyMod reversed() const {
    vector<T> b = a;
    reverse(b.begin(), b.end());
    return b;
  }
  PolyMod trim(int n) const {
    return vector<T>(a.begin(), a.begin() + min(n, size()));
  }
  // @TODO : operator + - *(with scala) /(with scala)
  PolyMod inv(int n){
    PolyMod q(T(1) / a[0]);
    for(int i=1; i<n; i<<=1){
      PolyMod p = PolyMod(2) - q * trim(i * 2);
      q = (p * q).trim(i * 2);
    }
    return q.trim(n);
  }
  PolyMod operator *= (const PolyMod &b){
    *this = fft::multiply_ntt<W, M>(a, b.a);
    normalize(); return *this;
  }
  PolyMod operator /= (const PolyMod &b){
    if(deg() < b.deg()) return *this = PolyMod();
    int sz = deg() - b.deg() + 1;
    PolyMod ra = reversed().trim(sz), rb = b.reversed().trim(sz).inv(sz);
    *this = (ra * rb).trim(sz);
    for(int i=sz-size(); i; i--) push_back(T(0));
    reverse(all(a)); normalize();
    return *this;
  }
  PolyMod operator %= (const PolyMod &b){
    if(deg() < b.deg()) return *this;
    PolyMod tmp = *this; tmp /= b; tmp *= b;
    *this -= tmp; normalize();
    return *this;
  }
  PolyMod operator * (const PolyMod &b) const { return PolyMod(*this) *= b; }
  PolyMod operator / (const PolyMod &b) const { return PolyMod(*this) /= b; }
  PolyMod operator % (const PolyMod &b) const { return PolyMod(*this) %= b; }
};
using mint = MINT<998244353>;
using poly = PolyMod<3, 998244353>;
mint Kitamasa(poly c, poly a, ll n){
  poly d = vector<mint>{1};
  poly xn = vector<mint>{0, 1};
  poly f;
  for(int i=0; i<c.size(); i++) f.push_back(-c[i]);
  f.push_back(1);
  while(n){
    if(n & 1) d = d * xn % f;
    n >>= 1; xn = xn * xn % f;
  }
  mint ret = 0;
  for(int i=0; i<=a.deg(); i++) ret += a[i] * d[i];
  return ret;
}