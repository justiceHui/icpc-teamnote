namespace io { // thanks to cgiosy
  const signed IS=1<<20;
  char I[IS+1],*J=I;
  inline void daer(){if(J>=I+IS-64){
    char*p=I;do*p++=*J++;
    while(J!=I+IS);p[read(0,p,I+IS-p)]=0;J=I;}}
  template<int N=10,typename T=int>inline T getu(){
    daer();T x=0;int k=0;do x=x*10+*J-'0';
    while(*++J>='0'&&++k<N);++J;return x;}
  template<int N=10,typename T=int>inline T geti(){
    daer();bool e=*J=='-';J+=e;return(e?-1:1)*getu<N,T>();}
  struct f{f(){I[read(0,I,IS)]=0;}}flu;
};
struct FastMod{ // typedef __uint128_t L;
  ull b, m;
  FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
  ull reduce(ull a){ // can be proven that 0 <= r < 2*b
    ull q = (ull)((L(m) * a) >> 64), r = a - q * b;
    return r >= b ? r - b : r;
  }
};
inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
  if(pow == 0) return 0;
  int hpow = 1 << (pow-1), seg = (x<hpow) ? ( (y<hpow) ? 0 : 3 ) : ( (y<hpow) ? 1 : 2 );
  const int rotateDelta[4] = {3, 0, 0, 1}; seg = (seg + rotate) & 3;
  int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
  int nrot = (rotate + rotateDelta[seg]) & 3;
  int64_t subSquareSize = int64_t(1) << (2*pow - 2);
  int64_t ans = seg * subSquareSize, add = hilbertOrder(nx, ny, pow-1, nrot);
  ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1); return ans;
}
struct Query{
  int s, e, x; ll order; void init(){ order = hilbertOrder(s, e, 21, 0); }
  bool operator < (const Query &t) const { return order < t.order; }
};