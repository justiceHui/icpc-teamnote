/**
 * Author: JusticeHui
 * License: CC BY-NC-SA
 * Source: JusticeHui
 * Description: 
 * Problem: https://www.acmicpc.net/problem/16667
 * Code: http://boj.kr/c485bacdd2764e5b9ffa4a783c3e11b7
 */

// con[i] \in {A(∀), E(∃)}, 0-based string
// variable: 1-based(parameter), 0-based(computing)
// (a or not b) -> {a, -b} in 1-based index
// return empty vector if satisfiable, else any solution
// T(x) = x << 1, F(x) = x << 1 | 1, I(x) = x ^ 1
vector<int> TwoQBF(int n, string con, vector<pair<int,int>> cnf){
  auto f = [](int v){ return v > 0 ? T(v-1) : F(-v-1); };
  for(auto &[a,b] : cnf) AddCNF(a=f(a), b=f(b));
  if(!TwoSAT(n)) return {}; int k = SCC.size();
  vector<int> has(k,-1), from(k), to(k), res(n, -1);
  for(int i=n-1; i>=0; i--){ // WARNING: index is scc id
    if(has[C[T(i)]] != -1 || has[C[F(i)]] != -1) return {};
    if(con[i] == 'A') has[C[T(i)]] = T(i), has[C[F(i)]] = F(i);
  }
  for(int i=0; i<k; i++) if(has[i] != -1) from[i] = to[i] = 1;
  for(int i=0; i<n+n; i++){
    for(auto j : Gph[i]) if(C[i] != C[j]) DAG[C[i]].push_back(C[j]);
  }
  for(int i=k-1; i>=0; i--){
    bool flag = false; // i -> A?
    for(auto j : DAG[i]) flag |= to[j];
    if(flag && to[i]) return {}; to[i] |= flag;
  }
  for(int i=0; i<k; i++) for(auto j : DAG[i]) from[j] |= from[i]; // A->i?
  for(int i=0; i<k; i++){
    if(has[i] != -1) for(auto v : SCC[i]) res[v/2] = v % 2 == has[i] % 2;
    else if(from[i]) for(auto v : SCC[i]) res[v/2] = v % 2 == 0;
    else if(to[i]) for(auto v : SCC[i]) res[v/2] = v % 2 == 1;
  }
  for(int i=0; i<n; i++) if(res[i] == -1) res[i] = C[F(i)] < C[T(i)];
  return res;
}