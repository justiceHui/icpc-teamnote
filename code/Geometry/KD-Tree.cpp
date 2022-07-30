T GetDist(const P &a, const P &b){ return (a.x-b.x) * (a.x-b.x) + (a.y-b.y) * (a.y-b.y); }
struct Node{
  P p; int idx;
  T x1, y1, x2, y2;
  Node(const P &p, const int idx) : p(p), idx(idx), x1(1e9), y1(1e9), x2(-1e9), y2(-1e9) {}
  bool contain(const P &pt)const{ return x1 <= pt.x && pt.x <= x2 && y1 <= pt.y && pt.y <= y2; }
  T dist(const P &pt) const { return idx == -1 ? INF : GetDist(p, pt); }
  T dist_to_border(const P &pt) const {
    const auto [x,y] = pt;
    if(x1 <= x && x <= x2) return min((y-y1)*(y-y1), (y2-y)*(y2-y));
    if(y1 <= y && y <= y2) return min((x-x1)*(x-x1), (x2-x)*(x2-x));
    T t11 = GetDist(pt, {x1,y1}), t12 = GetDist(pt, {x1,y2});
    T t21 = GetDist(pt, {x2,y1}), t22 = GetDist(pt, {x2,y2});
    return min({t11, t12, t21, t22});
  }
};
template<bool IsFirst = 1> struct Cmp {
  bool operator() (const Node &a, const Node &b) const {
    return IsFirst ? a.p.x < b.p.x : a.p.y < b.p.y;
  }
};
struct KDTree { // Warning : no duplicate
  constexpr static size_t NAIVE_THRESHOLD = 16;
  vector<Node> tree;
  KDTree() = default;
  explicit KDTree(const vector<P> &v) {
    for(int i=0; i<v.size(); i++) tree.emplace_back(v[i], i); Build(0, v.size());
  }
  template<bool IsFirst = 1>
  void Build(int l, int r) {
    if(r - l <= NAIVE_THRESHOLD) return;
    const int m = (l + r) >> 1;
    nth_element(tree.begin()+l, tree.begin()+m, tree.begin()+r, Cmp<IsFirst>{});
    for(int i=l; i<r; i++){
      tree[m].x1 = min(tree[m].x1, tree[i].p.x); tree[m].y1 = min(tree[m].y1, tree[i].p.y);
      tree[m].x2 = max(tree[m].x2, tree[i].p.x); tree[m].y2 = max(tree[m].y2, tree[i].p.y);
    }
    Build<!IsFirst>(l, m); Build<!IsFirst>(m + 1, r);
  }
  template<bool IsFirst = 1>
  void Query(const P &p, int l, int r, Node &res) const {
    if(r - l <= NAIVE_THRESHOLD){
      for(int i=l; i<r; i++) if(p != tree[i].p && res.dist(p) > tree[i].dist(p)) res = tree[i];
    }
    else{
      const int m = (l + r) >> 1;
      const T t = IsFirst ? p.x - tree[m].p.x : p.y - tree[m].p.y;
      if(p != tree[m].p && res.dist(p) > tree[m].dist(p)) res = tree[m];
      if(!tree[m].contain(p) && tree[m].dist_to_border(p) >= res.dist(p)) return;
      if(t < 0){
        Query<!IsFirst>(p, l, m, res);
        if(t*t < res.dist(p)) Query<!IsFirst>(p, m+1, r, res);
      }
      else{
        Query<!IsFirst>(p, m+1, r, res);
        if(t*t < res.dist(p)) Query<!IsFirst>(p, l, m, res);
      }
    }
  }
  int Query(const P& p) const {
    Node ret(make_pair<T>(1e9, 1e9), -1); Query(p, 0, tree.size(), ret); return ret.idx;
  }
};