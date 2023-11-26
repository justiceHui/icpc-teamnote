/**
 * Author: (1) JusticeHui (2) Simon Lindholm
 * License: (1) CC BY-NC-SA (2) CC0
 * Source: (2) https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h
 * Problem 1: https://www.acmicpc.net/problem/10067
 * Code 1: (1) http://boj.kr/75d08d8ae7774e4f8b2fa3f99cb2c1da
 * Problem 2: https://www.acmicpc.net/problem/12795
 * Code 2: (2) http://boj.kr/f8e1d97f405c4839aac5ed3c28cf15d8
 * Problem 3: https://www.acmicpc.net/problem/24894
 * Code 3: (2) http://boj.kr/6099a68b9a024881a952b82fcccab012
 */

struct Line{ // call init() before use
  ll a, b, c; // y = ax + b, c = line index
  Line(ll a, ll b, ll c) : a(a), b(b), c(c) {}
  ll f(ll x){ return a * x + b; }
};
vector<Line> v; int pv;
void init(){ v.clear(); pv = 0; }
int chk(const Line &a, const Line &b, const Line &c) const {
  return (__int128_t)(a.b - b.b) * (b.a - c.a) <= (__int128_t)(c.b - b.b) * (b.a - a.a);
}
void insert(Line l){
  if(v.size() > pv && v.back().a == l.a){
    if(l.b < v.back().b) l = v.back(); v.pop_back();
  }
  while(v.size() >= pv+2 && chk(v[v.size()-2], v.back(), l)) v.pop_back();
  v.push_back(l);
}
p query(ll x){ // if min query, then v[pv].f(x) >= v[pv+1].f(x)
  while(pv+1 < v.size() && v[pv].f(x) <= v[pv+1].f(x)) pv++;
  return {v[pv].f(x), v[pv].c};
}
///// line container start (max query) /////
struct Line {
  mutable ll k, m, p;
  bool operator<(const Line& o) const { return k < o.k; }
  bool operator<(ll x) const { return p < x; }
}; // (for doubles, use inf = 1/.0, div(a,b) = a/b)
struct LineContainer : multiset<Line, less<>> {
  static const ll inf = LLONG_MAX; // div: floor
  ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
  bool isect(iterator x, iterator y) {
    if (y == end()) return x->p = inf, 0;
    if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
    else x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
  void add(ll k, ll m) {
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
  } ll query(ll x) { assert(!empty());
    auto l = *lower_bound(x); return l.k * x + l.m; }
};