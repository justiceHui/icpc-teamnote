//입력: Ax<=b, obj
//출력: maximize obj*x
//numeric stability is sensitive by M
//디버깅 노트
//1. T=f64 해보기(정수값만 나오는거같아도 중간에 유리수나올때 있음)
//2. M값 조절(답의 상한정도의 크기가 적절)
//듀얼후 리덕션한 결과값 primal로 복원하기
template<class T=f64,int M>
void dualize(Arr<Arr<T>> &a,Arr<T> &b,Arr<T>& obj){
  int m=sz(a), n=sz(a[0]);
  transpose(a),swap(b,obj);
  for(int i=0;i<n;i++){
    for(auto& j:a[i])j=-j;
    b[i]=-b[i];
  }
  for(auto& i:obj)i=-i;
}
template<class T=f64,int M>
tuple<T,Arr<T>,Arr<T>> simplex(Arr<Arr<T>>& a,Arr<T>& b,Arr<T>& obj){
  //return {maxval,argmax,dual_argmin}
  int m=sz(a),n=sz(a[0]),s=0;
  if(m>n){
    dualize<T,M>(a,b,obj);
    auto&& [x,y,z]=simplex<T,M>(a,b,obj);
    x*=-1;
    swap(y,z);
    return {move(x),move(y),move(z)};
  }
  func(void,elim,int r1,int r2,int c){//elim r2
    if(r1==r2){T x=a[r1][c]; for(auto& i:a[r1])i/=x;}
    else{
      T x=a[r2][c]/a[r1][c]; if(-eps<x&&x<eps)return;
      for(int i=0;i<n+s+m+2;i++)
        a[r2][i]-=x*a[r1][i];
    }
  };

  //make all b>=0
  Arr<char> geq(m);
  for(int i=0;i<m;i++)
    if(b[i]<0){
      for(auto& j:a[i])j=-j;
      for(auto& r:a)r.emplb(0);
      a[i][-1]=-1,b[i]=-b[i],geq[i]=true,s++;
    }

  //n vars, s slacks(-1), m slacks(1), 1 z, 1 b_value
  Arr<int> p(m);//행의 기본변수
  obj.resize(n+s+m+2);
  for(int i=0;i<m;i++)
    a[i].resize(n+s+m+2),a[i][p[i]=n+s+i]=1,a[i][-1]=b[i],obj[p[i]]=geq[i]?-M:0;
  
  //z=f(x) == z-f(x)=0
  for(auto &i:obj)i=-i;
  obj[-2]=1;
  a.emplb(obj);
  
  for(int i=0;i<m;i++)
    elim(i,m,p[i]);
  
  //now shape of a = (m+1)*(n+s+m+2)
  while(true){
    int ev=0,lvi=-1;
    for(int i=0;i<n+s+m;i++)
      ev=a[-1][ev]>a[-1][i]?i:ev;
    if(a[-1][ev]>-eps)break;
    for(int i=0;i<m;i++)
      if(a[i][ev]>eps and (!~lvi or a[i][-1]/a[i][ev]<a[lvi][-1]/a[lvi][ev]))
        lvi=i;
    if(!~lvi) throw "unbounded";
    for(int i=0;i<m+1;i++)elim(lvi,i,ev);
    p[lvi]=ev;
  }
  //if(?) throw "infeasible"
  Arr<T> ans(n+s+m+2);
  for(int i=0;i<m;i++)
    ans[p[i]]=a[i][-1];
  Arr<T> dual(m);
  for(int i=0;i<m;i++)
    dual[i]=a[-1][n+s+i]+(geq[i]?+M:0);
  return {a[-1][-1],ans,dual};
}