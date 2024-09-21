vector<int> getFail(const container &pat){
  vector<int> fail(pat.size());
//match: pat[0..j] and pat[j-i..i] is equivalent
//ins/del: manipulate corresponding range to pattern starts at 0
//        (insert/delete pat[i], manage pat[j-i..i])
  function<bool(int, int)> match = [&](int i, int j){ };
  function<void(int)> ins = [&](int i){ };
  function<void(int)> del = [&](int i){ };
  for(int i=1, j=0; i<pat.size(); i++){
    while(j && !match(i, j)){
      for(int s=i-j; s<i-fail[j-1]; s++) del(s);
      j = fail[j-1]; }
    if(match(i, j)) ins(i), fail[i] = ++j;
  } return fail;
}
vector<int> doKMP(const container &str, const container &pat){
  vector<int> ret, fail = getFail(pat);
//match: pat[0..j] and str[j-i..i] is equivalent
//ins/del: manipulate corresponding range to pattern starts at 0
//         (insert/delete str[i], manage str[j-i..i])
  function<bool(int, int)> match = [&](int i, int j){ };
  function<void(int)> ins = [&](int i){ };
  function<void(int)> del = [&](int i){ };
  for(int i=0, j=0, s; i<str.size(); i++){
    while(j && !match(i, j)){
      for(int s=i-j; s<i-fail[j-1]; s++) del(s);
      j = fail[j-1]; }
    if(match(i, j)){
      if(j+1 == pat.size()){
        ret.push_back(i-j); for(s=i-j;s<i-fail[j]+1; s++)del(s);
        j = fail[j];
      } else ++j;      ins(i);
    } } return ret;
}
// # a # b # a # a # b # a #
// 0 1 0 3 0 1 6 1 0 3 0 1 0
vector<int> Manacher(const string &inp){
  string s = "#"; for(auto c : inp) s += c, s += "#";
  int n = s.size(); vector<int> p(n);
  vector<pair<int,int>> range, maximal;
  auto make = [&](int l, int r) { return make_pair(l/2, (r-1)/2); };
  for(int i=0, k=-1, r=-1; i<n; i++){
    if(i <= r) p[i] = min(r-i, p[2*k-i]);
    while(i-p[i]-1 >= 0 && i+p[i]+1<n && s[i-p[i]-1] == s[i+p[i]+1]){
      p[i]++; range.push_back(make(i-p[i], i+p[i]));
    } if(i+p[i] > r) r = i+p[i], k = i;
    if(p[i] != 0) maximal.push_back(make(i-p[i], i+p[i]));
  } // compress(range), range can contains O(1) dup. substr...
  return p; } // range: distinct palindrome(<= n)
//z[i]=match length of s[0,n-1] and s[i,n-1]
vector<int> Z(const string &s){
  int n = s.size(); vector<int> z(n); z[0] = n;
  for(int i=1, l=0, r=0; i<n; i++){
    if(i < r) z[i] = min(r-i-1, z[i-l]);
    while(i+z[i] < n && s[i+z[i]] == s[z[i]]) z[i]++;
    if(i+z[i] > r) r = i+z[i], l = i;
  } return z;
}