/**
 * Author: JusticeHui
 * License: CC BY-NC-SA
 * Source: JusticeHui
 * Description: count tandem repeats and get maximum length
 * Problem: https://www.acmicpc.net/problem/25111
 * Code: http://boj.kr/0e3cbcb75ff647d2a6903e544605e589
 */

// return O(n log n) tuple {l, r, p} that
// [i, i+p) = [i+p, i+2p) for all l <= i < r
vector<tuple<int,int,int>> TandemRepeat(const string &s){
  int n = s.size(); vector<tuple<int,int,int>> res;
  string t = s; reverse(t.begin(), t.end());
  // WARNING: add empty suffix!!
  // sa.insert(sa.begin(), n) before calculate lcp/pos
  auto [sa_s,lcp_s,pos_s] = SuffixArray(s);
  auto [sa_t,lcp_t,pos_t] = SuffixArray(t);
  RMQ<int> rmq_s(lcp_s), rmq_t(lcp_t);
  auto get = [n](const vector<int> &pos, const RMQ<int> &rmq, int a, int b){
    if(pos[a] > pos[b]) swap(a, b);
    return a == b ? n - a : rmq.query(pos[a] + 1, pos[b]);
  };
  for(int p=1; p*2<=n; p++){
    for(int i=0, j=-1; i+p<=n; i+=p){
      int l = i - get(pos_t, rmq_t, n-i-p, n-i);
      int r = i - p + get(pos_s, rmq_s, i, i+p);
      if(l <= r && l != j) res.emplace_back(j=l, r+1, p);
  }} return res;
} // Check p = 0, time complexity O(n log n)