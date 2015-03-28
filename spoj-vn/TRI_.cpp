#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>

const int N = 123456;

struct Point2D {    
    int x, y;
    
    Point2D(int x = 0, int y = 0) : x(x), y(y) { }    
};

struct Line2D {
    int a, b;
    long long c;
    
    Line2D(const Point2D& u, const Point2D& v) {
        a = v.y - u.y;
        b = u.x - v.x;
        int g = std::__gcd(a, b);
        if (g > 0) {
            a /= g;
            b /= g;
        }
        c = (long long)a * u.x + (long long)b * u.y;
    }
};

struct Vector2D {
    int x, y;
    
    Vector2D(int x = 0, int y = 0) : x(x), y(y) { }
    
    Vector2D(const Point2D& a, const Point2D& b) : x(b.x - a.x), y(b.y - a.y) { }
};

struct Vector3D {
    long long x, y, z;
    
    Vector3D(long long x = 0, long long y = 0, long long z = 0) : x(x), y(y), z(z) { }
    
    static
    Vector3D crossProduct(const Vector3D& u, const Vector3D& v) {
        long long x = u.y * v.z - u.z * v.y;
        long long y = u.z * v.x - u.x * v.z;
        long long z = u.x * v.y - u.y * v.x;
        return Vector3D(x, y, z);
    }
};

std::vector<Point2D> monotoneChain(std::vector<Point2D> input) {
    int n = static_cast<int>(input.size());
    if (n == 1) return input;
    std::sort(input.begin(), input.end(), [] (const Point2D& a, const Point2D& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    } );
    auto helper = [] (const Point2D& a, const Point2D& b, const Point2D& c) {
        Vector3D ba(a.x - b.x, a.y - b.y, 1);
        Vector3D bc(c.x - b.x, c.y - b.y, 1);
        Vector3D cross = Vector3D::crossProduct(bc, ba);
        return cross.z > 0;
    };
    std::vector<Point2D> lowerHull, upperHull;
    for (int i = 0; i < n; ++i) {
        while (lowerHull.size() > 1 && !helper(lowerHull[lowerHull.size() - 2], lowerHull[lowerHull.size() - 1], input[i])) {
            lowerHull.pop_back();
        }
        lowerHull.push_back(input[i]);
    }
    for (int i = n - 1; i >= 0; --i) {
        while (upperHull.size() > 1 && !helper(upperHull[upperHull.size() - 2], upperHull[upperHull.size() - 1], input[i])) {
            upperHull.pop_back();
        }
        upperHull.push_back(input[i]);
    }
    lowerHull.pop_back();
    upperHull.pop_back();
    std::vector<Point2D> result;
    result.insert(result.end(), lowerHull.begin(), lowerHull.end());
    result.insert(result.end(), upperHull.begin(), upperHull.end());
    return result;
}

struct SegmentTree {
    struct node {
        node *left, *right;
        std::vector<Point2D>::iterator topmost, rightmost;
        std::vector<Point2D> convexHull;
    };
    
    node* root;
    
    using _Iter = std::vector<Point2D>::const_iterator;
    
    void build(node* x, _Iter first, _Iter last) {
        int count = last - first;
        if (count > 1) {
            _Iter middle = first + count / 2;
            build(x->left = new node(), first, middle);
            build(x->right = new node(), middle, last);
        }
        std::vector<Point2D> points(first, last);
        x->convexHull = monotoneChain(points);
        x->topmost = x->rightmost = x->convexHull.begin();
        for (auto iter = x->convexHull.begin(); iter != x->convexHull.end(); ++iter) {
            if (iter->y > x->topmost->y || (iter->y == x->topmost->y && iter->x < x->topmost->x)) {
                x->topmost = iter;
            }
            if (iter->x > x->rightmost->x || (iter->x == x->rightmost->x && iter->y < x->rightmost->y)) {
                x->rightmost = iter;
            }
        }
        if (x->rightmost == x->topmost) {
            if (x->rightmost != x->convexHull.begin()) {
                --x->rightmost;
            } else if (x->topmost + 1 != x->convexHull.end()) {
                ++x->topmost;
            }
        }
    }
    
    void build(const std::vector<Point2D>& input) {
        root = new node();
        build(root, input.begin(), input.end());
    }
    
    bool query(node* x, _Iter first, _Iter last, _Iter qFirst, _Iter qLast, const Line2D& line) const {
        if (qFirst <= first && last <= qLast) {
            auto evaluate = [&line] (const Point2D& p) {
                return (long long)line.a * p.x + (long long)line.b * p.y - line.c;
            };
            if (evaluate(*x->topmost) < 0 || evaluate(*x->rightmost) < 0) {
                return true;
            }
            int size = x->convexHull.size();
            int low = x->topmost - x->convexHull.begin();
            int high = x->rightmost - x->convexHull.begin();
            while (low != high) {
                int diff = high - low;
                if (diff < 0) diff += size;
                int mLow = low + diff / 3;
                if (mLow >= size) mLow -= size;
                int mHigh = high - diff / 3;
                if (mHigh < 0) mHigh += size;
                long long evalLow = evaluate(x->convexHull[mLow]);
                long long evalHigh = evaluate(x->convexHull[mHigh]);
                if (evalLow < 0 || evalHigh < 0) {
                    return true;
                }
                if (evalLow < evalHigh) {
                    high = mHigh - 1;
                    if (high < 0) high += size;
                } else {
                    low = mLow + 1;
                    if (low >= size) low -= size;
                }
            }
            return false;
        }
        int count = last - first;
        _Iter middle = first + count / 2;
        if (qLast <= middle) return query(x->left, first, middle, qFirst, qLast, line);
        if (qFirst >= middle) return query(x->right, middle, last, qFirst, qLast, line);
        return query(x->left, first, middle, qFirst, qLast, line) || query(x->right, middle, last, qFirst, qLast, line);
    }
    
    bool query(_Iter qf, _Iter qt, const std::vector<Point2D>& input, const Line2D& line) const {
        return query(root, input.begin(), input.end(), qf, qt, line);
    }
} T;

int main() {
//    freopen("in", "r", stdin);
//    freopen("out", "w", stdout);
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;
    std::vector<Point2D> points;
    for (int i = 1; i <= n; ++i) {
        int x, y;
        std::cin >> x >> y;
        points.push_back(Point2D(x, y));
    }
    auto cmp = [] (const Point2D& a, const Point2D& b) {
//        a.y / a.x < b.y / b.x;
        return (long long)a.y * b.x < (long long)b.y * a.x;
    };
    std::sort(points.begin(), points.end(), cmp);
    T.build(points);
    while (m--) {
        Point2D p1, p2;
        std::cin >> p1.x >> p1.y >> p2.x >> p2.y;
        if (cmp(p2, p1)) {
            std::swap(p1, p2);
        }
        auto i1 = std::lower_bound(points.begin(), points.end(), p1, cmp);
        auto i2 = std::upper_bound(points.begin(), points.end(), p2, cmp);
        bool answer = T.query(i1, i2, points, Line2D(p1, p2));
        std::cout << (answer ? 'Y' : 'N') << '\n';
    }
}
