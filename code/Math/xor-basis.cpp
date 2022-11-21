vector<ll> basis; // ascending
for(int i=0; i<n; i++){
    ll x; cin >> x;
    for(int j=(int)basis.size()-1; j>=0; j--) x = min(x, basis[j]^x);
    if(x) basis.insert(lower_bound(basis.begin(), basis.end(), x), x);
} // if xor maximization, reverse -> for(auto i:basis) r = max(r,r^i);