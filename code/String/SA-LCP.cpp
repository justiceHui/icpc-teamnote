// O(N \log N) + O(N)
// 서로 다른 부분 문자열의 개수 : n(n+1)/2 - sum(lcp)
// LCS : A+#+B, then do
/* int result = 0, pos = 0, B = N - A;
   for(int i=0; i<N-1; i++) if((sa[i] >= A) != (sa[i+1] >= A)){
   int t = min(lcp[i], A-1 - min(sa[i], sa[i+1]));
   if(t > res) res = t, pos = sa[i]; } */
vector<int> GetSA(const string &S){
  int N = S.size(), SZ = 256;
  vector<int> SA(N), C(max(N, SZ) + 1), X(N), Pos(N);
  for(int i=0; i<N; i++) Pos[i] = S[i];
  for(int i=0; i<N; i++) C[Pos[i]]++;
  for(int i=1; i<=SZ; i++) C[i] += C[i - 1];
  for(int i=N-1; ~i; i--) SA[--C[Pos[i]]] = i;
  for(int j=1; ; j<<=1){
    int p = 0; for(int i=N-j; i<N; i++) X[p++] = i;
    for(int i=0; i<N; i++) if(SA[i] >= j) X[p++] = SA[i] - j;
    fill(C.begin(), C.end(), 0); for(int i=0; i<N; i++) C[Pos[i]]++;
    partial_sum(C.begin(), C.end(), C.begin());
    for(int i=N-1; ~i; i--) SA[--C[Pos[X[i]]]] = X[i];
    X[SA[0]] = 0;
    for(int i=1; i<N; i++){
      X[SA[i]] = X[SA[i-1]];
      if(SA[i-1]+j < N && SA[i]+j < N && Pos[SA[i-1]] == Pos[SA[i]] && Pos[SA[i-1]+j] == Pos[SA[i]+j]) continue;
      X[SA[i]]++;
    }
    for(int i=0; i<N; i++) Pos[i] = X[i];
    SZ = Pos[SA[N-1]]; if(SZ == N-1) break;
  }
  return move(SA);
}
vector<int> GetLCP(const string &S, const vector<int> &SA){
  int N = S.size();
  vector<int> Pos(N), LCP(N);
  for(int i=0; i<N; i++) Pos[SA[i]] = i;
  for(int i=0, j=0; i<N; i++, j=max(j-1, 0)){
    if(Pos[i] == 0) continue;
    while(SA[Pos[i]-1]+j < N && SA[Pos[i]]+j < N && S[SA[Pos[i]-1]+j] == S[SA[Pos[i]]+j]) j++;
    LCP[Pos[i]] = j;
  }
  return move(LCP);
}
void Build(string A, string B){ // X=A.size(), Y=B.size()
  string S = A + "#" + B; vector<int> SA, LCP(X, 0);
  LCP = GetLCP(S, SA = GetSA(S));
  for(int i=0, len=X; i<N; i++){
    if(SA[i] >= X) len = X;
    else len = min(len, LCP[i]), Len[SA[i]] = max(Len[SA[i]], len);
  }
  for(int i=N-1, len=X; i>=0; i--){
    if(SA[i] >= X) len = X;
    else len = min(len, LCP[i+1]), Len[SA[i]] = max(Len[SA[i]], len);
  }
} // SA[i] < X, SA[i]+1 ~ SA+Len[SA[i]]