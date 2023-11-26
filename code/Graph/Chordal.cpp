struct Set { list<int> L; int last; Set() { last = 0; } };
struct PEO {
  int N; list<Set> L;
  vector<vector<int>> g; vector<int> vis, res;
  vector<list<Set>::iterator> ptr;
  vector<list<int>::iterator> ptr2;
  PEO(int n, vector<vector<int> > _g) {
    N = n; g = _g;
    for (int i = 1; i <= N; i++) sort(g[i].begin(), g[i].end());
    vis.resize(N + 1); ptr.resize(N + 1); ptr2.resize(N + 1);
    L.push_back(Set());
    for (int i = 1; i <= N; i++) {
      L.back().L.push_back(i);
      ptr[i] = L.begin(); ptr2[i] = prev(L.back().L.end());
    }
  }
  pair<bool, vector<int>> Run() {
    // lexicographic BFS
    int time = 0;
    while (!L.empty()) {
      if (L.front().L.empty()) { L.pop_front(); continue; }
      auto it = L.begin();
      int n = it->L.front(); it->L.pop_front();
      vis[n] = ++time;
      res.push_back(n);
      for (int next : g[n]) {
        if (vis[next]) continue;
        if (ptr[next]->last != time) {
          L.insert(ptr[next], Set()); ptr[next]->last = time;
        }
        ptr[next]->L.erase(ptr2[next]); ptr[next]--;
        ptr[next]->L.push_back(next);
        ptr2[next] = prev(ptr[next]->L.end());
      }
    }
    // PEO existence check
    for (int n = 1; n <= N; n++) {
      int mx = 0;
      for (int next : g[n]) if (vis[n] > vis[next]) mx = max(mx, vis[next]);
      if (mx == 0) continue;
      int w = res[mx - 1];
      for (int next : g[n]) {
        if (vis[w] > vis[next] && !binary_search(g[w].begin(), g[w].end(), next)){
          vector<int> chk(N+1), par(N+1, -1); // w와 next가 이어져 있지 않다면 not chordal
          deque<int> dq{next}; chk[next] = 1;
          while (!dq.empty()) {
            int x = dq.front(); dq.pop_front();
            for (auto y : g[x]) {
              if (chk[y] || y == n || y != w && binary_search(g[n].begin(), g[n].end(), y)) continue;
              dq.push_back(y); chk[y] = 1; par[y] = x;
            }
          }
          vector<int> cycle{next, n};
          for (int x=w; x!=next; x=par[x]) cycle.push_back(x);
          return {false, cycle};
        }
      }
    }
    reverse(res.begin(), res.end());
    return {true, res};
  }
};
bool vis[200201]; // 배열 크기 알아서 수정하자.
int p[200201], ord[200201], P = 0; // P=정점 개수
vector<int> V[200201], G[200201]; // V=bags, G=edges
void tree_decomposition(int N, vector<vector<int> > g) {
  for(int i=1; i<=N; i++) sort(g[i].begin(), g[i].end());
  vector<int> peo = PEO(N, g).Run(), rpeo = peo;
  reverse(rpeo.begin(), rpeo.end());
  for(int i=0; i<peo.size(); i++) ord[peo[i]] = i;
  for(int n : rpeo) { // tree decomposition
    vis[n] = true;
    if (n == rpeo[0]) { // 처음
      P++; V[P].push_back(n); p[n] = P; continue;
    }
    int mn = INF, idx = -1;
    for(int next : g[n]) if (vis[next] && mn > ord[next]) mn = ord[next], idx = next;
    assert(idx != -1); idx = p[idx];
    // 두 set인 V[idx]와 g[n](visited ver)가 같나?
    // V[idx]의 모든 원소가 g[n]에서 나타나는지 판별로 충분하다.
    int die = 0;
    for(int x : V[idx]) {
      if (!binary_search(g[n].begin(), g[n].end(), x)) { die = 1; break; }
    }
    if (!die) { V[idx].push_back(n), p[n] = idx; } // 기존 집합에 추가
    else { // 새로운 집합을 자식으로 추가
      P++;
      G[idx].push_back(P); // 자식으로만 단방향으로 잇자.
      V[P].push_back(n);
      for(int next : g[n]) if (vis[next]) V[P].push_back(next);
      p[n] = P;
    }
  }
  for(int i=1; i<=P; i++) sort(V[i].begin(), V[i].end());
}