static char buf[1 << 19]; // size : any number geq than 1024
static int idx = 0, bytes = 0;
static inline int _read() {
  if (!bytes || idx == bytes) {
    bytes = (int)fread(buf, sizeof(buf[0]), sizeof(buf), stdin);
    idx = 0;
  }
  return buf[idx++];
}
static inline int readInt() {
  int x = 0, s = 1, c = _read();
  while (c <= 32) c = _read();
  if (c == '-') s = -1, c = _read();
  while (c > 32) x = 10 * x + (c - '0'), c = _read();
  if (s < 0) x = -x; return x;
}
typedef __uint128_t L;
struct FastMod{
  ull b, m;
  FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
  ull reduce(ull a){
    ull q = (ull)((L(m) * a) >> 64), r = a - q * b; // can be proven that 0 <= r < 2*b
    return r >= b ? r - b : r;
  }
};
inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
  if(pow == 0) return 0;
  int hpow = 1 << (pow-1);
  int seg = (x<hpow) ? ( (y<hpow) ? 0 : 3 ) : ( (y<hpow) ? 1 : 2 );
  seg = (seg + rotate) & 3;
  const int rotateDelta[4] = {3, 0, 0, 1};
  int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
  int nrot = (rotate + rotateDelta[seg]) & 3;
  int64_t subSquareSize = int64_t(1) << (2*pow - 2);
  int64_t ans = seg * subSquareSize;
  int64_t add = hilbertOrder(nx, ny, pow-1, nrot);
  ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
  return ans;
}
struct Query{
  int s, e, x; ll order;
  void init(){ order = hilbertOrder(s, e, 21, 0); }
  bool operator < (const Query &t) const { return order < t.order; }
};