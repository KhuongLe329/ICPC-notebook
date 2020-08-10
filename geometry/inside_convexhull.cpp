///curling-usaco
#include <bits/stdc++.h>
#define pb          emplace_back
#define ll          long long
#define fi          first
#define se          second
#define mp          make_pair
#define int         int64_t

using namespace std;

const int N = int(1e5) + 1;
typedef pair<int, int> pii;

struct TPoint {
    int x, y;
    TPoint() {x = y = 0;}
    TPoint(int x, int y): x(x), y(y) {}

    TPoint operator+ (const TPoint& other) const& {return TPoint(x + other.x, y + other.y);}
    TPoint operator- (const TPoint& other) const& {return TPoint(x - other.x, y - other.y);}
    TPoint operator* (const int& k) const& {return TPoint(x * k, y * k);}
    int operator* (const TPoint& other) const& {return x * other.x + y * other.y;} ///dot product
    int operator% (const TPoint& other) const& {return x * other.y - y * other.x;} ///cross product
    int sqrlen() {return x * x + y * y;}
};

int cmp(int a, int b) {return a < b ? -1 : ((a > b) ? 1 : 0);}
int ccw(TPoint d, TPoint e, TPoint f) {return cmp((e - d) % (f - e), 0);}
const int TurnLeft = ccw(TPoint(0, 0), TPoint(0, 1), TPoint(-1, 1)); /// TurnLeft: 1
const int TurnRight = ccw(TPoint(0, 0), TPoint(0, 1), TPoint(1, 1)); /// TurnRight: -1

TPoint A;

vector<TPoint> Convexhull(vector<TPoint>& poly) {
    for(int i = 1; i < poly.size(); ++i) {
        if(poly[i].y < poly[0].y) swap(poly[i], poly[0]);
        else if(poly[i].y == poly[0].y && poly[i].x < poly[0].x) swap(poly[i], poly[0]);
    } A = poly[0];
    sort(poly.begin() + 1, poly.end(), [](const TPoint& p, const TPoint& q) {
              int tmp = (p - A) % (q - A);
              if(tmp == 0) return (p - A).sqrlen() < (q - A).sqrlen();
              return tmp > 0;
         });
    vector<TPoint> res; res.reserve(poly.size());
    res.pb(poly[0]);
    for(int i = 1; i < int(poly.size()); ++i) {
        while(res.size() >= 2 && ccw(res[res.size() - 2], res[res.size() - 1], poly[i]) <= 0) res.pop_back();
        res.pb(poly[i]);
    }
    return res;
}

int n;
vector<TPoint> convex1, convex2, hull;

int area(TPoint a, TPoint b, TPoint c) {
    return abs(a % b + b % c + c % a);
}

bool Inside(TPoint a, TPoint b, TPoint c, TPoint p) {
    return area(a, b, p) + area(a, c, p) + area(b, c, p) == area(a, b, c);
}

bool Inside(TPoint p) {
    int low = 1, mid, high = hull.size() - 1;
    if(ccw(hull[0], hull[1], p) == -1) return 0;
    if(hull.size() == 2) {
        if(ccw(hull[0], hull[1], p) != 0) return 0;
        if(min(hull[0].x, hull[1].x) <= p.x && max(hull[0].x, hull[1].x) >= p.x
           && min(hull[1].y, hull[0].y) <= p.y && max(hull[1].y, hull[0].y) >= p.y) return 1;
        return 0;
    }
    while(low <= high) {
        mid = (low + high) >> 1;
        if(ccw(hull[0], hull[mid], p) == 1) low = mid + 1;
        else high = mid - 1;
    }
    return Inside(hull[0], hull[high], hull[high + 1], p);
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define Task        "curling"
    if(fopen(Task".in", "r")) {
        freopen(Task".in", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    cin >> n; convex1.resize(n); convex2.resize(n);
    for(TPoint& p: convex1) cin >> p.x >> p.y;
    for(TPoint& p: convex2) cin >> p.x >> p.y;
    hull = Convexhull(convex1); int res = 0;
    for(TPoint p: convex2) res += Inside(p);
    cout << res << ' ';
    res = 0; hull = Convexhull(convex2);
    for(TPoint p: convex1) res += Inside(p);
    cout << res;
}
