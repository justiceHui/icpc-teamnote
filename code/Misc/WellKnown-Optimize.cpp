// Quadrangle Inequality : C(a, c)+C(b, d) ≤ C(a, d)+C(b, c)
// Monotonicity : C(b, c) ≤ C(a, d)
// CHT, DnC Opt(Quadrangle), Knuth(Quadrangle and Monotonicity)
// Knuth: K[i][j-1] <= K[i][j] <= K[i+1][j]
  // 1. Calculate D[i][i], K[i][i]
  // 2. Calculate D[i][j], K[i][j] (i < j)
// Another: D[i][j] = min(D[i-1][k] + C[k+1][j]), C quadrangle
  // i=1..k  j=n..1  k=K[i-1][j]..K[i][j+1]  update, vnoi/icpc22_mn_c

// 크기가 A, B인 두 서브트리의 결과를 합칠 때 O(AB)이면 O(N^3)이 아니라 O(N^2)
// 각 정점마다 sum(2 ~ C번째로 높이가 작은 정점의 높이)에 결과를 구할 수 있으면 O(N^2)이 아니라 O(N)

// IOI 16 Alien(Lagrange Multiplier)
// IOI 09 Region, IOI 11 Elephant(sqrt batch process)
// 서로소 합집합의 크기가 적당히 bound 되어 있을 때 사용
// 쿼리 메모이제이션 / 쿼리 하나에 O(A log B), 전체 O(N√Q log N)