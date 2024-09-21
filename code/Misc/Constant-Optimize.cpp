namespace io { // thanks to cgiosy
  const signed IS=1<<20; char I[IS+1],*J=I;
  inline void daer(){if(J>=I+IS-64){
    char*p=I;do*p++=*J++;
    while(J!=I+IS);p[read(0,p,I+IS-p)]=0;J=I;}}
  template<int N=10,typename T=int>inline T getu(){
    daer();T x=0;int k=0;do x=x*10+*J-'0';
    while(*++J>='0'&&++k<N);++J;return x;}
  template<int N=10,typename T=int>inline T geti(){
    daer();bool e=*J=='-';J+=e;return(e?-1:1)*getu<N,T>();}
  struct f{f(){I[read(0,I,IS)]=0;}}flu; };
struct FastMod{ // typedef __uint128_t L;
  ull b, m; FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
  ull reduce(ull a){ // can be proven that 0 <= r < 2*b
    ull q = (ull)((L(m) * a) >> 64), r = a - q * b;
    return r >= b ? r - b : r;
} };
inline pair<uint32_t, uint32_t> Div(uint64_t a, uint32_t b){
  if(__builtin_constant_p(b)) return {a/b, a%b};
  uint32_t lo=a, hi=a>>32;
  __asm__("div %2" : "+a,a" (lo), "+d,d" (hi) : "r,m" (b));
  return {lo, hi}; // BOJ 27505, q r < 2^32
} // divide 10M times in ~400ms
ull mulmod(ull a, ull b, ull M){ // ~2x faster than int128
  ll ret = a * b - M * ull(1.L / M * a * b);
  return ret + M * (ret < 0) - M * (ret >= (ll)M);
} // safe for 0 ≤ a,b < M < (1<<63) when long double is 80bit