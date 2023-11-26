/**
 * Author: JusticeHui
 * License: CC BY-NC-SA
 * Source: JusticeHui
 * Description: 
 * Problem: https://www.acmicpc.net/problem/27425
 * Code: http://boj.kr/f9ecbb88ef7c4e29b1962bc538b691b8
 */

bool segment_in_polygon_non_strict(const vector<Point> &poly, Point s, Point e){
  if(!PointInPolygon(poly, s, false) || !PointInPolygon(poly, e, false)) return false;
  if(s == e) return true; int cnt[4] = {0}; // no, at least one corner, mid, inf
  for(int j=(int)poly.size()-1, i=0; i<poly.size(); j=i++){
    int flag = get<0>(SegmentIntersect(poly[i], poly[j], s, e));
    if(flag<=0) flag = flag?3:0; else flag = max(1, flag-2);
    cnt[flag] += 1;
  }
  if(cnt[2] != 0 || cnt[3] > 1) return false;
  if((cnt[3] == 1 || cnt[1] != 0) && !PointInPolygon(poly, (s + e) / 2, false)) return false;
  return true;
}