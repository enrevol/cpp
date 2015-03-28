#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

const int N = 250010;
const int SQRT = 500;

struct point {
    int x, y;
} p[N];

vector<int> xs, ys;
vector<int> vert[N];
vector<int> small, large;
bool mark[N];
unordered_map<int, int> cnt[N];

void compress(vector<int>& v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
}

int main() {
//    freopen("in", "r", stdin);
//    freopen("out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i].x >> p[i].y;
        xs.push_back(p[i].x);
        ys.push_back(p[i].y);
    }
    compress(xs);
    compress(ys);
    for (int i = 1; i <= n; ++i) {
        p[i].x = lower_bound(xs.begin(), xs.end(), p[i].x) - xs.begin();
        p[i].y = lower_bound(ys.begin(), ys.end(), p[i].y) - ys.begin();
        vert[p[i].x].push_back(p[i].y);
    }
    for (int i = 0; i < int(xs.size()); ++i) {
        sort(vert[i].begin(), vert[i].end());
        if (vert[i].size() <= SQRT) {
            small.push_back(i);
        } else {
            large.push_back(i);
        }
    }
    cerr << "large = " << large.size() << '\n';
    cerr << "small = " << small.size() << '\n';
    long long answer = 0;
    for (int i = 0; i < int(large.size()); ++i) {
        const vector<int>& x1 = vert[large[i]];
        for (int y : x1) {
            mark[y] = true;
        }
        for (int j = 0; j < int(small.size()); ++j) {
            const vector<int>& x2 = vert[small[j]];
            int cnt = 0;
            for (int y : x2)
                if (mark[y])
                    ++cnt;
            answer += (long long)cnt * (cnt - 1) / 2;
        }
        for (int j = 0; j < int(large.size()) && large[j] < large[i]; ++j) {
            const vector<int>& x2 = vert[large[j]];
            int cnt = 0;
            for (int y : x2)
                if (mark[y])
                    ++cnt;
            answer += (long long)cnt * (cnt - 1) / 2;
        }
        for (int y : x1) {
            mark[y] = false;
        }
    }
    for (int i = 0; i < int(small.size()); ++i) {
        const vector<int>& x = vert[small[i]];
        for (int j = 0; j < int(x.size()); ++j)
            for (int k = j + 1; k < int(x.size()); ++k)
                ++cnt[x[j]][x[k]];
    }
    for (int i = 0; i < int(ys.size()); ++i) {
        for (auto p : cnt[i]) {
            int v = p.second;
            answer += (long long)v * (v - 1) / 2;
        }
    }
    cout << answer;
}