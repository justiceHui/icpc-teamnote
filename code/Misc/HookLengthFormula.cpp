int HookLength(const vector<int> &young){
  if(young.empty()) return 1;
  vector<int> len(young[0]);
  ll num = 1, div = 1, cnt = 0;
  for(int i=(int)young.size()-1; i>=0; i--){
    for(int j=0; j<young[i]; j++){
      num = num * ++cnt % MOD;
      div = div * (++len[j] + young[i] - j - 1) % MOD;
    }
  }
  return num * Pow(div, MOD-2) % MOD;
}