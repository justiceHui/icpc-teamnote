/**
 * Author: Aeren
 * License: 
 * Source: https://github.com/Aeren1564/Algorithms/blob/master/Algorithm_Implementations_Cpp/Numeric/Number_Theory/xudyh_sieve.sublime-snippet & https://github.com/Aeren1564/Algorithms/blob/master/Algorithm_Implementations_Cpp/Numeric/Number_Theory/dirichlet_convolution_formulae.sublime-snippet
 * Description: calculate prefix sum of multiplicative function
 * Problem: https://judge.yosupo.jp/problem/sum_of_totient_function
 * Code: https://judge.yosupo.jp/submission/172988
 */

/* e(x) = [x==1], 1(x) = 1, id_k(x) = x^k
mu: mobius function, id(x) = x
phi: euler totient function
sigma_k: sum of k-th power of divisors
sigma = sigma_1, d = tau = sigma_0
sigma_k = id_k * 1  | sigma = id * 1
id_k = sigma_k * mu | id = sigma * mu
e = 1 * mu | d = 1 * 1 | 1 = d * mu
phi * 1 = id | phi = id * mu | sigma = phi * d
g = f * 1 iff f = g * mu */
template<class T, class F1, class F2, class F3>
struct xudyh_sieve{
  T th; // threshold, 2(single query) ~ 5 * MAXN^2/3
  F1 pf; F2 pg; F3 pfg;
  // prefix sum of f(up to th), g(easy to calc), f*g(easy to calc)
  unordered_map<T, T> mp; // f * g means dirichlet conv.
  xudyh_sieve(T th,F1 pf,F2 pg,F3 pfg):th(th),pf(pf),pg(pg),pfg(pfg){}
  // Calculate the preix sum of a multiplicative f up to n
  T query(T n){ // O(n^2/3)
    if(n <= th) return pf(n); if(mp.count(n)) return mp[n];
    T res = pfg(n);
    for(T low = 2, high = 2; low <= n; low = high + 1){
      high = n / (n / low);
      res -= (pg(high) - pg(low - 1)) * query(n / low); // MOD
    }
    return mp[n] = res / pg(1);//Pow(pg(1),MOD-2)?
  }
};