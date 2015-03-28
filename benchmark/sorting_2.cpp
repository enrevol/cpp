#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include <cstdlib>
#include <ctime>

#include <windows.h>

class timer {
  _LARGE_INTEGER start_time_;
 public:
  timer() {
    QueryPerformanceCounter(&start_time_);
  }
  void restart() {
    QueryPerformanceCounter(&start_time_);
  }
  double elapsed() const {
    _LARGE_INTEGER end_time, frequency;
    QueryPerformanceCounter(&end_time);
    QueryPerformanceFrequency(&frequency);
    return double(end_time.QuadPart - start_time_.QuadPart) / frequency.QuadPart;
  }
} tm;

typedef std::pair<int, int> p2;

const int N = 1e6; // number of elements
const int M = 1e7;

int arr[N];

inline
long long generate(long long from, long long to) {
  long long x = 0;
  long double m = to - from + 1;
  for (int i = 0; i < 3; ++i) {
    x += (m / 32768) * rand();
    m /= 32768;
  }
  return x + from;
}

template<int max_size, typename T, class Node>
class Tree
{
 protected:
  Node* __root;
  Node* __data;
  Node* __next;
  
 public:
  Tree()
  {
    __data = new Node[max_size + 1];
    __root = __next = __data;    
  }
  
  ~Tree()
  {
    delete[] __data;
  }
  
  inline
  int
  size() const
  {
    return __next - __data;
  }
};

template<int max_size, typename T, class Node>
class Tree_normal : public Tree<max_size, T, Node>
{
  inline
  long long
  __total_height(const Node* current, const int depth) const
  {
    if (current == this->__data)
      return 0;
    return __total_height(current->left, depth + 1) + depth + __total_height(current->right, depth + 1);
  }
  
  inline
  int
  __max_depth(const Node* current, const int depth) const
  {
    if (current == this->__data)
      return 0;
    return std::max(depth, std::max(__max_depth(current->left, depth + 1), __max_depth(current->right, depth + 1)));
  }
    
  inline
  void
  __inorder(const Node* current) const  
  {
    if (current->left != this->__data)
      __inorder(current->left);
    printf("%d\n", current->key);
    if (current->right != this->__data)
      __inorder(current->right);
  }
  
 public:
  Tree_normal()
  {
    this->__data->left = this->__data->right = this->__data;
  }
  
  inline
  void
  inorder() const
  {
    puts("-----");
    __inorder(this->__root);
  }
  
  inline
  long long
  total_height() const
  {
    return __total_height(this->__root, 0);
  }
  
  inline
  int
  max_depth() const
  {
    return __max_depth(this->__root, 0);
  }
};

template<int max_size, typename T, class Node>
class Tree_indexed : public Tree<max_size, T, Node>
{
  inline
  long long
  __total_height(const Node* current, const int depth) const
  {
    if (current == this->__data)
      return 0;
    return __total_height(current->node[0], depth + 1) + depth + __total_height(current->node[1], depth + 1);
  }
  
  inline
  int
  __max_depth(const Node* current, const int depth) const
  {
    if (current == this->__data)
      return 0;
    return std::max(depth, std::max(__max_depth(current->node[0], depth + 1), __max_depth(current->node[1], depth + 1)));
  }
    
  inline
  void
  __inorder(const Node* current) const  
  {
    if (current->node[0] != this->__data)
      __inorder(current->node[0]);
    printf("%d\n", current->key);
    if (current->node[1] != this->__data)
      __inorder(current->node[1]);
  }
  
 public:
  Tree_indexed()
  {
    this->__data->node[0] = this->__data->node[1] = this->__data;
  }  
  
  inline
  void
  inorder() const
  {
    puts("-----");
    __inorder(this->__root);
  }
  
  inline
  long long
  total_height() const
  {
    return __total_height(this->__root, 0);
  }
  
  inline
  int
  max_depth() const
  {
    return __max_depth(this->__root, 0);
  }
};

template<typename T>
struct BST_Node
{
  BST_Node* left;
  BST_Node* right;
  T key;
};

template<int max_size, typename T>
class BST : public Tree_normal<max_size, T, BST_Node<T>>
{
  typedef BST_Node<T> _Node;
  
 public:
  inline
  void
  insert(const T key)
  {
    _Node* z = this->__root;
    _Node* p = this->__data;
    while (z != this->__data && z->key != key)
    {
      p = z;
      if (key < z->key) z = z->left;
      else z = z->right;
    }
    if (z == this->__data)
    {
      z = ++this->__next;
      z->key = key;
      z->left = z->right = this->__data;
      if (p == this->__data) this->__root = z;
      else if (p->key < z->key) p->right = z;
      else p->left = z;
    }
  }
};

template<typename T>
struct Treap_Node_recursive
{
  Treap_Node_recursive* left;
  Treap_Node_recursive* right;
  T key;
  int priority;
};

template<int max_size, typename T>
class Treap_recursive : public Tree_normal<max_size, T, Treap_Node_recursive<T>>
{
  typedef Treap_Node_recursive<T> _Node;
  
  inline
  void
  __left_rotate(_Node*& current)
  {
    _Node* child = current->right;
    current->right = child->left;
    child->left = current;
    current = child;
  }
  
  inline
  void
  __right_rotate(_Node*& current)
  {
    _Node* child = current->left;
    current->left = child->right;
    child->right = current;
    current = child;
  }
  
  inline
  void
  __insert(_Node*& current, const T key)
  {
    if (current != this->__data)
    {
      if (key < current->key)
      {
        __insert(current->left, key);
        if (current->left->priority > current->priority)
          __right_rotate(current);
      }
      else if (key > current->key)
      {
        __insert(current->right, key);
        if (current->right->priority > current->priority)
          __left_rotate(current);
      }
    }
    else
    {
      current = ++this->__next;
      current->left = current->right = this->__data;
      current->key = key;
      current->priority = rand();
    }
  }
  
 public:  
  inline
  void
  insert(const T key)
  {
    __insert(this->__root, key);
  }
};

Treap_recursive<N, int> TR_rec;

template<typename T>
struct Treap_Node_parent
{
  Treap_Node_parent* left;
  Treap_Node_parent* right;
  Treap_Node_parent* parent;
  T key;
  int priority;
};

template<int max_size, typename T>
class Treap_iterative : public Tree_normal<max_size, T, Treap_Node_parent<T>>
{
  typedef Treap_Node_parent<T> _Node;
  
  inline
  void
  __left_rotate(_Node* x)
  {
    _Node* y = x->right;
    x->right = y->left;
    if (y->left != this->__data) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == this->__data) this->__root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    x->parent = y;
    y->left = x;
  }
  
  inline
  void
  __right_rotate(_Node* x)
  {
    _Node* y = x->left;
    x->left = y->right;
    if (y->right != this->__data) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == this->__data) this->__root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    x->parent = y;
    y->right = x;
  }
  
 public:
  inline
  void
  insert(const T key)
  {
    _Node* z = this->__root;
    _Node* p = this->__data;
    while (z != this->__data && z->key != key)
    {
      p = z;
      if (z->key < key) z = z->right;
      else z = z->left;
    }
    if (z == this->__data)
    {
      z = ++this->__next;
      z->left = z->right = this->__data;
      z->key = key;
      z->priority = rand();
      z->parent = p;
      if (p == this->__data) this->__root = z;
      else if (key < p->key) p->left = z;
      else p->right = z;
      while (p != this->__data && p->priority < z->priority)
      {
        if (z == p->left) __right_rotate(p);
        else __left_rotate(p);
        p = z->parent;
      }
    }
  }
};

Treap_iterative<N, int> TR_ite;

template<typename T>
struct Treap_Node_parent_indexed
{
  Treap_Node_parent_indexed* node[3];
  T key;
  int priority;
};

template<int max_size, typename T>
class Treap_iterative_indexed : public Tree_indexed<max_size, T, Treap_Node_parent_indexed<T>>
{
  typedef Treap_Node_parent_indexed<T> _Node;
  
  // 0 right
  // 1 left
  
  inline
  void
  __rotate(_Node* x, const int index)
  {
    _Node* y = x->node[index];
    x->node[index] = y->node[index ^ 1];
    if (y->node[index ^ 1] != this->__data) y->node[index ^ 1]->node[2] = x;
    y->node[2] = x->node[2];
    if (x->node[2] == this->__data) this->__root = y;
    else x->node[2]->node[x == x->node[2]->node[1]] = y;
    x->node[2] = y;
    y->node[index ^ 1] = x;
  }
  
 public:  
  inline
  void
  insert(const T key)
  {
    _Node* z = this->__root;
    _Node* p = this->__data;
    while (z != this->__data && z->key != key)
    {
      p = z;
      z = z->node[z->key < key];
    }
    if (z == this->__data)
    {
      z = ++this->__next;
      z->node[0] = z->node[1] = this->__data;
      z->key = key;
      z->priority = rand();
      z->node[2] = p;
      if (p == this->__data) this->__root = z;
      else p->node[key > p->key] = z;
      while (p != this->__data && p->priority < z->priority)
      {
        __rotate(p, z == p->node[1]);
        p = z->node[2];
      }
    }
  }
};

Treap_iterative_indexed<N, int> TR_ite_idx;

template<typename T>
struct BST_Node_parent
{
  BST_Node_parent* left;
  BST_Node_parent* right;
  BST_Node_parent* parent;
  T key;
};

template<int max_size, typename T>
class Splay_Tree_bottom_up : public Tree_normal<max_size, T, BST_Node_parent<T>>
{
  typedef BST_Node_parent<T> _Node;
  
  inline
  void
  __left_rotate(_Node* x)
  {
    _Node* y = x->right;
    x->right = y->left;
    if (y->left != this->__data) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == this->__data) this->__root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
  }
  
  inline
  void
  __right_rotate(_Node* x)
  {
    _Node* y = x->left;
    x->left = y->right;
    if (y->right != this->__data) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == this->__data) this->__root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->right = x;
    x->parent = y;
  }
  
  inline
  void
  __splay(_Node* x)
  {
    while (x->parent != this->__data)
    {
      if (x->parent->parent == this->__data)
      {
        if (x->parent->left == x) __right_rotate(x->parent);
        else __left_rotate(x->parent);
      }
      else if (x->parent->left == x && x->parent->parent->left == x->parent)
      {
        __right_rotate(x->parent->parent);
        __right_rotate(x->parent);
      }
      else if (x->parent->right == x && x->parent->parent->right == x->parent)
      {
        __left_rotate(x->parent->parent);
        __left_rotate(x->parent);
      }
      else if (x->parent->left == x && x->parent->parent->right == x->parent)
      {
        __right_rotate(x->parent);
        __left_rotate(x->parent);
      }
      else
      {
        __left_rotate(x->parent);
        __right_rotate(x->parent);
      }
    }
  }
  
 public:  
  inline
  void
  insert(const T key)
  {
    _Node* z = this->__root;
    _Node* p = this->__data;
    while (z != this->__data && z->key != key)
    {
      p = z;
      if (z->key < key) z = z->right;
      else z = z->left;
    }
    if (z == this->__data)
    {
      z = ++this->__next;
      z->key = key;
      z->left = z->right = this->__data;
      z->parent = p;
      if (p == this->__data) this->__root = z;
      else if (p->key < z->key) p->right = z;
      else p->left = z;
    }
    __splay(z);
  }  
};

Splay_Tree_bottom_up<N, int> ST_bu;

template<int max_size, typename T>
class Splay_Tree_top_down : public Tree_normal<max_size, T, BST_Node<T>>
{
  typedef BST_Node<T> _Node;
  
  inline
  void
  __left_rotate(_Node*& x)
  {
    _Node* y = x->right;
    x->right = y->left;
    y->left = x;
    x = y;
  }
  
  inline
  void
  __right_rotate(_Node*& x)
  {
    _Node* y = x->left;
    x->left = y->right;
    y->right = x;
    x = y;
  }
  
  inline
  void
  __splay(_Node*& x, const int key)
  {
    if (x == this->__data || x->key == key)
      return;
    if (x->key > key)
    {
      if (x->left == this->__data) return;
      if (x->left->key > key)
      {
        __splay(x->left->left, key);
        __right_rotate(x);
      }
      else if (x->left->key < key)
      {
        __splay(x->left->right, key);
        if (x->left->right != this->__data)
          __left_rotate(x->left);
      }
      if (x->left != this->__data)
        __right_rotate(x);
    }
    else
    {
      if (x->right == this->__data) return;
      if (x->right->key < key)
      {
        __splay(x->right->right, key);
        __left_rotate(x);
      }
      else if (x->right->key > key)
      {
        __splay(x->right->left, key);
        if (x->right->left != this->__data)
          __right_rotate(x->right);
      }
      if (x->right != this->__data)
        __left_rotate(x);
    }
  }
  
  inline
  void
  __new_node(_Node*& x, const T key)
  {
    x = ++this->__next;
    x->left = x->right = this->__data;
    x->key = key;
  }
  
  inline
  void
  __insert(_Node*& x, const T key)
  {
    if (x != this->__data)
    {
      __splay(x, key);
      if (x->key == key) return;
      _Node* y;
      __new_node(y, key);
      if (x->key > key)
      {
        y->right = x;
        y->left = x->left;
        x->left = this->__data;
      }
      else
      {
        y->left = x;
        y->right = x->right;
        x->right = this->__data;
      }
      x = y;
    }
    else
    {
      __new_node(x, key);
    }    
  }
  
 public:
  inline
  void
  insert(const T key)
  {
    __insert(this->__root, key);
  }
};

Splay_Tree_top_down<N, int> ST_td;

template<int max_size, typename T>
class Splay_Tree_top_down_original : public Tree_normal<max_size, T, BST_Node<T>>
{
  typedef BST_Node<T> _Node;
  
  inline
  _Node*
  __splay(_Node* x, const int key)
  {    
    if (x == this->__data) return x;
    _Node tmp;
    tmp.left = tmp.right = this->__data;
    _Node* l = &tmp;
    _Node* r = &tmp;
    while (1)
    {
      if (key < x->key)
      {
        if (x->left == this->__data) break;
        if (key < x->left->key)
        {
          _Node* y = x->left;
          x->left = y->right;
          x->right = x;
          x = y;
          if (x->left == this->__data) break;
        }
        r->left = x;
        r = x;
        x = x->left;
        r->left = this->__data;
      }
      else if (key > x->key)
      {
        if (x->right == this->__data) break;
        if (key > x->right->key)
        {
          _Node* y = x->right;
          x->right = y->left;
          y->left = x;
          x = y;
          if (x->right == this->__data) break;
        }
        l->right = x;
        l = x;
        x = x->right;
        l->right = this->__data;
      }
      else break;
    }
    l->right = x->left;
    r->left = x->right;
    x->left = tmp.right;
    x->right = tmp.left;
    return x;
  }
  
  inline
  _Node*
  __insert(_Node* x, const T key)
  {    
    if (x == this->__data)
    {
      _Node* y = ++this->__next;
      y->key = key;
      y->left = y->right = this->__data;
      return y;
    }
    x = __splay(x, key);
    if (key == x->key) return x;
    _Node* y = ++this->__next;
    y->key = key;
    if (key < x->key)
    {
      y->left = x->left;
      y->right = x;
      x->left = this->__data;
    }
    else
    {
      y->right = x->right;
      y->left = x;
      x->right = this->__data;
    }
    return y;
  }
  
 public:
  inline
  void
  insert(const T key)
  {
    this->__root = __insert(this->__root, key);
  }
};

Splay_Tree_top_down_original<N, int> ST_td_o;

void
test_treap_recursive()
{  
  int* b = new int[N];
  std::copy(arr, arr + N, b);
  tm.restart();
  for (int i = 0; i < N; ++i) TR_rec.insert(b[i]);
  printf("treap (recursive)             : %.2lf", tm.elapsed());
  printf("  avg H = %.2lf", TR_rec.total_height() * 1.0 / TR_rec.size());
  printf("  max H = %d\n", TR_rec.max_depth());
  delete[] b;
}

void
test_treap_iterative()
{
  int* b = new int[N];
  std::copy(arr, arr + N, b);
  tm.restart();
  for (int i = 0; i < N; ++i) TR_ite.insert(b[i]);
  printf("treap (iterative)             : %.2lf", tm.elapsed());
  printf("  avg H = %.2lf", TR_ite.total_height() * 1.0 / TR_ite.size());
  printf("  max H = %d\n", TR_ite.max_depth());
  delete[] b;
}

void
test_treap_iterative_indexed()
{  
  int* b = new int[N];
  std::copy(arr, arr + N, b);
  tm.restart();
  for (int i = 0; i < N; ++i) TR_ite_idx.insert(b[i]);
  printf("treap (iterative indexed)     : %.2lf", tm.elapsed());
  printf("  avg H = %.2lf", TR_ite_idx.total_height() * 1.0 / TR_ite_idx.size());
  printf("  max H = %d\n", TR_ite_idx.max_depth());
  delete[] b;
}

void
test_splay_tree_bottom_up()
{
  int* b = new int[N];
  std::copy(arr, arr + N, b);
  tm.restart();
  for (int i = 0; i < N; ++i) ST_bu.insert(b[i]);
  printf("splay tree (bottom up)        : %.2lf", tm.elapsed());
  printf("  avg H = %.2lf", ST_bu.total_height() * 1.0 / ST_bu.size());
  printf("  max H = %d\n", ST_bu.max_depth());
  delete[] b;
}

void
test_splay_tree_top_down()
{
  int* b = new int[N];
  std::copy(arr, arr + N, b);
  tm.restart();
  for (int i = 0; i < N; ++i) ST_td.insert(b[i]);
  printf("splay tree (top down)         : %.2lf", tm.elapsed());
  printf("  avg H = %.2lf", ST_td.total_height() * 1.0 / ST_td.size());
  printf("  max H = %d\n", ST_td.max_depth());
  delete[] b;
}

void
test_splay_tree_top_down_original()
{
  int* b = new int[N];
  std::copy(arr, arr + N, b);
  tm.restart();
  for (int i = 0; i < N; ++i) ST_td_o.insert(b[i]);
  printf("splay tree (top down origin)  : %.2lf", tm.elapsed());
  printf("  avg H = %.2lf", ST_td_o.total_height() * 1.0 / ST_td_o.size());
  printf("  max H = %d\n", ST_td_o.max_depth());
  //ST_td_o.inorder();
  delete[] b;
}


std::set<int> std_set;

void
test_std_set()
{
  int* b = new int[N];
  std::copy(arr, arr + N, b);
  tm.restart();
  for (int i = 0; i < N; ++i) std_set.insert(b[i]);
  printf("std::set                      : %.2lf\n", tm.elapsed());
  delete[] b;
}

template<int bit, int max>
void
test_radix_sort_bit()
{
  int* b = new int[N];
  int* radix = new int[N];
  std::copy(arr, arr + N, b);
  tm.restart();
  const int base = 1 << bit;
  for (int exp = 0; exp < max; exp += bit)
  {
    int bucket[base] = { 0 };
    for (int i = 0; i < N; ++i)
      ++bucket[(b[i] >> bit) & (base - 1)];
    for (int i = 1; i < base; ++i)
      bucket[i] += bucket[i - 1];
    for (int i = N - 1; i >= 0; --i)
      radix[--bucket[(b[i] >> bit) & (base - 1)]] = b[i];
    for (int i = 0; i < N; ++i)
      b[i] = radix[i] >> bit;
  }
  printf("radix sort %2d bit             : %.2lf\n", bit, tm.elapsed());
  delete[] b;
  delete[] radix;
}

template<int bit, int max>
void
test_radix_sort_bit_with_buffer()
{  
  int** buffer = new int*[2];
  buffer[0] = new int[N];
  buffer[1] = new int[N];
  std::copy(arr, arr + N, buffer[1]);
  tm.restart();
  const int base = 1 << bit;
  int f = 1;
  for (int exp = 0; exp < max; exp += bit)
  {
    int bucket[base] = { 0 };
    for (int i = 0; i < N; ++i)
      ++bucket[(buffer[f][i] >> exp) & (base - 1)];
    for (int i = 1; i < base; ++i)
      bucket[i] += bucket[i - 1];
    for (int i = N - 1; i >= 0; --i)
      buffer[f ^ 1][--bucket[(buffer[f][i] >> exp) & (base - 1)]] = buffer[f][i];
    f ^= 1;
  }
  printf("radix sort %2d bit with buffer : %.2lf\n", bit, tm.elapsed());
  delete[] buffer[0];
  delete[] buffer[1];
  delete[] buffer;
}

template<int digit, int max>
void
test_radix_sort_digit()
{
  int* b = new int[N];
  int* radix = new int[N];
  std::copy(arr, arr + N, b);
  tm.restart();
  const int base = digit == 1 ? 10 : digit == 2 ? 100 : digit == 3 ? 1000 : 10000;
  int exp = 1;
  while (max / exp > 0)
  {
    int bucket[base] = { 0 };
    for (int i = 0; i < N; ++i)
      ++bucket[(b[i] / exp) % base];
    for (int i = 1; i < base; ++i)
      bucket[i] += bucket[i - 1];
    for (int i = N - 1; i >= 0; --i)
      radix[--bucket[(b[i] / exp) % base]] = b[i];
    for (int i = 0; i < N; ++i)
      b[i] = radix[i];
    exp *= base;
  }
  printf("radix sort %d digit            : %.2lf\n", digit, tm.elapsed());
  delete[] b;
  delete[] radix;
}

void
test_std_sort() {
  int* b = new int[N];
  std::copy(arr, arr + N, b);
  tm.restart();
  std::sort(b, b + N);
  printf("std::sort                     : %.2lf\n", tm.elapsed());
  delete[] b;
}

void
test_std_stable_sort()
{
  int* b = new int[N];
  std::copy(arr, arr + N, b);
  tm.restart();
  std::stable_sort(b, b + N);
  printf("std::stable_sort              : %.2lf\n", tm.elapsed());
  delete[] b;
}

void
test_std_sort_heap()
{
  int* b = new int[N];
  std::copy(arr, arr + N, b);
  tm.restart();
  std::make_heap(b, b + N);
  std::sort_heap(b, b + N);
  printf("std::sort_heap                : %.2lf\n", tm.elapsed());
  delete[] b;
}

int
main()
{
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //srand(time(NULL));
  for (int i = 0; i < N; ++i)
  {
    arr[i] = generate(1, M);
    arr[i] += i * 10;
  }
  for (int i = 1; i << 1 < N; i += 2) std::swap(arr[i], arr[N - i - 1]);
  std::reverse(arr + (N >> 1), arr + N);
  test_treap_recursive();
  test_treap_iterative();
  test_treap_iterative_indexed();
  test_splay_tree_bottom_up();
  test_splay_tree_top_down();
  //test_splay_tree_top_down_original();
  test_std_set();
  test_radix_sort_bit<4, 32>();
  test_radix_sort_bit<8, 32>();
  test_radix_sort_bit<16, 32>();
  test_radix_sort_bit_with_buffer<4, 32>();
  test_radix_sort_bit_with_buffer<8, 32>();
  test_radix_sort_bit_with_buffer<16, 32>();
  test_radix_sort_digit<1, M>();
  test_radix_sort_digit<2, M>();
  test_radix_sort_digit<3, M>();
  test_radix_sort_digit<4, M>();
  test_std_sort();
  test_std_stable_sort();
  test_std_sort_heap();
}