template<class T, class U>
T incMod(T x, U mod) { x += 1; return x == mod ? 0 : x; }
template<class Domain, class CoDomain, size_t LEN = 5>
pair<Domain, CoDomain> dlas( function<CoDomain(Domain&)> f,
  function<void(Domain&)> mutate,
  Domain const& initial, u64 maxIdleIters = -1ULL) {
  array<Domain, 3> S{initial, initial, initial};
  CoDomain curF = f(S[0]), minF = curF;
  size_t curPos = 0, minPos = 0, k = 0;
  array<CoDomain, LEN> fitness; fitness.fill(curF);
  for(u64 idleIters=0; idleIters<maxIdleIters; idleIters++){
    CoDomain prvF = curF;
    size_t newPos = incMod(curPos, 3);
    if (newPos == minPos) newPos = incMod(newPos, 3);
    Domain &curS = S[curPos], &newS = S[newPos];
    newS = curS; mutate(newS); CoDomain newF = f(newS);
    if(newF < minF) idleIters=0, minPos=newPos, minF=newF;
    if(newF == curF || newF < *max_element(all(fitness))){
      curPos = newPos; curF = newF;
    } CoDomain& fit = fitness[k]; k = incMod(k, LEN);
    if(curF > fit || curF < fit && curF < prvF) fit = curF;
  } return { S[minPos], minF };
} // 점수 최소화하는 함수, f: 상태의 점수를 반환
//dlas<state_type, score_type>(f, mutate, initial, maxIdleIter)
//initial:초기 상태, mutate:상태를 참조로 받아서 임의로 수정(반환X)
//maxIdleIters:지역 최적해에서 알마나 오래 기다릴지