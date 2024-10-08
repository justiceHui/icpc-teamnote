//0-based, S-T cut in graph=S-T cut in gomory-hu tree (path min)
vector<Edge> GomoryHuTree(int n, const vector<Edge> &e){
  Dinic<int,100> Flow; vector<Edge> res(n-1); vector<int> pr(n);
  for(int i=1; i<n; i++, Flow.clear()){ // // bi-directed edge
    for(const auto &[s,e,x] : e) Flow.AddEdge(s, e, x);
    int fl = Flow.MaxFlow(pr[i], i);
    for(int j=i+1; j<n; j++){
      if(!Flow.Level[i] == !Flow.Level[j] && pr[i] == pr[j]) pr[j] = i;
    } /*for-j end*/ res[i-1] = Edge(pr[i], i, fl);
  } /*for-i end*/ return res; }