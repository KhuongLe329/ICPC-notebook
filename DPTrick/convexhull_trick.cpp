/// convexhull get min, lines coming in decreasing order of a (y = ax + b)
const long long INF = (long long)1e15 + 11;
struct Line {
    long long a, b;
    long long f(long long x) {
        return a*x + b;
    }
};
struct Hull {
    vector<double> x;
    vector<Line> segs;
    
    Hull() {segs.clear(); x.clear();}

    void insert(Line l) {
        if (segs.empty()) {
            x.push_back(-INF);
            segs.push_back(l);
            return;
        }
        double xNew = -INF;
        while (!segs.empty()) {
            if (segs.back().a == l.a) {
                assert(segs.back().b <= l.b);
                return;
            }
            xNew = intersection(segs.back(), l);
            if (xNew < x.back()) {
                remove();
            } else break;
        }

        segs.push_back(l);
        x.push_back(xNew);
    }

    long long get(long long x0) {
        if (segs.empty()) return INF;
        auto i = upper_bound(x.begin(), x.end(), x0) - x.begin() - 1;
        return segs[i].f(x0);
    }

private:
    void remove() {
        segs.pop_back();
        x.pop_back();
    }
    double intersection(const Line& f, const Line& g) {
        return 1.0 * (f.b - g.b) / (g.a - f.a);
    }
};
/// Convexhull for max
struct Hull {
    vector<double> x;
    vector<Line> segs;

    void insert(Line l) {
        if (segs.empty()) {
            x.push_back(-INF);
            segs.push_back(l);
            return;
        }
        double xNew = -INF;
        while (!segs.empty()) {
            if (segs.back().a == l.a) {
                assert(segs.back().b >= l.b);
                return;
            }
            xNew = intersection(segs.back(), l);
            if (xNew < x.back()) {
                remove();
            } else break;
        }

        segs.push_back(l);
        x.push_back(xNew);
    }

    long long get(long long x0) {
        if (segs.empty()) {
            return -INF;
        }
        auto i = upper_bound(x.begin(), x.end(), x0) - x.begin() - 1;
        return segs[i].f(x0);
    }

private:
    void remove() {
        segs.pop_back();
        x.pop_back();
    }
    double intersection(const Line& f, const Line& g) {
        return 1.0 * (f.b - g.b) / (g.a - f.a);
    }
};
