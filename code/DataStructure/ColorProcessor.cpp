/**
 * Author: Aeren
 * License: 
 * Source: https://github.com/Aeren1564/Algorithms/blob/master/Algorithm_Implementations_Cpp/Data_Structure/Color_Processor/color_processor.sublime-snippet
 * Description: 
 * Problem 1: https://www.acmicpc.net/problem/12856
 * Code 1: http://boj.kr/1b2bf2f14a934bafa8d80f477d3021af
 * Problem 2: https://codeforces.com/contest/1638/problem/E
 * Code 2: https://codeforces.com/contest/1638/submission/233234929
 */

template<class CT, class T> struct color_processor {
  map<array<CT, 2>, T> v; // CT: coord type
  color_processor(T col={}): v({{{MIN,MAX},col}}){}
  auto get_range(CT p){ return *prev(v.upper_bound({p, MAX})); }
  // Cover [l, r) with color c, amortized O(1) process call
  // process(l, r, pc, c): color of [l, r) change pc -> c
  auto cover(CT l, CT r, T c, auto process){
    array<CT, 2> I{l, l};
    auto it = v.lower_bound(I);
    if(it != v.begin() && l < prev(it)->fi[1]){
      auto x = *--it; v.erase(it);
      v.insert({{x.fi[0],l}, x.se});
      it = v.insert({{l,x.fi[1]}, x.se}).fi;
    }
    while(it != v.end() && it->fi[0] < r){
      if(r < it->fi[1]){
        auto x = *it; v.erase(it);
        it = v.insert({{x.fi[0],r}, x.se}).fi;
        v.insert({{r,x.fi[1]}, x.se});
      }
      process(max(l,it->fi[0]), min(r,it->fi[1]), it->se, c);
      I = {min(I[0],it->fi[0]), max(I[1],it->fi[1])};
      it = v.erase(it);
    } return v.insert({I, c});
  }
  // new_color(l, r, pc): return new color for
  // [l, r) previous color pc O(Number of color ranges affected)
  void recolor(CT l, CT r, auto new_color){
    auto left = v.lower_bound({l, l});
    if(l < left->fi[0]){
      auto [range, c] = *--left; left = v.erase(left);
      left = v.insert(left, {{range[0],l},c});
      left = v.insert(left, {{l,range[1]},c});
    }
    auto right = v.lower_bound({r, r});
    if(r < right->fi[0]){
      auto [range, c] = *--right; right = v.erase(right);
      right = v.insert(right,{{range[0],r},c});
      right = v.insert(right,{{r,range[1]},c});
    }
    for(auto it=left; it!=right; ++it)
      it->se = new_color(it->fi[0], it->fi[1], it->se);
  }
};