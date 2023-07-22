using T = __int128_t; // T <= O(COORD^3)
// 0: not intersect, -1: infinity, 1: cross
// flag, xp, xq, yp, yq : (xp / xq, yp / yq)
tuple<int, T, T, T, T> FindPoint(Point s1, Point e1, Point s2, Point e2){
    if(!Intersect(s1, e1, s2, e2)) return {0, 0, 0, 0, 0};
    auto det = (e1 - s1) / (e2 - s2);
    if(!det){
        if(s1 > e1) swap(s1, e1);
        if(s2 > e2) swap(s2, e2);
        if(e1 == s2) return {1, e1.x, 1, e1.y, 1};
        if(e2 == s1) return {1, e2.x, 1, e2.y, 1};
        return {-1, 0, 0, 0, 0};
    }
    T p = (s2 - s1) / (e2 - s2), q = det;
    T xp = s1.x * q + (e1.x - s1.x) * p, xq = q;
    T yp = s1.y * q + (e1.y - s1.y) * p, yq = q;
    if(xq < 0) xp = -xp, xq = -xq;
    if(yq < 0) yp = -yp, yq = -yq;
    T xg = __gcd(abs(xp), xq), yg = __gcd(abs(yp), yq);
    return {1, xp/xg, xq/xg, yp/yg, yq/yg};
}