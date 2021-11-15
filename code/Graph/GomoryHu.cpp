// 0-based, S-T cut in graph == S-T cut in gomory-hu tree (path minimum)
vector<Edge> GomoryHuTree(int n, const vector<Edge> &e){
    Dinic<int,100> Flow;
    vector<Edge> res(n-1); vector<int> pr(n);
    for(int i=1; i<n; i++, Flow.clear()){
        for(const auto &[s,e,x] : e) Flow.AddEdge(s, e, x); // bi-directed
        int fl = Flow.MaxFlow(pr[i], i);
        for(int j=i+1; j<n; j++){
            if(!Flow.Level[i] == !Flow.Level[j] && pr[i] == pr[j]) pr[j] = i;
        }
        res[i-1] = Edge(pr[i], i, fl);
    }
    return res;
}