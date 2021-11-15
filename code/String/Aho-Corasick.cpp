struct Node{
  map<char, Node*> ch; int terminal;
  Node() : terminal(-1) {}
  ~Node(){
    for(auto &i : ch) delete i.second;
    ch.clear();
  }
  void insert(const char *key, int num){
    if(*key == 0){ terminal = num; return; }
    if(!ch[*key]) ch[*key] = new Node();
    ch[*key]->insert(key+1, num);
  }
  Node *fail; vector<int> out;
};
void aho_getFail(Node *root){
  queue<Node*> q; q.push(root);
  root->fail = root;
  while(q.size()){
    Node *now = q.front(); q.pop();
    for(auto &i : now->ch){
      Node *ch = i.second;
      if(!ch) continue;
      if(root == now) ch->fail = root;
      else{
        Node *t = now->fail;
        while(t != root && !t->ch[i.first]) t = t->fail;
        if(t->ch[i.first]) t = t->ch[i.first];
        ch->fail = t;
      }
      ch->out = ch->fail->out;
      if(ch->terminal != -1) ch->out.push_back(ch->terminal);
      q.push(ch);
    }
  }
}
vector<p> aho_find(const string &s, Node *root){
  vector<p> ret; auto state = root;
  for(int i=0; i<s.size(); i++){
    while(state != root && !state->ch[s[i]]) state = state->fail;
    if(state->ch[s[i]]) state = state->ch[s[i]];
    for(int j=0; j<state->out.size(); j++){
      ret.emplace_back(i, state->out[j]);
    }
  }
  return ret;
}