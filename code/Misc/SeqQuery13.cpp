struct Lz{
  ll a, b; // constructor, clear(a = 1, b = 0)
  Lz& operator+=(const Lz &t); // a *= t.a, b = t.a * b + t.b
};
struct Ty{
  ll cnt, sum; // constructor cnt=1, sum=0
  Ty& operator += (const Ty &t); // cnt += t.cnt, sum += t.sum
  Ty* operator += (const Lz &t); // sum= t .a * sum + cnt * t.b}
};