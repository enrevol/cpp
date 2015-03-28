#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 100010;
const int INF = 0x4000000;

struct node {
    node *left, *right;
    int v, sum, best;
} pool[N * 150];

node* avail = pool + 2;
pair<int, int> nodes[50];
int cnt;

void modify(node*& x, int v, int f, int t) {
    if (x == nullptr) {
        x = avail++;
        x->v = INF;
    }
    x->sum = (t - f + 1) * v;
    if (v >= 0) {
        x->best = x->sum;
    } else {
        x->best = v;
    }
    x->v = v;
}

void push(node* x, int f, int t) {
    if (x->v != INF) {
        int m = (f + t) / 2;
        modify(x->left, x->v, f, m);
        modify(x->right, x->v, m + 1, t);
        x->v = INF;
    }
}

void update(node* x) {
    if (x->left == nullptr) {
        x->sum = x->right->sum;
        x->best = x->right->best;
    } else if (x->right == nullptr) {
        x->sum = x->left->sum;
        x->best = x->left->best;
    } else {
        x->sum = x->left->sum + x->right->sum;
        x->best = max(x->left->best, x->left->sum + x->right->best);
    }
}

void update(node*& x, int f, int t, int qf, int qt, int v) {
    if (x == nullptr) {
        x = avail++;
    }
    push(x, f, t);
    if (qf <= f && t <= qt) {
        modify(x, v, f, t);
    } else {
        int m = (f + t) / 2;
        if (qf < m + 1) update(x->left, f, m, qf, qt, v);
        if (qt > m) update(x->right, m + 1, t, qf, qt, v);
        update(x);
    }
}

void query(node* x, int f, int t, int qf, int qt) {
    if (x == nullptr) return;
    push(x, f, t);
    if (qf <= f && t <= qt) {
        nodes[cnt++] = make_pair(x->sum, x->best);
        return;
    }
    int m = (f + t) / 2;
    if (qt < m + 1) {
        query(x->left, f, m, qf, qt);
    } else if (qf > m) {
        query(x->right, m + 1, t, qf, qt);
    } else {
        query(x->left, f, m, qf, qt);
        query(x->right, m + 1, t, qf, qt);
    }
}

int main() {
//    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    char type;
    node* root = nullptr;
    while (cin >> type && type != 'E') {
        if (type == 'I') {
            int f, t, v;
            cin >> f >> t >> v;
            update(root, 1, n, f, t, v);
        } else {
            int h;
            cin >> h;
            int answer = 0;
            for (int low = 1, high = n; low <= high; ) {
                int mid = (low + high) / 2;
                nodes[0].first = nodes[0].second = 0;
                cnt = 1;
                query(root, 1, n, 1, mid);
                for (int i = 1; i < cnt; ++i) {
                    nodes[0].second = max(nodes[0].second, nodes[0].first + nodes[i].second);
                    nodes[0].first += nodes[i].first;
                }
                if (nodes[0].second <= h) {
                    answer = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            cout << answer << '\n';
        }
    }
}
