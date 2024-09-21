pair<vector<int>, vector<int>> SuffixArray(const string &s){
  int n = s.size(), m = max(n, 256);
  vector<int> sa(n), lcp(n), pos(n), tmp(n), cnt(m);
  auto counting_sort = [&](){
    fill(cnt.begin(), cnt.end(), 0);
    for(int i=0; i<n; i++) cnt[pos[i]]++;
    partial_sum(cnt.begin(), cnt.end(), cnt.begin());
    for(int i=n-1; i>=0; i--) sa[--cnt[pos[tmp[i]]]] = tmp[i];
  };
  for(int i=0; i<n; i++) sa[i] = i, pos[i] = s[i], tmp[i] = i;
  counting_sort();
  for(int k=1; ; k<<=1){ int p = 0;
    for(int i=n-k; i<n; i++) tmp[p++] = i;
    for(int i=0; i<n; i++) if(sa[i] >= k) tmp[p++] = sa[i] - k;
    counting_sort(); tmp[sa[0]] = 0;
    for(int i=1; i<n; i++){
      tmp[sa[i]] = tmp[sa[i-1]];
      if(sa[i-1]+k < n && sa[i]+k < n && pos[sa[i-1]] == pos[sa[i]] && pos[sa[i-1]+k] == pos[sa[i]+k]) continue;
      tmp[sa[i]] += 1;
    }
    swap(pos, tmp); if(pos[sa.back()] + 1 == n) break;
  }
  for(int i=0, j=0; i<n; i++, j=max(j-1,0)){
    if(pos[i] == 0) continue;
    while(sa[pos[i]-1]+j < n && sa[pos[i]]+j < n && s[sa[pos[i]-1]+j] == s[sa[pos[i]]+j]) j++;
    lcp[pos[i]] = j;
  } return {sa, lcp};
}
auto [SA,LCP] = SuffixArray(S); RMQ<int> rmq(LCP);
vector<int> Pos(N); for(int i=0; i<N; i++) Pos[SA[i]] = i;
auto get_lcp = [&](int a, int b){
    if(Pos[a] > Pos[b]) swap(a, b);
    return a == b ? (int)S.size() - a : rmq.query(Pos[a]+1, Pos[b]);
};
vector<pair<int,int>> can; // common substring {start, lcp}
vector<tuple<int,int,int>> valid; // valid substring [string, end_l~end_r]
for(int i=1; i<N; i++){
  if(SA[i] < X && SA[i-1] > X) can.emplace_back(SA[i], LCP[i]);
  if(i+1 < N && SA[i] < X && SA[i+1] > X) can.emplace_back(SA[i], LCP[i+1]);
}
for(int i=0; i<can.size(); i++){
  int skip = i > 0 ? min({can[i-1].second, can[i].second, get_lcp(can[i-1].first, can[i].first)}) : 0;
  valid.emplace_back(can[i].first, can[i].first + skip, can[i].first + can[i].second - 1);
}