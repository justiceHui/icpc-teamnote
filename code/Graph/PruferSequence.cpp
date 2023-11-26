vector<pair<int,int>> Gen(int n, vector<int> a){ // a : [1,n]^(n-2)
  if(n == 1) return {}; if(n == 2) return { make_pair(1, 2) };
  vector<int> deg(n+1); for(auto i : a) deg[i]++;
  vector<pair<int,int>> res; priority_queue<int> pq;
  for(int i=n; i; i--) if(!deg[i]) pq.emplace(i);
  for(auto i : a){
    res.emplace_back(i, pq.top()); pq.pop();
    if(!--deg[i]) pq.push(i);
  }int u = pq.top(); pq.pop(); int v = pq.top(); pq.pop();
  res.emplace_back(u, v); return res;
}