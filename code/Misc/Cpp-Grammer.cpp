mt19937 rd((unsigned)chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> rnd_int(l, r); // rnd_int(rd)
uniform_real_distribution<double> rnd_real(0, 1);// rnd_real(rd)
// ext/pb_ds/assoc_container.hpp, tree_policy.hpp, rope
// namespace __gnu_pbds (find_by_order, order_of_key)
// namespace __gnu_cxx (append(str), substr(l, r), at(idx))
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
bool next_combination(T &bit, int N){
  T x = bit & -bit, y = bit + x;
  bit = (((bit & ~y) / x) >> 1) | y;
  return (bit < (1LL << N)); }
long long next_perm(long long v){
  long long t = v | (v-1);
  return (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));
} // __builtin_clz/ctz/popcount
for(submask=mask; submask; submask=(submask-1)&mask);
for(supermask=mask; supermask<(1<<n); supermask=(supermask+1)|mask);
int frq(int n, int i) { int j, r = 0; // # of digit i in [1, n]
  for (j = 1; j <= n; j *= 10) if (n / j / 10 >= !i) r += (n / 10 / j - !i) * j + (n / j % 10 > i ? j : n / j % 10 == i ? n % j + 1 : 0);
  return r; }
bitset<17> bs; bs[1] = bs[7] = 1; assert(bs._Find_first() == 1);
assert(bs._Find_next(0) == 1 && bs._Find_next(1) == 7);
assert(bs._Find_next(3) == 7 && bs._Find_next(7) == 17);
cout << bs._Find_next(7) << "\n";
template <int len = 1> // Arbitrary sized bitset
void solve(int n){ // solution using bitset<len>
  if(len < n){ solve<std::min(len*2, MAXLEN)>(n); return; } }