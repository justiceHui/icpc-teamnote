/**
 * Author: JusticeHui
 * License: CC BY-NC-SA 
 * Problem: https://www.acmicpc.net/problem/7469
 * Code: http://boj.kr/93b3f0f0700c411eb5a29b99c00c4921
 */

struct PSTNode{ // call init(root[0], s, e) before use
  PSTNode *l, *r; int v; PSTNode(){ l = r = nullptr; v = 0; }
}; PSTNode *root[101010];
PST(){ memset(root, 0, sizeof root); } // constructor
void init(PSTNode *node, int s, int e){
  if(s == e) return; int m = s + e >> 1;
  node->l = new PSTNode; node->r = new PSTNode;
  init(node->l, s, m); init(node->r, m+1, e);
}
void update(PSTNode *prv, PSTNode *now, int s, int e, int x){
  if(s == e){ now->v = prv ? prv->v + 1 : 1; return; }
  int m = s + e >> 1;
  if(x <= m){
    now->l = new PSTNode; now->r = prv->r;
    update(prv->l, now->l, s, m, x);
  }
  else{
    now->r = new PSTNode; now->l = prv->l;
    update(prv->r, now->r, m+1, e, x);
  } now->v = (now->l?now->l->v:0) + (now->r?now->r->v:0);
}
int kth(PSTNode *prv, PSTNode *now, int s, int e, int k){
  if(s == e) return s;
  int m = s + e >> 1, diff = now->l->v - prv->l->v;
  if(k <= diff) return kth(prv->l, now->l, s, m, k);
  else return kth(prv->r, now->r, m+1, e, k-diff);
}