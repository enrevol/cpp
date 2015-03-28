#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
#define DEBUG(z, x) { cerr << setw(z) << "" << (#x) << " = " << (x) << '\n'; }
 
using namespace std;
 
const int N = 50010;
 
int n, pos, bridges, parent[N], comp[N], cyc[N], rank[N], mark[N];
 
// initialization
void init() {
  bridges = 0;
  for (int i = 1; i <= n; ++i) {
    parent[i] = 0;
    comp[i] = cyc[i] = i;
    rank[i] = 0;
  }  
}
 
// find cycle representative of u
int find_cyc(int u) {
  if (cyc[u] != u) cyc[u] = find_cyc(cyc[u]);
  return cyc[u];
}
 
// find component representative of u
int find_comp(int u) {
  if (comp[u] != u) comp[u] = find_comp(comp[u]);
  return comp[u];
}
 
// compress cycle inclung u and v
void compress(int u, int v) {
  ++pos; // mark for lca searching
  int lca = 0;
  static int u_path[N], v_path[N];
  int u_sz = 0, v_sz = 0;
  for (;;) {
    if (u) {
      u = find_cyc(u);
      u_path[++u_sz] = u;
      if (mark[u] == pos) {
        lca = u;
        break;
      }
      mark[u] = pos;
      u = parent[u];
    }
    if (v) {
      v = find_cyc(v);
      v_path[++v_sz] = v;
      if (mark[v] == pos) {
        lca = v;
        break;
      }
      mark[v] = pos;
      v = parent[v];
    }        
  }
  for (int i = 1; i <= u_sz; ++i) {
    int x = u_path[i];
    cyc[x] = lca;
    if (x == lca) break;
    --bridges;
  }
  for (int i = 1; i <= v_sz; ++i) {
    int x = v_path[i];
    cyc[x] = lca;
    if (x == lca) break;
    --bridges;
  }
}
 
// make u the root of the tree including u
void reroot(int u) {
  u = find_cyc(u);
  int root = u; // new root
  int child = 0; // old child vertex
  // repeatly reverse edge
  int depth = 0;
  while (u) {
    int p = find_cyc(parent[u]);
    parent[u] = child;
    comp[u] = root;
    child = u;
    u = p;
    ++depth;
  }
  rank[root] = max(rank[root], depth);
}
 
void add_edge(int u, int v) {
  u = find_cyc(u);
  v = find_cyc(v);
  if (u == v) {
    // u and v are in the same cycle - no changes
    return;
  }
  int uid = find_comp(u);
  int vid = find_comp(v);
  if (uid != vid) {
    // u and v are in different components
    // adding edge (u, v) creates a bridge and makes u and v in the same component and in different cycles
    ++bridges;
    // unite u and v component ids, let u is the smaller tree    
    if (rank[uid] > rank[vid]) {
      swap(u, v);
      swap(uid, vid);
    }
    // reroot u
    reroot(u);
    // u is now the root
    // make u a child of v
    parent[u] = v;
    // update component id
    comp[u] = v;
    // update rank heuristic
    rank[vid] += rank[vid] == rank[u];
  } else {
    // u and v are in the same components
    // adding edge (u, v) creates a cycle including u and v
    // all bridges in this cycle won't be bridges anymore
    // the number of those bridges is equal to (cycle length - 1)
    compress(u, v);
  }
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int m;
    scanf("%d %d", &n, &m);
    init();
    while (m--) {
      int u, v;
      scanf("%d %d", &u, &v);
      ++u, ++v;
      add_edge(u, v);      
      printf("%d\n", bridges);
    }
  }
} 
