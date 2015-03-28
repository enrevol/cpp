#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>

const int N = 345678;

struct Point2D {    
    int x, y;
    
    Point2D(int x = 0, int y = 0) : x(x), y(y) { }    
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

bool ccw(const Point2D& a, const Point2D& b, const Point2D& c) {
    Vector3D ba(a.x - b.x, a.y - b.y, 1);
    Vector3D bc(c.x - b.x, c.y - b.y, 1);
    Vector3D cross = Vector3D::crossProduct(bc, ba);
    return cross.z > 0;
}

std::vector<Point2D> points;
std::vector<int> addOrders;

struct xCompare {
    bool operator()(int i, int j) {
        return points[i].x < points[j].x;
    }
};

struct yCompare {
    bool operator()(int i, int j) {
        return points[i].y < points[j].y;
    }
};

long long calc(const Point2D& a, const Point2D& b, const Point2D& c) {
    return (long long)a.y * b.x - (long long)a.x * b.y +
           (long long)b.y * c.x - (long long)b.x * c.y +
           (long long)c.y * a.x - (long long)c.x * a.y;
}

std::set<int, xCompare> xSet;
std::set<int, yCompare> ySet;
std::list<int>::iterator pointer[N];

int main() {
//    freopen("in", "r", stdin);
//    freopen("out", "w", stdout);
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        points.push_back(Point2D(x, y));
        xSet.insert(i);
        ySet.insert(i);
    }
    std::string ops;
    std::cin >> ops;
    for (char c : ops) {
        int p = -1;
        if (c == 'U') {
            p = *ySet.rbegin();
        } else if (c == 'D') {
            p = *ySet.begin();
        } else if (c == 'L') {
            p = *xSet.begin();
        } else {
            p = *xSet.rbegin();
        }
        assert(p != -1);
        ySet.erase(p);
        xSet.erase(p);
        addOrders.push_back(p);
    }
    long long area = 0;
    std::vector<long long> answer;
    int xMin = *xSet.begin();
    int xMax = *xSet.rbegin();
    int yMin = *ySet.begin();
    int yMax = *ySet.rbegin();
    std::list<int> convexHull;
    for (int p : xSet) {
        convexHull.push_front(p);
        pointer[p] = convexHull.begin();
    }
    auto next = [&] (std::list<int>::iterator iter) {
        ++iter;
        if (iter == convexHull.end()) {
            iter = convexHull.begin();
        }
        return iter;
    };
    auto prev = [&] (std::list<int>::iterator iter) {
        if (iter == convexHull.begin()) {
            iter = convexHull.end();
        }
        return --iter;
    };
    for (int i = addOrders.size() - 1; i >= 0; --i) {
        int p = addOrders[i];
        std::list<int>::iterator first, last;
        if (points[p].x < points[xMin].x) {
            if (points[p].y < points[yMin].y) {
                first = pointer[xMin];
                last = pointer[yMin];
            } else if (points[p].y > points[yMax].y) {
                first = pointer[yMax];
                last = pointer[xMin];
            } else {
                first = last = pointer[xMin];
            }
        } else if (points[p].x > points[xMax].x) {
            if (points[p].y < points[yMin].y) {
                first = pointer[yMin];
                last = pointer[xMax];
            } else if (points[p].y > points[yMax].y) {
                first = pointer[xMax];
                last = pointer[yMax];
            } else {
                first = last = pointer[xMax];
            }
        } else {
            if (points[p].y < points[yMin].y) {
                first = last = pointer[yMin];
            } else {
                first = last = pointer[yMax];
            }
        }
        if (points[p].x < points[xMin].x) {
            xMin = p;
        }
        if (points[p].x > points[xMax].x) {
            xMax = p;
        }
        if (points[p].y < points[yMin].y) {
            yMin = p;
        }
        if (points[p].y > points[yMax].y) {
            yMax = p;
        }
        while (ccw(points[p], points[*first], points[*prev(first)])) {
            first = prev(first);
        }
        while (ccw(points[*next(last)], points[*last], points[p])) {
            last = next(last);
        }
        for (auto iter = first; iter != last; iter = next(iter)) {
            long long subArea = calc(points[p], points[*iter], points[*next(iter)]);
            area = area + subArea;
        }
        for (auto iter = next(first); iter != last; ) {
            auto tmp = next(iter);
            convexHull.erase(iter);
            iter = tmp;
        }
        convexHull.insert(last, p);
        pointer[p] = --last;
        answer.push_back(area);
    }
    for (int i = answer.size() - 1; i >= 0; --i) {
        std::cout << answer[i] / 2;
        if (answer[i] % 2) {
            std::cout << ".5\n";
        } else {
            std::cout << ".0\n";
        }
    }
}
