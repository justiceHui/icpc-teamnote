// O(N*maxW), maximize sumW <= t
int Knapsack(vector<int> w, int t){
  int a = 0, b = 0, x;
  while(b < w.size() && a + w[b] <= t) a += w[b++];
  if(b == w.size()) return a;
  int m = *max_element(w.begin(), w.end());
  vector<int> u, v(2*m, -1); v[a+m-t] = b;
  for(int i=b; (u=v,i<w.size()); i++){
    for(x=0; x<m; x++) v[x+w[i]] = max(v[x+w[i]], u[x]);
    for(x=2*m; --x>m; ) for(int j=max(0,u[x]); j<v[x]; j++) v[x-w[j]] = max(v[x-w[j]], j);
  } for(a=t; v[a+m-t]<0; a--);;; return a;
}