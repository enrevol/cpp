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
} __tm;

typedef std::pair<int, int> p2;

const int N = 2e6; // number of elements
const int M = 1e9; // elements range [0..M-1]

int __arr[N];

template<typename _T>
class _BST
{
  struct _Node
  {
    _Node* __left;
    _Node* __right;
    _T __key;
  };
  
  _Node* __data;
  _Node* __next;
  _Node* __root;
 
 public:
  _BST()
  {
    __data = new _Node[N + 1];
    __next = __root = __data;
    __data->__left = __data->__right = __data;
  }
  
  ~_BST()
  {
    delete[] __data;
  }  
  
  inline
  void
  insert(const _T __key)
  {
    _Node* __z = __root;
    _Node* __p = __data;
    while (__z != __data && __z->__key != __key)
    {
      __p = __z;
      if (__key < __z->__key) __z = __z->__left;
      else __z = __z->__right;
    }
    if (__z == __data)
    {
      __z = ++__next;
      __z->__key = __key;
      __z->__left = __z->__right = __data;
      if (__p == __data) __root = __z;
      else if (__p->__key < __z->__key) __p->__right = __z;
      else __p->__left = __z;
    }
  }
};

_BST<int> __nbs_tree;

template<typename _T>
class _Treap
{
  struct _Node
  {
    _Node* __left;
    _Node* __right;
    int __priority;
    _T __key;
  };
  
  _Node* __data;
  _Node* __next;
  _Node* __root;
  
  inline
  void
  __left_rotate(_Node*& __current)
  {
    _Node* __child = __current->__right;
    __current->__right = __child->__left;
    __child->__left = __current;
    __current = __child;
  }
  
  inline
  void
  __right_rotate(_Node*& __current)
  {
    _Node* __child = __current->__left;
    __current->__left = __child->__right;
    __child->__right = __current;
    __current = __child;
  }
  
  inline
  void
  __insert(_Node*& __current, const _T __key)
  {
    if (__current != __data)
    {
      if (__key < __current->__key)
      {
        __insert(__current->__left, __key);
        if (__current->__left->__priority > __current->__priority)
          __right_rotate(__current);
      }
      else if (__key > __current->__key)
      {
        __insert(__current->__right, __key);
        if (__current->__right->__priority > __current->__priority)
          __left_rotate(__current);
      }
    }
    else
    {
      __current = ++__next;
      __current->__left = __current->__right = __data;
      __current->__key = __key;
      __current->__priority = rand();
    }
  }
  
  inline
  void
  __inorder(const _Node* __current)
  {
    if (__current->__left != __data)
      __inorder(__current->__left);
    printf("%d\n", __current->__key);
    if (__current->__right != __data)
      __inorder(__current->__right);
  }
  
 public:
  _Treap()
  {
    __data = new _Node[N + 1];
    __next = __root = __data;
  }
  
  ~_Treap()
  {
    delete[] __data;
  }
  
  inline
  void
  insert(const _T __key)
  {
    __insert(__root, __key);
  }
  
  inline
  void
  inorder()
  {
    puts("-----");
    __inorder(__root);
  }
};

_Treap<int> __T_1;

template<typename _T>
class _Treap_iterative
{
  struct _Node
  {
    _Node* __left;
    _Node* __right;
    _Node* __parent;
    int __priority;
    _T __key;
  };
  
  _Node* __data;
  _Node* __next;
  _Node* __root;
  
  inline
  void
  __left_rotate(_Node* __x)
  {
    _Node* __y = __x->__right;
    __x->__right = __y->__left;
    if (__y->__left != __data) __y->__left->__parent = __x;
    __y->__parent = __x->__parent;
    if (__x->__parent == __data) __root = __y;
    else if (__x == __x->__parent->__left) __x->__parent->__left = __y;
    else assert(__x == __x->__parent->__right), __x->__parent->__right = __y;
    __x->__parent = __y;
    __y->__left = __x;
  }
  
  inline
  void
  __right_rotate(_Node* __x)
  {
    _Node* __y = __x->__left;
    __x->__left = __y->__right;
    if (__y->__right != __data) __y->__right->__parent = __x;
    __y->__parent = __x->__parent;
    if (__x->__parent == __data) __root = __y;
    else if (__x == __x->__parent->__left) __x->__parent->__left = __y;
    else assert(__x == __x->__parent->__right), __x->__parent->__right = __y;
    __x->__parent = __y;
    __y->__right = __x;
  }
  
  inline
  void
  __inorder(const _Node* __current)
  {
    if (__current->__left != __data)
      __inorder(__current->__left);
    printf("%d\n", __current->__key);
    if (__current->__right != __data)
      __inorder(__current->__right);
  }
  
 public:
  _Treap_iterative()
  {
    __data = new _Node[N + 5];
    __next = __root = __data;
    __data->__left = __data->__right = __data->__parent = __data;
  }
  
  ~_Treap_iterative()
  {
    delete[] __data;
  }
  
  inline
  void
  insert(const _T __key)
  {
    _Node* __z = __root;
    _Node* __p = __data;
    while (__z != __data && __z->__key != __key)
    {
      __p = __z;
      if (__z->__key < __key) __z = __z->__right;
      else __z = __z->__left;
    }
    if (__z == __data)
    {
      __z = ++__next;
      __z->__left = __z->__right = __data;
      __z->__key = __key;
      __z->__priority = rand();
      __z->__parent = __p;
      if (__p == __data) __root = __z;
      else if (__key < __p->__key) __p->__left = __z;
      else __p->__right = __z;
      while (__p != __data && __p->__priority < __z->__priority)
      {
        if (__z == __p->__left) __right_rotate(__p);
        else __left_rotate(__p);
        __p = __z->__parent;
      }
    }
  }
    
  inline
  void
  inorder()
  {
    puts("-----");
    __inorder(__root);
  }
};

_Treap_iterative<int> __T_2;

template<typename _T>
class _Treap_iterative_indexed
{
  struct _Node
  {
    _Node* __node[3]; // left right parent
    int __priority;
    _T __key;
  };
  
  _Node* __data;
  _Node* __next;
  _Node* __root;
  
  // 0 right
  // 1 left
  
  inline
  void
  __rotate(_Node* __x, const int index)
  {
    _Node* __y = __x->__node[index];
    __x->__node[index] = __y->__node[index ^ 1];
    if (__y->__node[index ^ 1] != __data) __y->__node[index ^ 1]->__node[2] = __x;
    __y->__node[2] = __x->__node[2];
    if (__x->__node[2] == __data) __root = __y;
    else if (__x == __x->__node[2]->__node[0]) __x->__node[2]->__node[0] = __y;
    else assert(__x == __x->__node[2]->__node[1]), __x->__node[2]->__node[1] = __y;
    __x->__node[2] = __y;
    __y->__node[index ^ 1] = __x;
  }
  
  inline
  void
  __inorder(const _Node* __current)
  {
    if (__current->__node[0] != __data)
      __inorder(__current->__node[0]);
    printf("%d\n", __current->__key);
    if (__current->__node[1] != __data)
      __inorder(__current->__node[1]);
  }
  
 public:
  _Treap_iterative_indexed()
  {
    __data = new _Node[N + 5];
    __next = __root = __data;
    __data->__node[0] = __data->__node[1] = __data->__node[2] = __data;
  }
  
  ~_Treap_iterative_indexed()
  {
    delete[] __data;
  }
  
  inline
  void
  insert(const _T __key)
  {
    _Node* __z = __root;
    _Node* __p = __data;
    while (__z != __data && __z->__key != __key)
    {
      __p = __z;
      __z = __z->__node[__z->__key < __key];
    }
    if (__z == __data)
    {
      __z = ++__next;
      __z->__node[0] = __z->__node[1] = __data;
      __z->__key = __key;
      __z->__priority = rand();
      __z->__node[2] = __p;
      if (__p == __data) __root = __z;
      else __p->__node[__key > __p->__key] = __z;
      while (__p != __data && __p->__priority < __z->__priority)
      {
        __rotate(__p, __z == __p->__node[1]);
        __p = __z->__node[2];
      }
    }
  }
    
  inline
  void
  inorder()
  {
    puts("-----");
    __inorder(__root);
  }
};

_Treap_iterative_indexed<int> __T_3;

template<typename _T>
class _Splay_Tree
{
  struct _Node
  {
    _Node* __left;
    _Node* __right;
    _Node* __parent;
    _T __key;
  };
  
  _Node* __data;
  _Node* __next;
  _Node* __root;
  
  inline
  void
  __left_rotate(_Node* __x)
  {
    _Node* __y = __x->__right;
    __x->__right = __y->__left;
    if (__y->__left != __data) __y->__left->__parent = __x;
    __y->__parent = __x->__parent;
    if (__x->__parent == __data) __root = __y;
    else if (__x == __x->__parent->__left) __x->__parent->__left = __y;
    else __x->__parent->__right = __y;
    __y->__left = __x;
    __x->__parent = __y;
  }
  
  inline
  void
  __right_rotate(_Node* __x)
  {
    _Node* __y = __x->__left;
    __x->__left = __y->__right;
    if (__y->__right != __data) __y->__right->__parent = __x;
    __y->__parent = __x->__parent;
    if (__x->__parent == __data) __root = __y;
    else if (__x == __x->__parent->__left) __x->__parent->__left = __y;
    else __x->__parent->__right = __y;
    __y->__right = __x;
    __x->__parent = __y;
  }
  
  inline
  void
  __splay(_Node* __x)
  {
    while (__x->__parent != __data)
    {
      if (__x->__parent->__parent == __data)
      {
        if (__x->__parent->__left == __x) __right_rotate(__x->__parent);
        else __left_rotate(__x->__parent);
      }
      else if (__x->__parent->__left == __x && __x->__parent->__parent->__left == __x->__parent)
      {
        __right_rotate(__x->__parent->__parent);
        __right_rotate(__x->__parent);
      }
      else if (__x->__parent->__right == __x && __x->__parent->__parent->__right == __x->__parent)
      {
        __left_rotate(__x->__parent->__parent);
        __left_rotate(__x->__parent);
      }
      else if (__x->__parent->__left == __x && __x->__parent->__parent->__right == __x->__parent)
      {
        __right_rotate(__x->__parent);
        __left_rotate(__x->__parent);
      }
      else
      {
        __left_rotate(__x->__parent);
        __right_rotate(__x->__parent);
      }
    }
  }
  
  inline
  void
  __inorder(const _Node* __current)
  {
    if (__current->__left != __data)
      __inorder(__current->__left);
    printf("%d\n", __current->__key);
    if (__current->__right != __data)
      __inorder(__current->__right);
  }
  
 public:
  _Splay_Tree()
  {
    __data = new _Node[N + 1];
    __root = __next = __data;
    __data->__left = __data->__right = __data->__parent = __data;
  }
  
  ~_Splay_Tree()
  {
    delete[] __data;
  }
  
  inline
  void
  insert(const _T __key)
  {
    _Node* __z = __root;
    _Node* __p = __data;
    while (__z != __data && __z->__key != __key)
    {
      __p = __z;
      if (__z->__key < __key) __z = __z->__right;
      else __z = __z->__left;
    }
    if (__z == __data)
    {
      __z = ++__next;
      __z->__key = __key;
      __z->__left = __z->__right = __data;
      __z->__parent = __p;
      if (__p == __data) __root = __z;
      else if (__p->__key < __z->__key) __p->__right = __z;
      else __p->__left = __z;
      //__splay(__z);
    }
    __splay(__z);
  }
  
  inline
  void
  inorder()
  {
    puts("-----");
    __inorder(__root);
  }
};

_Splay_Tree<int> __ST;

void
__bst()
{
  int* __b = new int[N];
  std::copy(__arr, __arr + N, __b);
  __tm.restart();
  for (int __i = 0; __i < N; ++__i)
    __nbs_tree.insert(__b[__i]);
  printf("bst                           : %.2lf\n", __tm.elapsed());
  delete[] __b;
}

void
__treap()
{
  
  int* __b = new int[N];
  std::copy(__arr, __arr + N, __b);
  __tm.restart();
  for (int __i = 0; __i < N; ++__i)
    __T_1.insert(__b[__i]);
  printf("treap                         : %.2lf\n", __tm.elapsed());
  //__T_1.inorder();
  delete[] __b;
}

void
__treap_iterative()
{
  
  int* __b = new int[N];
  std::copy(__arr, __arr + N, __b);
  __tm.restart();
  for (int __i = 0; __i < N; ++__i)
    __T_2.insert(__b[__i]);
  printf("treap (iterative)             : %.2lf\n", __tm.elapsed());
  //__T_2.inorder();
  delete[] __b;
}

void
__treap_iterative_indexed()
{
  
  int* __b = new int[N];
  std::copy(__arr, __arr + N, __b);
  __tm.restart();
  for (int __i = 0; __i < N; ++__i)
    __T_3.insert(__b[__i]);
  printf("treap (iterative) + indexed   : %.2lf\n", __tm.elapsed());
  //__T_3.inorder();
  delete[] __b;
}

void
__splay_tree()
{
  int* __b = new int[N];
  std::copy(__arr, __arr + N, __b);
  __tm.restart();
  for (int __i = 0; __i < N; ++__i)
    __ST.insert(__b[__i]);
  printf("splay tree                    : %.2lf\n", __tm.elapsed());
  //__ST.inorder();
  delete[] __b;
}

std::set<int> __set;

void
__std_set()
{
  int* __b = new int[N];
  std::copy(__arr, __arr + N, __b);
  __tm.restart();
  for (int __i = 0; __i < N; ++__i)
    __set.insert(__b[__i]);
  printf("std::set                      : %.2lf\n", __tm.elapsed());
  delete[] __b;
}

template<int __bit, int __max>
void
__radix_sort_bit()
{
  int* __b = new int[N];
  int* __radix = new int[N];
  std::copy(__arr, __arr + N, __b);
  __tm.restart();
  const int __base = 1 << __bit;
  for (int __exp = 0; __exp < __max; __exp += __bit)
  {
    int __bucket[__base] = { 0 };
    for (int __i = 0; __i < N; ++__i)
      ++__bucket[(__b[__i] >> __bit) & (__base - 1)];
    for (int __i = 1; __i < __base; ++__i)
      __bucket[__i] += __bucket[__i - 1];
    for (int __i = N - 1; __i >= 0; --__i)
      __radix[--__bucket[(__b[__i] >> __bit) & (__base - 1)]] = __b[__i];
    for (int __i = 0; __i < N; ++__i)
      __b[__i] = __radix[__i] >> __bit;
  }
  printf("radix sort %2d bit             : %.2lf\n", __bit, __tm.elapsed());
  delete[] __b;
  delete[] __radix;
}

template<int __bit, int __max>
void
__radix_sort_bit_with_buffer()
{  
  int** __buffer = new int*[2];
  __buffer[0] = new int[N];
  __buffer[1] = new int[N];
  std::copy(__arr, __arr + N, __buffer[1]);
  __tm.restart();
  const int __base = 1 << __bit;
  int __f = 1;
  for (int __exp = 0; __exp < __max; __exp += __bit)
  {
    int __bucket[__base] = { 0 };
    for (int __i = 0; __i < N; ++__i)
      ++__bucket[(__buffer[__f][__i] >> __exp) & (__base - 1)];
    for (int __i = 1; __i < __base; ++__i)
      __bucket[__i] += __bucket[__i - 1];
    for (int __i = N - 1; __i >= 0; --__i)
      __buffer[__f ^ 1][--__bucket[(__buffer[__f][__i] >> __exp) & (__base - 1)]] = __buffer[__f][__i];
    __f ^= 1;
  }
  printf("radix sort %2d bit with buffer : %.2lf\n", __bit, __tm.elapsed());
  delete[] __buffer[0];
  delete[] __buffer[1];
  delete[] __buffer;
}

template<int __digit, int __max>
void
__radix_sort_digit()
{
  int* __b = new int[N];
  int* __radix = new int[N];
  std::copy(__arr, __arr + N, __b);
  __tm.restart();
  const int __base = __digit == 1 ? 10 : __digit == 2 ? 100 : __digit == 3 ? 1000 : 10000;
  int __exp = 1;
  while (__max / __exp > 0)
  {
    int __bucket[__base] = { 0 };
    for (int __i = 0; __i < N; ++__i)
      ++__bucket[(__b[__i] / __exp) % __base];
    for (int __i = 1; __i < __base; ++__i)
      __bucket[__i] += __bucket[__i - 1];
    for (int __i = N - 1; __i >= 0; --__i)
      __radix[--__bucket[(__b[__i] / __exp) % __base]] = __b[__i];
    for (int __i = 0; __i < N; ++__i)
      __b[__i] = __radix[__i];
    __exp *= __base;
  }
  printf("radix sort %d digit            : %.2lf\n", __digit, __tm.elapsed());
  delete[] __b;
  delete[] __radix;
}

void
__std_sort() {
  int* __b = new int[N];
  std::copy(__arr, __arr + N, __b);
  __tm.restart();
  std::sort(__b, __b + N);
  printf("std::sort                     : %.2lf\n", __tm.elapsed());
  delete[] __b;
}

void
__std_stable_sort()
{
  int* __b = new int[N];
  std::copy(__arr, __arr + N, __b);
  __tm.restart();
  std::stable_sort(__b, __b + N);
  printf("std::stable_sort              : %.2lf\n", __tm.elapsed());
  delete[] __b;
}

void
__std_sort_heap()
{
  int* __b = new int[N];
  std::copy(__arr, __arr + N, __b);
  __tm.restart();
  std::make_heap(__b, __b + N);
  std::sort_heap(__b, __b + N);
  printf("std::sort_heap                : %.2lf\n", __tm.elapsed());
  delete[] __b;
}

void
__insertion_sort()
{
  int* __b = new int[N];
  std::copy(__arr, __arr + N, __b);
  std::vector<int> __vect;  
  __tm.restart();
  __vect.reserve(N);
  for (int __i = 0; __i < N; ++__i)
  {
    __typeof(__vect.begin()) __t = std::lower_bound(__vect.begin(), __vect.end(), __arr[__i]);
    __vect.insert(__t, __arr[__i]);
  }
  printf("insertion sort                : %.2lf\n", __tm.elapsed());
  delete[] __b;
}

int
main()
{
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  srand(time(NULL));
  for (int __i = 0; __i < N; ++__i)
  {
    __arr[__i] = (1ll * rand() * rand() * rand() * rand()) % M;
    //__arr[__i] = __i;
  }
  //for (int __i = 1; __i << 1 < N; __i += 2) std::swap(__arr[__i], __arr[N - __i - 1]);
  //__insertion_sort();  
  __treap();
  __treap_iterative();
  __treap_iterative_indexed();
  __splay_tree();
  __std_set();
  //__bst();
  __radix_sort_bit<4, 32>();
  __radix_sort_bit<8, 32>();
  __radix_sort_bit<16, 32>();
  __radix_sort_bit_with_buffer<4, 32>();
  __radix_sort_bit_with_buffer<8, 32>();
  __radix_sort_bit_with_buffer<16, 32>();
  __radix_sort_digit<1, M>();
  __radix_sort_digit<2, M>();
  __radix_sort_digit<3, M>();
  __radix_sort_digit<4, M>();
  __std_sort();
  __std_stable_sort();
  __std_sort_heap();
}