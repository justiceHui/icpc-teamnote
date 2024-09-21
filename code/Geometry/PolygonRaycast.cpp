/**
 * Author: zigui
 * License: 
 * Source: https://zigui.tistory.com/5
 * Description: get every events between polygon and line
 * Problem(raycast): https://www.acmicpc.net/problem/14633
 * Code(raycast): http://boj.kr/7dd1a350000a4be6921a3ecf5a91a125
 * Problem(visible): https://www.acmicpc.net/problem/2125
 * Code(visible): http://boj.kr/52ce2f887c734d45bdf8adb6e8af5162
 */

// ray A + kd and CCW polygon C, return events {k, event_id}
// 0: out->line / 1: in->line / 2: line->out / 3: line->in
// 4: pass corner outside / 5: pass corner inside / 6: out -> in / 7: in -> out
// WARNING: C.push_back(C[0]) before use, ccw, no colinear
struct frac{
  ll first, second; frac(){}
  frac(ll a, ll b) : first(a), second(b) {
    if( b < 0 ) first = -a, second = -b; // operator cast int128
  } double v(){ return 1.*first/second; } // operator <,<=,==
}; // assert(d != P(0,0));
frac raypoints(const vector<P> &C, P A, P d, vector<pair<frac, int>> &R){ vector<pair<frac, int>> L;
  auto g = gcd(abs(d.x), abs(d.y)); d.x /= g, d.y /= g;
  for(int i = 0; i+1 < C.size(); i++){ P v = C[i+1] - C[i];
    int a = sign(d/(C[i]-A)), b = sign(d/(C[i+1]-A));
    if(a == 0)L.emplace_back(frac(d*(C[i]-A)/size2(d), 1), b);
    if(b == 0)L.emplace_back(frac(d*(C[i+1]-A)/size2(d), 1),a);
    if(a*b == -1) L.emplace_back(frac((A-C[i])/v, v/d), 6);
  } sort(L.begin(), L.end());
  for(int i = 0; i < L.size(); i++){
    // assert(i+2 >= L.size() || !(L[i].first == L[i+2].first));
    if(i+1<L.size()&&L[i].first==L[i+1].first&&L[i].second!=6){
      int a = L[i].second, b = L[i+1].second;
      R.emplace_back(L[i++].first, a*b? a*b > 0? 4:6:(1-a-b)/2);
    } /* end if */ else R.push_back(L[i]); } /* end for */
  int state = 0; // 0: out, 1: in, 2: line+ccw, 3: line+cw
  for(auto &[_,n] : R){
    if( n == 6 ) n ^= state, state ^= 1;
    else if( n == 4 ) n ^= state;
    else if( n == 0 ) n = state, state ^= 2;
    else if( n == 1 ) n = state^(state>>1), state ^= 3;
  } return frac(g, 1);
}
bool visible(const vector<P> &C, P A, P B){
  if( A == B ) return true;//return outside?
  char I[4] = "356", O[4] = "157";
  vector<pair<frac, int>> R; vector<frac> E;
  frac s = frac(0, 1), e = raypoints(C, A, B-A, R);
  for(auto [f,n] : R){
    if(*find(O, O+3, n+'0')) E.push_back(f);
    if(*find(I, I+3, n+'0')) E.push_back(f);
  }
  for(int j = 0; j < E.size(); j += 2) if( !(e <= E[j] || E[j+1] <= s) ) return false;
  return true; }