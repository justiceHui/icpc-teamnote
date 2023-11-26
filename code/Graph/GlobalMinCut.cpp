/**
 * Author: Stanford
 * License: 
 * Source: Stanford Notebook, http://www.cs.tau.ac.il/~zwick/grad-algo-08/gmc.pdf
 * Secondary source: https://github.com/ecnerwala/icpc-book/blob/master/content/graph/GlobalMinCut.h
 * Problem: https://www.acmicpc.net/problem/13367
 * Code: http://boj.kr/e525158ce39a4e22b3b985bad986cb56
 */

template<typename T, T INF>// 0-based, adj matrix
pair<T, vector<int>> GetMinCut(vector<vector<T>> g){
  int n=g.size(); vector<int> use(n), cut, mn_cut; T mn=INF;
  for(int phase=n-1; phase>=0; phase--){
    vector<int> w=g[0], add=use; int k=0, prv;
    for(int i=0; i<phase; i++){ prv = k; k = -1;
      for(int j=1; j<n; j++) if(!add[j] && (k==-1 || w[j] > w[k])) k=j;
      if(i + 1 < phase){
        for(int j=0; j<n; j++) w[j] += g[k][j];
        add[k] = 1; continue; }
      for(int j=0; j<n; j++) g[prv][j] += g[k][j];
      for(int j=0; j<n; j++) g[j][prv] = g[prv][j];
      use[k] = 1; cut.push_back(k);
      if(w[k] < mn) mn_cut = cut, mn = w[k];
    }
  } return {mn, mn_cut};
}