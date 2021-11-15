template<typename T, T inf>
struct pq_set{
  priority_queue<T, vector<T>, greater<T>> in, out; // min heap, inf = 1e18
  // priority_queue<T> in, out; // max heap, inf = -1e18
  pq_set(){ in.push(inf); }
  void insert(T v){ in.push(v); }
  void erase(T v){ out.push(v); }
  T top(){
  while(out.size() && in.top() == out.top()) in.pop(), out.pop();
  return in.top();
  }
  bool empty(){
  while(out.size() && in.top() == out.top()) in.pop(), out.pop();
  return in.top() == inf;
  }
};