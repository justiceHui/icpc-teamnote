// man : 1~n, woman : n+1~2n
struct StableMarriage{
  int n;
  vector<vector<int>> g;
  StableMarriage(int n) : n(n), g(2*n+1) {
    for(int i=1; i<=n+n; i++) g[i].reserve(n);
  }
  void addEdge(int u, int v){ // insert in decreasing order of preference.
    g[u].push_back(v);
  }
  vector<int> run(){
    queue<int> q;
    vector<int> match(2*n+1), ptr(2*n+1);
    for(int i=1; i<=n; i++) q.push(i);
    while(q.size()){
      int i = q.front(); q.pop();
      for(int &p=ptr[i]; p<g[i].size(); p++){
        int j = g[i][p];
        if(!match[j]){ match[i] = j; match[j] = i; break; }
        int m = match[j], u = -1, v = -1;
        for(int k=0; k<g[j].size(); k++){
          if(g[j][k] == i) u = k;
          if(g[j][k] == m) v = k;
        }
        if(u < v){
          match[m] = 0; q.push(m);
          match[i] = j; match[j] = i;
          break;
        }
      }
    }
    return match;
  }
};