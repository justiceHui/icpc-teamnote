/**
 * Author: edenooo
 * License: 
 * Source: https://github.com/infossm/infossm.github.io/blob/master/_posts/2021-04-18-lichao-tree-lazy.md
 * Problem 1: https://www.acmicpc.net/problem/12795
 * Code 1: http://boj.kr/d7919377fcfd4fd699b34bb6c71378ef
 * Problem 2: https://atcoder.jp/contests/abc177/tasks/abc177_f
 * Code 2: https://atcoder.jp/contests/abc177/submissions/47653611
 */

/* get_point(x) : get min(f(x)), O(log X)
range_min(l,r) get min(f(x)), l<=x<=r, O(log X)
insert(l,r,a,b) : insert f(x)=ax+b, l<=x<=r, O(log^2 X)
add(l,r,a,b) : add f(x)=ax+b, l<=x<=r, O(log^2 X)
WARNING: a != 0인 add가 없을 때만 range_min 가능 */
template<typename T, T LE, T RI, T INF=(long long)(4e18)>
struct LiChao{
  struct Node{
    int l, r; T a, b, mn, aa, bb;
    Node(){ l = r = 0; a = 0; b = mn = INF; aa = bb = 0; }
    void apply(){ mn += bb; a += aa; b += bb; aa = bb = 0; }
    void add_lazy(T _aa, T _bb){ aa += _aa; bb += _bb; }
    T f(T x) const { return a * x + b; }
  }; vector<Node> seg; LiChao() : seg(2) {}
  void make_child(int n){
    if(!seg[n].l) seg[n].l = seg.size(), seg.emplace_back();
    if(!seg[n].r) seg[n].r = seg.size(), seg.emplace_back();
  }
  void push(int node, T s, T e){
    if(seg[node].aa || seg[node].bb){
      if(s != e){
        make_child(node);
        seg[seg[node].l].add_lazy(seg[node].aa, seg[node].bb);
        seg[seg[node].r].add_lazy(seg[node].aa, seg[node].bb);
      } seg[node].apply();
    }
  }
  void insert(T l, T r, T a, T b, int node=1, T s=LE, T e=RI){
    if(r < s || e < l || l > r) return;
    make_child(node); push(node, s, e); T m = (s + e) >> 1;
    seg[node].mn=min({seg[node].mn, a*max(s,l)+b,a*min(e,r)+b});
    if(s < l || r < e){
      if(l <= m) insert(l, r, a, b, seg[node].l, s, m);
      if(m+1 <= r) insert(l, r, a, b, seg[node].r, m+1, e);
      return;
    }
    T &sa = seg[node].a, &sb = seg[node].b;
    if(a*s+b < sa*s+sb) swap(a, sa), swap(b, sb);
    if(a*e+b >= sa*e+sb) return;
    if(a*m+b < sa*m+sb){
      swap(a,sa); swap(b,sb); insert(l,r,a,b,seg[node].l,s,m);
    } else insert(l, r, a, b, seg[node].r, m+1, e);
  }
  void add(T l, T r, T a, T b, int node=1, T s=LE, T e=RI){
    if(r < s || e < l || l > r) return;
    make_child(node); push(node, s, e); T m = (s + e) >> 1;
    if(s < l || r < e){
      insert(s, m, seg[node].a, seg[node].b, seg[node].l, s, m);
      insert(m+1,e,seg[node].a,seg[node].b,seg[node].r,m+1,e);
      seg[node].a = 0; seg[node].b = seg[node].mn = INF;
      if(l <= m) add(l, r, a, b, seg[node].l, s, m);
      if(m+1 <= r) add(l, r, a, b, seg[node].r, m+1, e);
      seg[node].mn=min(seg[seg[node].l].mn, seg[seg[node].r].mn);
      return;
    } seg[node].add_lazy(a, b); push(node, s, e);
  }
  T get_point(T x, int node=1, T s=LE, T e=RI){
    if(node == 0) return INF; push(node, s, e);
    T m = (s + e) >> 1, res = seg[node].f(x);
    if(x <= m) return min(res, get_point(x, seg[node].l, s, m));
    else return min(res, get_point(x, seg[node].r, m+1, e));
  }
  T range_min(T l, T r, int node=1, T s=LE, T e=RI){
    if(node == 0 || r < s || e < l || l > r) return INF;
    push(node, s, e); T m = (s + e) >> 1;
    if(l <= s && e <= r) return seg[node].mn;
    return min({ seg[node].f(max(s,l)), seg[node].f(min(e,r)),
       range_min(l, r, seg[node].l, s, m),
       range_min(l, r, seg[node].r, m+1, e) });
  }
};