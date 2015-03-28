#include <cassert>
#include <iostream>
#include <string>

const int N = 123456;

struct node {
    node *l, *r, *p, *c;
    int sz, pri, key;
    node() : l(nullptr), r(nullptr), p(nullptr), sz(1), pri(rand() << 16 | rand()) { }
};

node* root[N];

inline
void update(node* x) {
    if (x != nullptr) {
        x->sz = 1;
        if (x->l != nullptr) x->sz += x->l->sz;
        if (x->r != nullptr) x->sz += x->r->sz;
    }
}

void split(node* x, node*& l, node*& r, int p) {
    if (x == nullptr) {
        l = r = nullptr;
    } else {
        int cnt = 0;
        if (x->l != nullptr) cnt = x->l->sz;
        if (cnt >= p) {
            r = x;
            split(x->l, l, r->l, p);
            if (r->l != nullptr) r->l->p = r;
        } else {
            l = x;
            split(x->r, l->r, r, p - cnt - 1);
            if (l->r != nullptr) l->r->p = l;
        }
    }
    update(l);
    update(r);
}

void merge(node*& x, node* l, node* r) {
    if (l == nullptr) {
        x = r;
    } else if (r == nullptr) {
        x = l;
    } else if (l->pri > r->pri) {
        x = l;
        merge(x->r, l->r, r);
        if (x->r != nullptr) x->r->p = x;
    } else {
        x = r;
        merge(x->l, l, r->l);
        if (x->l != nullptr) x->l->p = x;
    }
    update(x);
}

int index(node* x) {
    assert(x != nullptr);
    int r = 1;
    if (x->l != nullptr) {
        r += x->l->sz;
    }
    while (x->p != nullptr) {
        if (x == x->p->r) {
            ++r;
            if (x->p->l != nullptr) {
                r += x->p->l->sz;
            }
        }
        x = x->p;
    }
    return r;
}

int find(int p) {
    node* x = root[0];
    for (;;) {
        int cnt = 0;
        if (x->l != nullptr) {
            cnt += x->l->sz;
        }
        if (cnt + 1 == p)
            return x->key;
        if (p <= cnt) {
            x = x->l;
        } else {
            p = p - cnt - 1;
            x = x->r;
        }
    }
    assert(false);
}

int count(int v, int p) {
    int r = 0;
    node* x = root[v];
    while (x != nullptr) {
        int i = index(x->c);
        if (p < i) {
            x = x->l;
        } else {
            ++r;
            if (x->l != nullptr) {
                r += x->l->sz;
            }
            if (i == p) break;
            x = x->r;
        }
    }
    return r;
}

void insert(int p, int v) {    
    int z = count(v, p);
    node* d = nullptr;
    node* e = nullptr;
    split(root[v], d, e, z);
    node* f = new node();
    merge(d, d, f);
    merge(root[v], d, e);
    node* a = nullptr;
    node* b = nullptr;
    split(root[0], a, b, p);
    node* c = new node();    
    merge(a, a, c);
    merge(root[0], a, b);
    c->key = f->key = v;
    f->c = c;
    c->c = f;
}

void erase(int p) {
    int v = find(p);
    int z = count(v, p);
    node* d = nullptr;
    node* e = nullptr;
    node* f = nullptr;
    split(root[v], d, e, z - 1);
    split(e, f, e, 1);
    merge(root[v], d, e);
    node* a = nullptr;
    node* b = nullptr;
    node* c = nullptr;
    split(root[0], a, b, p - 1);
    split(b, c, b, 1);
    merge(root[0], a, b);
}

int main() {
//    freopen("input.txt", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::fill(root, root + N, nullptr);
    for (int i = 1; i <= n; ++i) {
        int a;
        std::cin >> a;
        insert(i - 1, a);
    }
    while (q--) {
        int type, f, t, p, v;
        std::cin >> type;
        if (type == 1) {
            std::cin >> p >> v;
            insert(p, v);
        } else if (type == 2) {
            std::cin >> p >> v;
            erase(p);
            insert(p - 1, v);
        } else {
            std::cin >> f >> t >> v;
            std::cout << count(v, t) - count(v, f - 1) << '\n';
        }
    }
}