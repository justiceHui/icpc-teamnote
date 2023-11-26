/**
 * Author: JusticeHui
 * License: CC BY-NC-SA
 * Source: JusticeHui
 * Description: 
 * Problem: https://judge.yosupo.jp/problem/lyndon_factorization
 * Code: https://judge.yosupo.jp/submission/173673
 */

// link[i]: length of smallest suffix of s[0..i-1]
// factorization result: s[res[i]..res[i+1]-1]
vector<int> Lyndon(const string &s){
  int n = s.size(); vector<int> link(n);
  for(int i=0; i<n; ){
    int j=i+1, k=i; link[i] = 1;
    for(; j<n && s[k]<=s[j]; j++){
      if(s[j] == s[k]) link[j] = link[k], k++;
      else link[j] = j - i + 1, k = i;
    } for(; i<=k; i+=j-k);
  } vector<int> res;
  for(int i=n-1; i>=0; i-=link[i]) res.push_back(i-link[i]+1);
  reverse(res.begin(), res.end()); return res;
}
// rotate(v.begin(), v.begin()+min_rotation(v), v.end());
template<typename T> int min_rotation(T s){ // O(N)
  int a = 0, N = s.size();
  for(int i=0; i<N; i++) s.push_back(s[i]);
  for(int b=0; b<N; b++) for(int k=0; k<N; k++){
    if(a+k == b || s[a+k] < s[b+k]){ b += max(0, k-1); break; }
    if(s[a+k] > s[b+k]){ a = b; break; }
  }
  return a;
}