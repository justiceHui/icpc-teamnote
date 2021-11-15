// O(N \log N) + O(N)
// 서로 다른 부분 문자열의 개수 : n(n+1)/2 - sum(lcp)
// LCS : A+#+B, then do
/* int result = 0, pos = 0, B = N - A;
   for(int i=0; i<N-1; i++) if((sa[i] >= A) != (sa[i+1] >= A)){
   int t = min(lcp[i], A-1 - min(sa[i], sa[i+1]));
   if(t > res) res = t, pos = sa[i]; } */
int sa[1010101], lcp[1010101], pos[1010101];
void getSA(const string &s){
  int n = s.size(), m = 500;
  vector<int> cnt(max(n, m)+1), x(n+1), y(n+1);
  for(int i=1; i<=n; i++) cnt[x[i]=s[i-1]]++;
  for(int i=1; i<=m; i++) cnt[i] += cnt[i-1];
  for(int i=n; i; i--) sa[cnt[x[i]]--] = i;
  for(int len=1, pv=0, i; pv<n; len<<=1, m=pv){
    for(pv=0, i=n-len+1; i<=n; i++) y[++pv] = i;
    for(i=1; i<=n; i++) if(sa[i] > len) y[++pv] = sa[i] - len;
    for(i=0; i<=m; i++) cnt[i] = 0;
    for(i=1; i<=n; i++) cnt[x[y[i]]]++;
    for(i=1; i<=m; i++) cnt[i] += cnt[i-1];
    for(i=n; i>=1; i--) sa[cnt[x[y[i]]]--] = y[i];
    swap(x, y); pv = 1; x[sa[1]] = 1;
    for(i=1; i<n; i++){
      int a = sa[i], b = sa[i+1], a_len = a + len, b_len = b + len;
      if(a_len <= n && b_len <= n && y[a] == y[b] && y[a_len] == y[b_len]) x[sa[i+1]] = pv;
      else x[sa[i+1]] = ++pv;
    }
  }
  for(int i=0; i<n; i++) sa[i] = sa[i+1]-1, pos[sa[i]] = i;
}
void getLCP(const string &s){
  int n = s.size();
  for(int i=0,k=0; i<n; i++, k=max(k-1, 0)){
    if(pos[i] == n-1) continue;
    for(int j=sa[pos[i]+1]; s[i+k]==s[j+k]; k++);
    lcp[pos[i]] = k;
  }
}