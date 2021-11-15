//NOTE: n*m행렬이다. 코드는 <m>(n)형태니 조심
#pragma GCC optimize ("Ofast")
int REF(bool pv_fix){
  int pi = 0;
  for(int i=0; i<n; i++){
    while(pi < m && !a[i][pi]){
      if(!pv_fix){
        for(int j=i+1; j<n; j++) if(a[j][pi]) break;
        if(j < n){ swap(a[i], a[j]); break; }
      }
      pi++;
    }
    if(pi == m)break;
    if(a[i][pi])for(int j=i+1;j<n;j++)if(a[j][pi])a[j]^=a[i];
    pi++;
  }
  return rank = i;
}
int RREF(int rm){REF(false),flipX(rank),flipY(rm),REF(true),flipY(rm),flipX(rank);return rank;}
void flipX(int rn){
  for(int i=0; i<rn/2; i++) swap(a[i], a[rn-1-i]);
}
void flipY(int rm){
  for(int i=0;i<n;i++) for(int j=0;j<rm/2;j++) swap(a[i][j], a[i][rm-1-j]);
}