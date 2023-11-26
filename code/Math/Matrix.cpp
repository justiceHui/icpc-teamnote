/**
 * Author: JusticeHui
 * License: CC BY-NC-SA
 * Source: JusticeHui
 * Description: get RREF, rank, det, inverse matrix of A
 * Problem (rref): https://www.acmicpc.net/problem/20307
 * Code (rref): http://boj.kr/72e7455edc2044aa93cd0fa347b44c81
 * Problem (rank): https://www.acmicpc.net/problem/15737
 * Code (rank): http://boj.kr/bc9bbe60a5144744acf94289368c2e01
 * Problem (Det): https://judge.yosupo.jp/problem/matrix_det
 * Code (Det, Gauss): https://judge.yosupo.jp/submission/62842
 * Code (Det, Det): https://judge.yosupo.jp/submission/173048
 * Problem (Inv): https://www.acmicpc.net/problem/9254
 * Code (Inv): http://boj.kr/2e9185babd8b4c049b534d80c6951893
 */

template<typename T> // return {rref, rank, det, inv}
tuple<vector<vector<T>>, int, T, vector<vector<T>>> Gauss(vector<vector<T>> a, bool square=true){
  int n = a.size(), m = a[0].size(), rank = 0;
  vector<vector<T>> out(n, vector<T>(m, 0)); T det = T(1);
  for(int i=0; i<n; i++) if(square) out[i][i] = T(1);
  for(int i=0; i<m; i++){
    if(rank == n) break;
    if(IsZero(a[rank][i])){
      T mx = T(0); int idx = -1; // fucking precision error
      for(int j=rank+1; j<n; j++) if(mx < abs(a[j][i])) mx = abs(a[j][i]), idx = j;
      if(idx == -1 || IsZero(a[idx][i])){ det = 0; continue; }
      for(int k=0; k<m; k++){
        a[rank][k] = Add(a[rank][k], a[idx][k]);
        if(square)out[rank][k]=Add(out[rank][k],out[idx][k]);
      }
    }
    det = Mul(det, a[rank][i]);
    T coeff = Div(T(1), a[rank][i]);
    for(int j=0; j<m; j++) a[rank][j] = Mul(a[rank][j], coeff);
    for(int j=0; j<m; j++) if(square) out[rank][j] = Mul(out[rank][j], coeff);
    for(int j=0; j<n; j++){
      if(rank == j) continue;
      T t = a[j][i]; // Warning: [j][k], [rank][k]
      for(int k=0; k<m; k++) a[j][k] = Sub(a[j][k], Mul(a[rank][k], t));
      for(int k=0; k<m; k++) if(square) out[j][k] = Sub(out[j][k], Mul(out[rank][k], t));
    }
    rank++; // linear system: warning len(A) != len(A[0])
  } return {a, rank, det, out}; // linear system: get RREF(A|b)
} // 0 0 ... 0 b[i]: inconsistent, rank < len(A[0]): multiple
// get det(A) mod M, M can be composite number
// remove mod M -> get pure det(A) in integer
ll Det(vector<vector<ll>> a){//destroy matrix
  int n = a.size(); ll ans = 1;
  for(int i=0; i<n; i++){
    for(int j=i+1; j<n; j++){
      while(a[j][i] != 0){ // gcd step
        ll t = a[i][i] / a[j][i];
        if(t)for(int k=i;k<n;k++) a[i][k]=(a[i][k]-a[j][k]*t)%M;
        swap(a[i], a[j]); ans *= -1;
      }
    }
    ans = ans * a[i][i] % M; if(!ans) return 0;
  } return (ans + M) % M;
}