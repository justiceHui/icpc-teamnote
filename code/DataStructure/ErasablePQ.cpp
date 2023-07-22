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