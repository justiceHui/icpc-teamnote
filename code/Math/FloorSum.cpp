// sum of floor((A*i+B)/M) over 0 <= i < N in O(log(N+M+A+B))
ll FloorSum(ll N, ll M, ll A, ll B){ // 1 <= N,M <= 1e9, 0 <= A,B < M
  ll R = 0;
  if(A >= M) R += N * (N - 1) / 2 * (A / M), A %= M;
  if(B >= M) R += B / M * N, B %= M;
  ll Y = (A * N + B) / M, X = Y * M - B;
  if(Y == 0) return R;
  R += (N - (X + A - 1) / A) * Y;
  R += FloorSum(Y, A, M, (A - X % A) % A);
  return R;
}