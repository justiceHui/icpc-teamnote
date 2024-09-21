int SZ; vector<vector<int>> G1, G2;
void Init(int n){ SZ = n; G1 = G2 = vector<vector<int>>(SZ*2); }
int New(){
  for(int i=0;i<2;i++) G1.emplace_back(), G2.emplace_back();
  return SZ++; }
void AddEdge(int s, int e){ G1[s].push_back(e); G2[e].push_back(s); }
// T(x) = x << 1, F(x) = x << 1 | 1, I(x) = x ^ 1
void AddCNF(int a, int b){ AddEdge(I(a), b); AddEdge(I(b), a); }
void MostOne(vector<int> vec){ compress(vec);
  for(int i=0; i<vec.size(); i++){
    int now = New();
    AddEdge(vec[i], T(now)); AddEdge(F(now), I(vec[i]));
    if(i == 0) continue;
    AddEdge(T(now-1), T(now)); AddEdge(F(now), F(now-1));
    AddEdge(T(now-1), I(vec[i])); AddEdge(vec[i], F(now-1));
  }
}