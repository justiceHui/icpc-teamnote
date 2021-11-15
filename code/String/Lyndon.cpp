// factorize string into w1 >= w2 >= ... >= wk, wi is smallest cyclic shift of suffix.
vector<string> Lyndon(const string &s){ // O(N)
  int n = s.size(), i = 0, j, k;
  vector<string> res;
  while(i < n){
    for(j=i+1, k=i; i<n && s[k]<=s[j]; j++) k = s[k] < s[j] ? i : k + 1;
    for(; i<=k; i+=j-k) res.push_back(s.substr(i, j-k));
  }
  return res;
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