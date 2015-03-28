#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
 
const int N = 1010;
const int INF = 1e6;
const double EPS = 1e-8;
const double NO_INTERSECTION = 123456789;

int read() {
    bool minus = false;
    int result = 0;
    char ch = getchar_unlocked();
    for (;;) {
        if (ch == '-') break;
        if ('0' <= ch && ch <= '9') break;
        ch = getchar_unlocked();
    }
    if (ch == '-') {
        minus = true;
    } else {
        result = ch - '0';
    }
    for (;;) {
        ch = getchar_unlocked();
        if (ch < '0' || ch > '9') break;
        result = result * 10 + (ch - '0');
    }
    if (minus) {
        return -result;
    }
    return result;
}

double abs(double x) {
    return x >= 0 ? x : -x;
}

bool equal(double x, double y) {
    return abs(x - y) <= EPS;
}

int gcd(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

struct Point {
    int x, y;
} points[N];

struct Line {
    int a, b;
    long long c;
    int lower_y, upper_y;
    
    Line() { }
    
    // ax + by = c
    Line(int x1, int y1, int x2, int y2) {
        a = y2 - y1;
        b = x1 - x2;
        int g = gcd(a, b);
        if (g != 0) {
            a /= g;
            b /= g;
        }
        if (a < 0) {
            a = -a;
            b = -b;
        }
        c = (long long)a * x1 + (long long)b * y1;
    }
    
    double intersect(int y) const {
        if (lower_y <= y && y <= upper_y) {
            long long d = c - (long long)b * y;
            double result = double(d) / a;
            return result;
        }
        return NO_INTERSECTION;
    }
} lines[N];

struct Part {
    int lower_y, upper_y;
    double a, b;
    std::vector<double> upper, lower;
    
    void process() {
        std::sort(lower.begin(), lower.end());
        std::sort(upper.begin(), upper.end());
        for (int i = 1; i < int(lower.size()); i += 2) {
            double delta_upper = upper[i] - upper[i - 1];
            double delta_lower = lower[i] - lower[i - 1];
            if (equal(delta_upper, delta_lower)) {
                b += delta_upper;
            } else {
                a += (delta_upper - delta_lower) / (upper_y - lower_y);
                b += delta_lower;
            }
        }
    }
    
    double query(int y) const {
        double result = a * (y - lower_y) + b;
        return result;
    }
} parts[N];

std::vector<int> vals;
double pos[N];

int main() {
//    freopen("in", "r", stdin);
//    freopen("out", "w", stdout);
//    std::cin.tie(NULL);
//    std::ios::sync_with_stdio(false);
    int n = read();
    int m = read();
    vals.reserve(n);
    for (int i = 0; i < n; ++i) {
        points[i].x = read();
        points[i].y = read();
        vals.push_back(points[i].y);
    }
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        lines[i] = Line(points[i].x, points[i].y, points[j].x, points[j].y);
        lines[i].lower_y = std::min(points[i].y, points[j].y);
        lines[i].upper_y = std::max(points[i].y, points[j].y);
    }
    std::sort(vals.begin(), vals.end());
    vals.erase(std::unique(vals.begin(), vals.end()), vals.end());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < int(vals.size()); ++j) {
            pos[j] = lines[i].intersect(vals[j]);
        }
        for (int j = 0; j + 1 < int(vals.size()); ++j) {
            if (pos[j] != NO_INTERSECTION && pos[j + 1] != NO_INTERSECTION) {
                parts[j].lower.push_back(pos[j]);
                parts[j].upper.push_back(pos[j + 1]);
            }
        }
    }
    for (int i = 0; i + 1 < int(vals.size()); ++i) {
        parts[i].lower_y = vals[i];
        parts[i].upper_y = vals[i + 1];
        parts[i].process();
    }
    for (int i = 0; i < m; ++i) {
        int y = read();
        double answer = 0;
        if (vals.front() <= y && y <= vals.back()) {
            int part_id = -1;
            int low = 0;
            int high = vals.size() - 2;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (parts[mid].lower_y <= y) {
                    part_id = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            answer = parts[part_id].query(y);
        }
        printf("%.7lf\n", answer);
    }
}
