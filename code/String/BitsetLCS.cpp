#include <x86intrin.h>
template<size_t _Nw> void _M_do_sub(_Base_bitset<_Nw> &A, const _Base_bitset<_Nw> &B){
  for(int i=0, c=0; i<_Nw; i++) c = _subborrow_u64(c, A._M_w[i], B._M_w[i], (ull*)&A._M_w[i]);
}
void _M_do_sub(_Base_bitset<1> &A, const _Base_bitset<1> &B){ A._M_w -= B._M_w; }
template<size_t _Nb> bitset<_Nb>& operator-=(bitset<_Nb> &A, const bitset<_Nb> &B){
  _M_do_sub(A, B); return A;
}
template<size_t _Nb> inline bitset<_Nb> operator-(const bitset<_Nb> &A, const bitset<_Nb> &B){
  bitset<_Nb> C(A); return C -= B;
}
char s[50050], t[50050];
int lcs(){ // O(NM/64)
  bitset<50050> dp, ch[26];
  int n = strlen(s), m = strlen(t);
  for(int i=0; i<m; i++) ch[t[i]-'A'].set(i);
  for(int i=0; i<n; i++){ auto x = dp | ch[s[i]-'A']; dp = dp - (dp ^ x) & x; }
  return dp.count();
}