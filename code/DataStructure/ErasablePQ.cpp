/**
 * Author: cgiosy
 * License: 
 * Source: https://gist.github.com/cgiosy/14d0076e7f735c0a05890ad3c8071096
 * Problem: https://www.acmicpc.net/problem/7662
 * Code: http://boj.kr/f793b752cab14e1684dea4d1fd149e2c
 */

template<class T=int, class O=less<T>>
struct pq_set {
  priority_queue<T, vector<T>, O> q, del;
  const T& top() const { return q.top(); }
  int size() const { return int(q.size()-del.size()); }
  bool empty() const { return !size(); }
  void insert(const T x) { q.push(x); flush(); }
  void pop() { q.pop(); flush(); }
  void erase(const T x) { del.push(x); flush(); }
  void flush() { while(del.size() && q.top()==del.top()) q.pop(), del.pop(); }
};