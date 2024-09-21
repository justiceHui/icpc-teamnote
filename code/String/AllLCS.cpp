/**
 * Author: 
 * License: 
 * Source: https://github.com/abc864197532/std_abs/blob/main/codebook/Else/All_LCS.cpp
 * Description: get LCS(A[0..i], B[l..r]) in O(N^2)
 * Problem: https://www.acmicpc.net/problem/25954
 * Code: http://boj.kr/9368303a74fb42c4bcee722250822216
 */

void AllLCS(const string &s, const string &t){
  vector<int> h(t.size()); iota(h.begin(), h.end(), 0);
  for(int i=0, v=-1; i<s.size(); i++, v=-1){
    for(int r=0; r<t.size(); r++){
      if(s[i] == t[r] || h[r] < v) swap(h[r], v);
      //LCS(s[0..i],t[l..r]) = r-l+1 - sum([h[x] >= l] | x <= r)
} /*for r*/ } /* for i */ } /* end*/