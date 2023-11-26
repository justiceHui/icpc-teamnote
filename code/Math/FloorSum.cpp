/**
 * Author: Aeren
 * License: 
 * Source: https://github.com/Aeren1564/Algorithms/blob/master/Algorithm_Implementations_Cpp/Numeric/Number_Theory/weighted_floor_sum.sublime-snippet
 * Source(modsum): https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/ModSum.h
 * Problem: https://judge.yosupo.jp/problem/sum_of_floor_of_linear
 * Code: https://judge.yosupo.jp/submission/172980
 */

// sum of floor((A*i+B)/M) over 0 <= i < N in O(log(N+M+A+B))
// Also, sum of i * floor((A*i+B)/M) and floor((A*i+B)/M)^2
template<class T, class U> // T must be able to hold arg^2
array<U, 3> weighted_floor_sum(T n, T m, T a, T b){
  array<U, 3> res{}; auto[qa,ra]=div(a,m); auto[qb,rb]=div(b,m);
  if(T n2 = (ra * n + rb) / m){
    auto prv=weighted_floor_sum<T,U>(n2, ra, m, m-rb-1);
    res[0] += U(n-1)*n2 - prv[0];
    res[1] += (U(n-1)*n*n2 - prv[0] - prv[2]) / 2;
    res[2] += U(n-1)*(n2-1)*n2 - 2*prv[1] + res[0];
  }
  res[2] += U(n-1)*n*(2*n-1)/6 * qa*qa + U(n)*qb*qb;
  res[2] += U(n-1)*n * qa*qb + 2*res[0]*qb + 2*res[1]*qa;
  res[0] += U(n-1)*n/2 * qa + U(n)*qb;
  res[1] += U(n-1)*n*(2*n-1)/6 * qa + U(n-1)*n/2 * qb;
  return res;
}
ll modsum(ull to, ll c, ll k, ll m){
  c = (c % m + m) % m; k = (k % m + m) % m;
  return to*c + k*sumsq(to) - m*divsum(to, c, k, m);
} // sum (ki+c)%m 0<=i<to, O(log m) large constant