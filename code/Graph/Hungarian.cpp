/**
 * Author: ?
 * License: ?
 * Source: https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/graphs%20(12)/Matching/Hungarian.h
 * Description: 
 * Problem: https://judge.yosupo.jp/problem/assignment
 * Code: https://judge.yosupo.jp/submission/234568
 */

// C[j][w] = cost(j-th job, w-th worker), j <= w, O(J^2W)
// ret[i] = minimum cost to assign 0..i jobs to distinct workers
template<typename T>bool ckmin(T &a, const T &b){return b<a ? a=b,1 : 0;}
template<typename T>vector<T>Hungarian(const vector<vector<T>>&C){
  const int J = C.size(), W = C[0].size(); assert(J <= W);
  vector<int> job(W+1, -1); //job[i] - i(worker) matched
  vector<T> ys(J), yt(W + 1), answers;//W-th worker is dummy
  const T inf = numeric_limits<T>::max();
  for(int j_cur=0; j_cur<J; j_cur++){
    int w_cur = W; job[w_cur] = j_cur;
    vector<T> min_to(W+1,inf);vector<int> prv(W+1, -1),in(W+1);
    while(job[w_cur] != -1){
      in[w_cur]=1; T delta=inf; int j = job[w_cur], w_next;
      for(int w=0; w<W; w++){ if(in[w] != 0) continue;
        if(ckmin(min_to[w], C[j][w]-ys[j]-yt[w])) prv[w]=w_cur;
        if(ckmin(delta, min_to[w])) w_next = w;
      }
      for(int w=0; w<=W; w++){
        if(in[w] == 0) min_to[w] -= delta;
        else ys[job[w]] += delta, yt[w] -= delta;
      } /*end for w*/ w_cur = w_next; } /* end while */
    for(int w; w_cur!=-1; w_cur=w)job[w_cur]=job[w=prv[w_cur]];
    answers.push_back(-yt[W]);
  } return answers; }