struct Node{
  Node *l, *r, *p;
  bool flip; int sz;
  T now, sum, lz;
  Node(){ l = r = p = nullptr; sz = 1; flip = false; now = sum = lz = 0; }
  bool IsLeft() const { return p && this == p->l; }
  bool IsRoot() const { return !p || (this != p->l && this != p->r); }
  friend int GetSize(const Node *x){ return x ? x->sz : 0; }
  friend T GetSum(const Node *x){ return x ? x->sum : 0; }
  void Rotate(){
    p->Push(); Push();
    if(IsLeft()) r && (r->p = p), p->l = r, r = p;
    else l && (l->p = p), p->r = l, l = p;
    if(!p->IsRoot()) (p->IsLeft() ? p->p->l : p->p->r) = this;
    auto t = p; p = t->p; t->p = this; t->Update(); Update();
  }
  void Update(){
    sz = 1 + GetSize(l) + GetSize(r); sum = now + GetSum(l) + GetSum(r);
  }
  void Update(const T &val){ now = val; Update(); }
  void Push(){
    Update(now + lz); if(flip) swap(l, r);
    for(auto c : {l, r}) if(c) c->flip ^= flip, c->lz += lz;
    lz = 0; flip = false;
  }
};
Node* rt;
Node* Splay(Node *x, Node *g=nullptr){
  for(g || (rt=x); x->p!=g; x->Rotate()){
    if(!x->p->IsRoot()) x->p->p->Push(); x->p->Push(); x->Push();
    if(x->p->p != g) (x->IsLeft() ^ x->p->IsLeft() ? x : x->p)->Rotate();
  }
  x->Push(); return x;
}
Node* Kth(int k){
  for(auto x=rt; ; x=x->r){
    for(; x->Push(), x->l && x->l->sz > k; x=x->l);
    if(x->l) k -= x->l->sz;
    if(!k--) return Splay(x);
  }
}
Node* Gather(int s, int e){ auto t = Kth(e+1); return Splay(t, Kth(s-1))->l; }
Node* Flip(int s, int e){ auto x = Gather(s, e); x->flip ^= 1; return x; }
Node* Shift(int s, int e, int k){
  if(k >= 0){
    k %= e-s+1; if(k) Flip(s, e), Flip(s, s+k-1), Flip(s+k, e);
  }
  else{
    k = -k; k %= e-s+1; if(k) Flip(s, e), Flip(s, e-k), Flip(e-k+1, e);
  }
  return Gather(s, e);
}
int Idx(Node *x){ return x->l->sz; }
//////////// Link Cut Tree Start ////////////
Node* Splay(Node *x){
  for(; !x->IsRoot(); x->Rotate()){
    if(!x->p->IsRoot()) x->p->p->Push(); x->p->Push(); x->Push();
    if(!x->p->IsRoot()) (x->IsLeft() ^ x->p->IsLeft() ? x : x->p)->Rotate();
  }
  x->Push(); return x;
}
void Access(Node *x){
  Splay(x); x->r = nullptr; x->Update();
  for(auto y=x; x->p; Splay(x)) y = x->p, Splay(y), y->r = x, y->Update();
}
int GetDepth(Node *x){ Access(x); x->Push(); return GetSize(x->l); }
Node* GetRoot(Node *x){
  Access(x); for(x->Push(); x->l; x->Push()) x = x->l; return Splay(x);
}
Node* GetPar(Node *x){
  Access(x); x->Push(); if(!x->l) return nullptr;
  x = x->l; for(x->Push(); x->r; x->Push()) x = x->r;
  return Splay(x);
}
void Link(Node *p, Node *c){ Access(c); Access(p); c->l = p; p->p = c; c->Update(); }
void Cut(Node *c){ Access(c); c->l->p = nullptr; c->l = nullptr; c->Update(); }
Node* GetLCA(Node *x, Node *y){
  Access(x); Access(y); Splay(x); return x->p ? x->p : x;
}
Node* Ancestor(Node *x, int k){
  k = GetDepth(x) - k; assert(k >= 0);
  for(;;x->Push()){
    int s = GetSize(x->l); if(s == k) return Access(x), x;
    if(s < k) k -= s + 1, x = x->r; else x = x->l;
  }
}
void MakeRoot(Node *x){ Access(x); Splay(x); x->flip ^= 1; }
bool IsConnect(Node *x, Node *y){ return GetRoot(x) == GetRoot(y); }
void PathUpdate(Node *x, Node *y, T val){
  Node *root = GetRoot(x); // original root
  MakeRoot(x); Access(y);  // make x to root, tie with y
  Splay(x); x->lz += val; x->Push();
  MakeRoot(root);    // Revert
  Node *lca = GetLCA(x, y);
  Access(lca); Splay(lca); lca->Push();
  lca->Update(lca->now - val);
}
T VertexQuery(Node *x, Node *y){
  Node *l = GetLCA(x, y); T ret = l->now;
  Access(x); Splay(l); if(l->r) ret = ret + l->r->sum;
  Access(y); Splay(l); if(l->r) ret = ret + l->r->sum;
  return ret;
}
Node* GetQueryResultNode(Node *u, Node *v){
  if(GetRoot(u) != GetRoot(v)) return 0;
  MakeRoot(u); Access(v); auto ret = v->l;
  while(ret->mx != ret->v){
    if (ret->l && ret->mx == ret->l->mx) ret = ret->l;
    else ret = ret->r;
  }
  Access(ret); return ret;
}