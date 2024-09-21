struct Node{
  int g[26], fail, out;
  Node() { memset(g, 0, sizeof g); fail = out = 0; }
};
vector<Node> T(2); int aut[100101][26];
void Insert(int n, int i, const string &s){
  if(i == s.size()){ T[n].out++; return; }
  int c = s[i] - 'a';
  if(T[n].g[c] == 0) T[n].g[c] = T.size(), T.emplace_back();
  Insert(T[n].g[c], i+1, s);
}
int go(int n, int i){ // DO NOT USE `aut` DIRECTLY
  int &res = aut[n][i]; if(res) return res;
  if(n != 1 && T[n].g[i] == 0) res = go(T[n].fail, i);
  else if(T[n].g[i] != 0) res = T[n].g[i]; else res = 1;
  return res;
}
void Build(){
  queue<int> q; q.push(1); T[1].fail = 1;
  while(!q.empty()){
    int n = q.front(); q.pop();
    for(int i=0; i<26; i++){
      int next = T[n].g[i]; if(next == 0) continue;
     if(n == 1)T[next].fail=1;else T[next].fail=go(T[n].fail,i);
      q.push(next); T[next].out += T[T[next].fail].out;
    } /* for i */ } /* while q */ } /* build */
bool Find(const string &s){
  int n = 1, ok = 0;
  for(int i=0; i<s.size(); i++){
    n = go(n, s[i] - 'a'); if(T[n].out != 0) ok = 1;
  } return ok;
}