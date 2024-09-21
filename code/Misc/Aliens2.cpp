// pair<T, vector<int>> f(T c): return opt_val, prv
// cost function must be multiplied by 2
template<class T, bool GET_MAX = false>
pair<T,vector<int>> AliensTrick(int n,int k,auto f,T lo,T hi){
    T l = lo, r = hi; while(l < r) {
        T m = (l + r + (GET_MAX?1:0)) >> 1;
        vector<int> prv = f(m*2+(GET_MAX?-1:+1)).second;
        int cnt = 0; for(int i=n; i; i=prv[i]) cnt++;
        if(cnt <= k) (GET_MAX?l:r) = m;
        else (GET_MAX?r:l) = m + (GET_MAX?-1:+1);
    }
    T opt_value = f(l*2).first / 2 - k*l;
    vector<int> prv1 = f(l*2+(GET_MAX?1:-1)).second, p1{n};
    vector<int> prv2 = f(l*2-(GET_MAX?1:-1)).second, p2{n};
    for(int i=n; i; i=prv1[i]) p1.push_back(prv1[i]);
    for(int i=n; i; i=prv2[i]) p2.push_back(prv2[i]);
    reverse(p1.begin(),p1.end());reverse(p2.begin(),p2.end());
    assert(p2.size() <= k+1 && k+1 <=p1.size());
    if(p1.size() == k+1) return {opt_value, p1};
    if(p2.size() == k+1) return {opt_value, p2};
    for(int i=1, j=1; i<p1.size(); i++){
        while(j < p2.size() && p2[j] < p1[i-1]) j++;
        if(p1[i] <= p2[j] && i - j == k+1 - (int)p2.size()){
            vector<int> res;
            res.insert(res.end(), p1.begin(), p1.begin()+i);
            res.insert(res.end(), p2.begin()+j, p2.end());
            return {opt_value, res};
    } /* if */ } /* for */ assert(false);
}