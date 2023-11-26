template<typename T> T float_sum(vector<T> v){
  T sum=0, c=0, y, t;
  for(T i:v) y=i-c, t=sum+y, c=(t-sum)-y, sum=t;
  return sum; //worst O(eps*N), avg O(eps*sqrtN)
}//dnc: worst O(eps*logN), avg O(eps*sqrtlogN)
// 1. split positive / negative
// 2. sort by abs(v[i]) increasing order
// 3. if sum <= 0 then add positive else negetive