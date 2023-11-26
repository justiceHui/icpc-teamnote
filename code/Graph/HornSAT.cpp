/* n : numer of variance
{}, 0 : x1 | {0, 1}, 2 : (x1 and x2) => x3, (-x1 or -x2 or x3)
fail -> empty vector */
vector<int> HornSAT(int n, const vector<vector<int>> &cond, const vector<int> &val){
  int m = cond.size(); vector<int> res(n), margin(m), stk;
  vector<vector<int>> gph(n);
  for(int i=0; i<m; i++){
    margin[i] = cond[i].size();
    if(cond[i].empty()) stk.push_back(i);
    for(auto j : cond[i]) gph[j].push_back(i);
  }
  while(!stk.empty()){
    int v = stk.back(), h = val[v]; stk.pop_back();
    if(h < 0) return vector<int>();
    if(res[h]) continue; res[h] = 1;
    for(auto i : gph[h]) if(!--margin[i]) stk.push_back(i);
  } return res;
}