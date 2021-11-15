inline int True(int x){ return x << 1; }
inline int False(int x){ return x << 1 | 1; }
inline int Inv(int x){ return x ^ 1; }
struct TwoSat{
  int n;
  vector<vector<int>> g;
  vector<int> result;
  TwoSat(int n, int m = 0) : n(n), g(n+n) { if(!m) g.reserve(m+m); }
  int addVar(){ g.emplace_back(); g.emplace_back(); return n++; }
  void addEdge(int s, int e){ g[s].push_back(e); }
  void addCNF(int a, int b){ addEdge(Inv(a), b); addEdge(Inv(b), a); } // (A or B)
  void setValue(int x){ addCNF(x, x); } // (A or A)
  void addAlwaysTrue(int a, int b){ addEdge(a, b); addEdge(Inv(b), Inv(a)); } // A => B
  void addMostOne(const vector<int> &li){
    if(li.empty()) return; int t;
    for(int i=0; i<li.size(); i++){
      t = addVar();
      addAlwaysTrue(li[i], True(t));
      if(!i) continue;
      addAlwaysTrue(True(t-1), True(t));
      addAlwaysTrue(True(t-1), Inv(li[i]));
    }
  }
  void addExactlyOne(const vector<int> &li){
    if(li.empty()) return; int t;
    for(int i=0; i<li.size(); i++){
      t = addVar();
      addAlwaysTrue(li[i], True(t));
      if(!i) continue;
      addAlwaysTrue(True(t-1), True(t));
      addAlwaysTrue(True(t-1), Inv(li[i]));
    }
    setValue(True(t));
  }
  vector<int> val, comp, z; int pv = 0;
  int dfs(int i){
    int low = val[i] = ++pv, x; z.push_back(i);
    for(int e : g[i]) if(!comp[e]) low = min(low, val[e] ?: dfs(e));
    if(low == val[i]){
      do{
        x = z.back(); z.pop_back();
        comp[x] = low;
        if (result[x>>1] == -1) result[x>>1] = ~x&1;
      }while(x != i);
    }
    return val[i] = low;
  }
  bool sat(){
    result.assign(n, -1);
    val.assign(2*n, 0); comp = val;
    for(int i=0; i<n+n; i++) if(!comp[i]) dfs(i);
    for(int i=0; i<n; i++) if(comp[2*i] == comp[2*i+1]) return 0;
    return 1;
  }
  vector<int> getValue(){ return move(result); }
};