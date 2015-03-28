#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#define pb push_back
using namespace std;
int depthType;
struct node {
  node* parent;
  vector<node*> child;  
  int depth, value;
};
int dfs(node* current) {
  if (current->value != -1) return current->value;  
  int depth = current->depth;
  int sz = current->child.size();
  int res = current->child[0]->value;
  if (res == -1) res = dfs(current->child[0]);
  for (int i = 1; i < sz; ++i) {
    int t = dfs(current->child[i]);
    if ((depth & 1) != depthType) res &= t;
    else res |= t;
  }
  return res;
}
int main() {
  int nCase = 0;
  string s;
  while (cin >> s) {
    if (s == "()") break;
    node root;
    node* current = &root;
    root.depth = 0;
    root.value = -1;
    int maxDepth = 0;
    for (int i = 1; i < s.length() - 1; ++i) {    
      if (s[i] != ')') {
        node* t = new node();
        t->depth = current->depth + 1;
        t->parent = current;
        current->child.pb(t);
        if (s[i] == '(') {
          current = t;
          t->value = -1;
        } else {
          t->value = s[i] == 'T';
        }
        maxDepth = max(maxDepth, t->depth);
      }
      else {
        current = current->parent;
      }
    }
    depthType = maxDepth & 1;
    int d = dfs(&root);
    string ans;
    if (d) ans = "true";
    else ans = "false";
    cout << ++nCase << ". " << ans << '\n';    
  }    
}