template<typename T> T float_sum(vector<T> v){
  T sum=0, c=0, y, t; // sort abs(v[i]) increase?
  for(T i:v) y=i-c, t=sum+y, c=(t-sum)-y, sum=t;
  return sum; //worst O(eps*N), avg O(eps*sqrtN)
}//dnc: worst O(eps*logN), avg O(eps*sqrtlogN)