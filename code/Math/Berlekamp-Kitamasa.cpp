/**
 * Author: koosaga
 * License: 
 * Source: https://gist.github.com/koosaga/d4afc4434dbaa348d5bef0d60ac36aa4
 * Problem (berlekamp): https://judge.yosupo.jp/problem/find_linear_recurrence
 * Code (berlekamp): https://judge.yosupo.jp/submission/173130
 * Problem (get nth): https://www.acmicpc.net/problem/13727
 * Code (get nth): https://www.acmicpc.net/source/share/1189b100e914451fb8d604f0a944f23d
 * Problem (det): https://www.acmicpc.net/problem/27071
 * Code (det): http://boj.kr/ea349ecc44d246bc8492847fa1567042
 */

const int mod = 1e9+7; ll pw(ll a, ll b){/*a^b mod M*/}
vector<int> berlekamp_massey(vector<int> x){
  int n = x.size(),L=0,m=0; ll b=1; if(!n) return {};
  vector<int> C(n), B(n), T; C[0]=B[0]=1;
  for(int i=0; ++m && i<n; i++){ ll d = x[i] % mod;
    for(int j=1; j<=L; j++) d = (d + 1LL * C[j] * x[i-j]) % mod;
    if(!d) continue; T=C; ll c = d * pw(b, mod-2) % mod;
    for(int j=m; j<n; j++) C[j] = (C[j] - c * B[j-m]) % mod;
    if(2 * L <= i) L = i-L+1, B = T, b = d, m = 0;
  }
  C.resize(L+1); C.erase(C.begin());
  for(auto &i : C) i = (mod - i) % mod; return C;
} // O(NK + N log mod)
int get_nth(vector<int> rec, vector<int> dp, ll n){
  int m = rec.size(); vector<int> s(m), t(m); ll ret=0;
  s[0] = 1; if(m != 1) t[1] = 1; else t[0] = rec[0];
  auto mul = [&rec](vector<int> v, vector<int> w){
    int m = v.size(); vector<int> t(2*m);
    for(int j=0; j<m; j++) for(int k=0; k<m; k++){
      t[j+k] = (t[j+k] + 1LL * v[j] * w[k]) % mod;
    }
    for(int j=2*m-1; j>=m; j--) for(int k=1; k<=m; k++){
      t[j-k] = (t[j-k] + 1LL * t[j] * rec[k-1]) % mod;
    }
    t.resize(m); return t;
  };
  for(; n; n>>=1, t=mul(t,t)) if(n & 1) s=mul(s,t);
  for(int i=0; i<m; i++) ret += 1LL * s[i] * dp[i] % mod;
  return ret % mod;
} // O(N2 log X)
int guess_nth_term(vector<int> x, ll n){
  if(n < x.size()) return x[n];
  vector<int> v = berlekamp_massey(x);
  return v.empty() ? 0 : get_nth(v, x, n);
}
struct elem{int x, y, v;}; // A_(x, y) <- v, 0-based. no duplicate please..
vector<int> get_min_poly(int n, vector<elem> M){
  // smallest poly P such that A^i = sum_{j < i} {A^j \times P_j}
  vector<int> rnd1, rnd2, gobs; mt19937 rng(0x14004);
  auto gen = [&rng](int lb, int ub){ return uniform_int_distribution<int>(lb, ub)(rng); };
  for(int i=0; i<n; i++) rnd1.push_back(gen(1, mod-1)), rnd2.push_back(gen(1, mod-1));
  for(int i=0; i<2*n+2; i++){ int tmp = 0;
    for(int j=0; j<n; j++) tmp = (tmp + 1LL * rnd2[j] * rnd1[j]) % mod;
    gobs.push_back(tmp); vector<int> nxt(n);
    for(auto &j : M) nxt[j.x] = (nxt[j.x] + 1LL * j.v * rnd1[j.y]) % mod;
    rnd1 = nxt;
  } auto v = berlekamp_massey(gobs);
  return vector<int>(v.rbegin(), v.rend());
}
ll det(int n, vector<elem> M){
  vector<int> rnd; mt19937 rng(0x14004);
  auto gen = [&rng](int lb, int ub){ return uniform_int_distribution<int>(lb, ub)(rng); };
  for(int i=0; i<n; i++) rnd.push_back(gen(1, mod-1));
  for(auto &i : M) i.v = 1LL * i.v * rnd[i.y] % mod;
  auto sol = get_min_poly(n, M)[0]; if(n % 2 == 0) sol = mod - sol;
  for(auto &i : rnd) sol = 1LL * sol * pw(i, mod-2) % mod;
  return sol;
}