template<class T, bool GET_MAX = false> // D[i] = func_{0 <= j < i} D[j] + cost(j, i)
pair<vector<T>, vector<int>> monotone_queue_dp(int n, const vector<T> &init, auto cost){
  assert((int)init.size() == n + 1); // cost function -> auto, do not use std::function
  vector<T> dp = init; vector<int> prv(n+1);
  auto compare = [](T a, T b){ return GET_MAX ? a < b : a > b; };
  auto cross = [&](int i, int j){
    int l = j, r = n + 1;
    while(l < r){
      int m = (l + r + 1) / 2;
      if(compare(dp[i] + cost(i, m), dp[j] + cost(j, m))) r = m - 1; else l = m;
  } return l; };
  deque<int> q{0};
  for(int i=1; i<=n; i++){
    while(q.size() > 1 && compare(dp[q[0]] + cost(q[0], i), dp[q[1]] + cost(q[1], i))) q.pop_front();
    dp[i] = dp[q[0]] + cost(q[0], i); prv[i] = q[0];
    while(q.size() > 1 && cross(q[q.size()-2], q.back()) >= cross(q.back(), i)) q.pop_back();
    q.push_back(i);
  } /*for end*/ return {dp, prv}; }