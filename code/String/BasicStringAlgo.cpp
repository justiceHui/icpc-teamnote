vector<int> getFail(const container &pat){
    vector<int> fail(pat.size());
    // match: pat[0..j] and pat[j-i..i] is equivalent
    // ins/del: manipulate corresponding range to pattern starts at 0
    //      (insert/delete pat[i], manage pat[j-i..i])
    function<bool(int, int)> match = [&](int i, int j){ };
    function<void(int)> ins = [&](int i){ };
    function<void(int)> del = [&](int i){ };
    for(int i=1, j=0; i<pat.size(); i++){
        while(j && !match(i, j)){
            for(int s=i-j; s<i-fail[j-1]; s++) del(s);
            j = fail[j-1];
        }
        if(match(i, j)) ins(i), fail[i] = ++j;
    }
    return fail;
}
vector<int> doKMP(const container &str, const container &pat){
    vector<int> ret, fail = getFail(pat);
    // match: pat[0..j] and str[j-i..i] is equivalent
    // ins/del: manipulate corresponding range to pattern starts at 0
    //      (insert/delete str[i], manage str[j-i..i])
    function<bool(int, int)> match = [&](int i, int j){ };
    function<void(int)> ins = [&](int i){ };
    function<void(int)> del = [&](int i){ };
    for(int i=0, j=0; i<str.size(); i++){
        while(j && !match(i, j)){
            for(int s=i-j; s<i-fail[j-1]; s++) del(s);
            j = fail[j-1];
        }
        if(match(i, j)){
            if(j+1 == pat.size()){
                ret.push_back(i-j);
                for(int s=i-j; s<i-fail[j]+1; s++) del(s);
                j = fail[j];
            }
            else ++j;
            ins(i);
        }
    }
    return ret;
}
// 1e5+3, 1e5+13, 131'071, 524'287, 1'299'709, 1'301'021
// 1e9-63, 1e9+7, 1e9+9, 1e9+103
template<ll P, ll M> struct Hashing {
    vector<ll> H, B;
    void Build(const string &S){
        H.resize(S.size()+1);
        B.resize(S.size()+1);
        B[0] = 1;
        for(int i=1; i<=S.size(); i++) H[i] = (H[i-1] * P + S[i-1]) % M;
        for(int i=1; i<=S.size(); i++) B[i] = B[i-1] * P % M;
    }
    ll sub(int s, int e){
        ll res = (H[e] - H[s-1] * B[e-s+1]) % M;
        return res < 0 ? res + M : res;
    }
};
// # a # b # a # a # b # a #
// 0 1 0 3 0 1 6 1 0 3 0 1 0
vector<int> Manacher(const string &inp){
    int n = inp.size() * 2 + 1;
    vector<int> ret(n);
    string s = "#";
    for(auto i : inp) s += i, s += "#";
    for(int i=0, p=-1, r=-1; i<n; i++){
        ret[i] = i <= r ? min(r-i, ret[2*p-i]) : 0;
        while(i-ret[i]-1 >= 0 && i+ret[i]+1 < n && s[i-ret[i]-1] == s[i+ret[i]+1]) ret[i]++;
        if(i+ret[i] > r) r = i+ret[i], p = i;
    }
    return ret;
}
// input: manacher array, 1-based hashing structure
// output: set of pair(hash_val, length)
set<pair<hash_t,int>> UniquePalindrome(const vector<int> &dp, const Hashing &hashing){
    set<pair<hash_t,int>> st;
    for(int i=0,s,e; i<dp.size(); i++){
        if(!dp[i]) continue;
        if(i & 1) s = i/2 - dp[i]/2 + 1, e = i/2 + dp[i]/2 + 1;
        else s = (i-1)/2 - dp[i]/2 + 2, e = (i+1)/2 + dp[i]/2;

        for(int l=s, r=e; l<=r; l++, r--){
            auto now = hashing.get(l, r);
            auto [iter,flag] = st.emplace(now, r-l+1);
            if(!flag) break;
        }
    }
    return st;
}
//z[i]=match length of s[0,n-1] and s[i,n-1]
vector<int> Z(const string &s){
    int n = s.size();
    vector<int> z(n);
    z[0] = n;
    for(int i=1, l=0, r=0; i<n; i++){
        if(i < r) z[i] = min(r-i-1, z[i-l]);
        while(i+z[i] < n && s[i+z[i]] == s[z[i]]) z[i]++;
        if(i+z[i] > r) r = i+z[i], l = i;
    }
    return z;
}