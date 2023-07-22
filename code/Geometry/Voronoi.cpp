/*
input: order will be changed, sorted by (y,x) order
vertex: voronoi intersection points, degree 3, may duplicated
edge: may contain inf line (-1)
area
  - (a,b) = i-th element of area
  - (u,v) = i-th element of edge
  - input[a] is located CCW of u->v line
  - input[b] is located CW of u->v line
  - u->v line is a subset of perpendicular bisector of input[a] to input[b] segment
  - Straight line {a, b}, {-1, -1} through midpoint of input[a] and input[b]
*/
const double EPS = 1e-9;
int dcmp(double x){ return x < -EPS? -1 : x > EPS ? 1 : 0; }
// sq(x) = x*x, size(p) = hypot(p.x, p.y)
// sz2(p) = sq(p.x)+sq(p.y), r90(p) = (-p.y, p.x)
double sq(double x){ return x*x; }
double size(pdd p){ return hypot(p.x, p.y); }
double sz2(pdd p){ return sq(p.x) + sq(p.y); }
pdd r90(pdd p){ return pdd(-p.y, p.x); }
pdd line_intersect(pdd a, pdd b, pdd u, pdd v){ return u + (((a-u)/b) / (v/b))*v; }
pdd get_circumcenter(pdd p0, pdd p1, pdd p2){
  return line_intersect(0.5 * (p0+p1), r90(p0-p1), 0.5 * (p1+p2), r90(p1-p2)); }
double pb_int(pdd left, pdd right, double sweepline){
  if(dcmp(left.y - right.y) == 0) return (left.x + right.x) / 2.0;
  int sign = left.y < right.y ? -1 : 1;
  pdd v = line_intersect(left, right-left, pdd(0, sweepline), pdd(1, 0));
  double d1 = sz2(0.5 * (left+right) - v), d2 = sz2(0.5 * (left-right));
  return v.x + sign * sqrt(std::max(0.0, d1 - d2)); }
struct Beachline{
  struct node{ node(){}
    node(pdd point, int idx):point(point), idx(idx), end(0), link{0, 0}, par(0), prv(0), nxt(0) {}
    pdd point; int idx; int end;
    node *link[2], *par, *prv, *nxt; };
  node *root;
  double sweepline;
  Beachline() : sweepline(-1e20), root(NULL){ }
  inline int dir(node *x){ return x->par->link[0] != x; }
  void rotate(node *n){
    node *p = n->par; int d = dir(n);
    p->link[d] = n->link[!d];
    if(n->link[!d]) n->link[!d]->par = p;
    n->par = p->par; if(p->par) p->par->link[dir(p)] = n;
    n->link[!d] = p; p->par = n;
  } void splay(node *x, node *f = NULL){
    while(x->par != f){
      if(x->par->par == f);
      else if(dir(x) == dir(x->par)) rotate(x->par);
      else rotate(x);
      rotate(x); }
    if(f == NULL) root = x;
  } void insert(node *n, node *p, int d){
    splay(p); node* c = p->link[d];
    n->link[d] = c; if(c) c->par = n;
    p->link[d] = n; n->par = p;
    node *prv = !d?p->prv:p, *nxt = !d?p:p->nxt;
    n->prv = prv;   if(prv) prv->nxt = n;
    n->nxt = nxt;   if(nxt) nxt->prv = n;
  } void erase(node* n){
    node *prv = n->prv, *nxt = n->nxt;
    if(!prv && !nxt){ if(n == root) root = NULL; return; }
    n->prv = NULL; if(prv) prv->nxt = nxt;
    n->nxt = NULL; if(nxt) nxt->prv = prv;
    splay(n);
    if(!nxt){
      root->par = NULL; n->link[0] = NULL;
      root = prv; }
    else{
      splay(nxt, n);   node* c = n->link[0];
      nxt->link[0] = c;  c->par = nxt;     n->link[0] = NULL;
      n->link[1] = NULL; nxt->par = NULL;
      root = nxt; }
  } bool get_event(node* cur, double &next_sweep){
    if(!cur->prv || !cur->nxt) return false;
    pdd u = r90(cur->point - cur->prv->point);
    pdd v = r90(cur->nxt->point - cur->point);
    if(dcmp(u/v) != 1) return false;
    pdd p = get_circumcenter(cur->point, cur->prv->point, cur->nxt->point);
    next_sweep = p.y + size(p - cur->point); return true;
  } node* find_bl(double x){
    node* cur = root;
    while(cur){
      double left = cur->prv ? pb_int(cur->prv->point, cur->point, sweepline) : -1e30;
      double right = cur->nxt ? pb_int(cur->point, cur->nxt->point, sweepline) : 1e30;
      if(left <= x && x <= right){ splay(cur); return cur; }
      cur = cur->link[x > right]; }
  }
}; using BNode = Beachline::node;
static BNode* arr;
static int sz;
static BNode* new_node(pdd point, int idx){
  arr[sz] = BNode(point, idx); return arr + (sz++); }
struct event{
  event(double sweep, int idx):type(0), sweep(sweep), idx(idx){}
  event(double sweep, BNode* cur):type(1), sweep(sweep), prv(cur->prv->idx), cur(cur), nxt(cur->nxt->idx){}
  int type, idx, prv, nxt; BNode* cur; double sweep;
  bool operator>(const event &l)const{ return sweep > l.sweep; }
};
void VoronoiDiagram(vector<pdd> &input, vector<pdd> &vertex, vector<pii> &edge, vector<pii> &area){
  Beachline bl = Beachline();
  priority_queue<event, vector<event>, greater<event>> events;
  auto add_edge = [&](int u, int v, int a, int b, BNode* c1, BNode* c2){
    if(c1) c1->end = edge.size()*2;
    if(c2) c2->end = edge.size()*2 + 1;
    edge.emplace_back(u, v);
    area.emplace_back(a, b);
  };
  auto write_edge = [&](int idx, int v){ idx%2 == 0 ? edge[idx/2].x = v : edge[idx/2].y = v; };
  auto add_event = [&](BNode* cur){ double nxt; if(bl.get_event(cur, nxt)) events.emplace(nxt, cur); };
  int n = input.size(), cnt = 0;
  arr = new BNode[n*4]; sz = 0;
  sort(input.begin(), input.end(), [](const pdd &l, const pdd &r){
    return l.y != r.y ? l.y < r.y : l.x < r.x; });
  BNode* tmp = bl.root = new_node(input[0], 0), *t2;
  for(int i = 1; i < n; i++){
    if(dcmp(input[i].y - input[0].y) == 0){
      add_edge(-1, -1, i-1, i, 0, tmp);
      bl.insert(t2 = new_node(input[i], i), tmp, 1);
      tmp = t2;
    }
    else events.emplace(input[i].y, i);
  }
  while(events.size()){
    event q = events.top(); events.pop();
    BNode *prv, *cur, *nxt, *site;
    int v = vertex.size(), idx = q.idx;
    bl.sweepline = q.sweep;
    if(q.type == 0){
      pdd point = input[idx];
      cur = bl.find_bl(point.x);
      bl.insert(site = new_node(point, idx), cur, 0);
      bl.insert(prv = new_node(cur->point, cur->idx), site, 0);
      add_edge(-1, -1, cur->idx, idx, site, prv);
      add_event(prv); add_event(cur);
    }
    else{
      cur = q.cur, prv = cur->prv, nxt = cur->nxt;
      if(!prv || !nxt || prv->idx != q.prv || nxt->idx != q.nxt) continue;
      vertex.push_back(get_circumcenter(prv->point, nxt->point, cur->point));
      write_edge(prv->end, v); write_edge(cur->end, v);
      add_edge(v, -1, prv->idx, nxt->idx, 0, prv);
      bl.erase(cur);
      add_event(prv); add_event(nxt);
    }
  }
  delete arr;
}