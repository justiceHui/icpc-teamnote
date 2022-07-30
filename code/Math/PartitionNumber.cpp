for(int j=1; j*(3*j-1)/2<=i; j++) P[i] += (j%2?1:-1)*P[i-j*(3*j-1)/2], P[i] %= MOD;
for(int j=1; j*(3*j+1)/2<=i; j++) P[i] += (j%2?1:-1)*P[i-j*(3*j+1)/2], P[i] %= MOD;