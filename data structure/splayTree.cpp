#include <bits/stdc++.h>
#define pb          emplace_back
#define ll          long long
#define fi          first
#define se          second
#define mp          make_pair

using namespace std;

const int N = int(1e5) + 7;

struct SplayTree {
    struct TNode {
        TNode *P, *L, *R;
        int sz, val;
        bool rev;
        TNode(TNode* P = NULL, TNode* L = NULL, TNode* R = NULL, int sz = 0, int val = 0, bool rev = 0):
            P(P), L(L), R(R), sz(sz), val(val), rev(rev) {}
    };
    typedef TNode* PNode;
    PNode root, nil, x;
    int n;
    SplayTree() {}
    SplayTree(int n): n(n) {
        nil = new TNode();
        nil -> P = nil -> R = nil -> L = nil;
        root = Build(1, n);
    }
    PNode Build(int l, int r) {
        if (l > r) return nil;
        int m = (l + r) >> 1;
        PNode x = new TNode();
        x -> val = m;
        x -> P = nil;
        Link(x, Build(l, m - 1), false);
        Link(x, Build(m + 1, r), true);
        Update(x);
        return x;
    }
    void Link(PNode p, PNode chil, bool Right) {
        if(Right) {
            p -> R = chil;
            chil -> P = p;
        } else {
            p -> L = chil;
            chil -> P = p;
        }
    }
    void Update(PNode x) {x -> sz = x -> L -> sz + x -> R -> sz + 1;}
    PNode Locate(PNode x, int i) {
        for(int t; ;) {
           PushDown(x);
           t = x -> L -> sz + 1;
           if(t == i) break;
           if(i < t) x = x -> L;
           else x = x -> R, i -= t;
        }
        return x;
    }
    void PushDown(PNode& x) {
        if(x == nil) return;
        if(x -> rev) {
          x -> rev ^= 1;
          swap(x -> L, x -> R);
          x -> L -> rev ^= 1;
          x -> R -> rev ^= 1;
        }
    }
    void UpTree(PNode x) {
        PNode y = x -> P, z = y -> P;
        if(y -> L == x) Link(y, x -> R, false), Link(x, y, true);
        else Link(y, x -> L, true), Link(x, y, false);
        Link(z, x, z -> R == y);
        Update(y); Update(x);
    }
    void Splay(PNode x) {
        for (; ;) {
            PNode y = x -> P, z = y -> P;
            if (y == nil) return;
            if (z != nil)
                if ((z -> L == y) == (y -> L == x)) UpTree(y);
                else UpTree(x);
            UpTree(x);
        }
    }
    void Split(PNode T, int i, PNode& A, PNode& B) {
        PushDown(T);
        if(i == 0) {A = nil; B = T; return;}
        A = Locate(T, i);
        Splay(A);
        B = A -> R;
        A -> R = B -> P = nil;
        Update(A);
    }
    PNode Join(PNode A, PNode B) {
        PushDown(A); PushDown(B);
        if(A == nil) return B;
        A = Locate(A, A -> sz);
        Splay(A);
        Link(A, B, true);
        Update(A);
        return A;
    }
    void Print(PNode x) {
        if(x == nil) return;
        PushDown(x);
        Print(x -> L);
        cout << x -> val << ' ';
        Print(x -> R);
    }
    void Reverse(int l, int r) {
        PNode T1, T2, T3;
        Split(root, l - 1, T1, T3);
        Split(T3, r - l + 1, T2, T3);
        T2 -> rev ^= 1;
        root = Join(Join(T1, T2), T3);
    }
} tree;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define Task        "test"
    if(fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    int n, q;
    cin >> n >> q;
    tree = SplayTree(n);
    while(q --) {
        int i, j;
        cin >> i >> j;
        tree.Reverse(i, j);
    }
    tree.Print(tree.root);
}
///Lazy Update
#include <bits/stdc++.h>
#define pb          emplace_back
#define ll          long long
#define fi          first
#define se          second
#define mp          make_pair

using namespace std;

const int N = int(2e5) + 7;

int base[N];
struct SplayTree {
    struct TVal { ///Val = p * n + s
        ll c, s, p;
        int tq;
        TVal(ll c = 0, ll s = 0, ll p = 0, int tq = 0): c(c), s(s), p(p), tq(tq) {}
        ll val(int n) {return 1ll * tq * c + s + n * p;}
        ll calc(int n) {return 1ll * tq * c * n + s * n + 1ll * n * (n - 1) / 2 * p;}
        inline TVal& operator += (const TVal& o) {
           if(o.tq) (*this) = o;
           else this -> s += o.s, this -> p += o.p;
           return (*this);
        }
    };
    struct TNode {
        TNode *P, *L, *R;
        int sz;
        ll val, sum;
        TVal node;
        TNode(TNode* P = NULL, TNode* L = NULL, TNode* R = NULL, int sz = 0, int val = 0, ll sum = 0):
            P(P), L(L), R(R), sz(sz), val(val), sum(sum) {}
    };
    typedef TNode* PNode;
    PNode root, nil, x;
    int n;
    SplayTree() {}
    SplayTree(int n): n(n) {
        nil = new TNode();
        nil -> P = nil -> R = nil -> L = nil;
        root = Build(1, n);
    }
    PNode Build(int l, int r) {
        if (l > r) return nil;
        int m = (l + r) >> 1;
        PNode x = new TNode();
        x -> val = base[m];
        x -> P = nil;
        Link(x, Build(l, m - 1), false);
        Link(x, Build(m + 1, r), true);
        Update(x);
        return x;
    }
    void Link(PNode p, PNode chil, bool Right) {
        if(Right) {
            p -> R = chil;
            chil -> P = p;
        } else {
            p -> L = chil;
            chil -> P = p;
        }
    }
    void Update(PNode x) {
        x -> sz = x -> L -> sz + x -> R -> sz + 1;
        x -> sum = x -> L -> sum + x -> R -> sum + x -> val;
    }
    PNode Locate(PNode x, int i) {
        for(int t; ;) {
           PushDown(x);
           t = x -> L -> sz + 1;
           if(t == i) break;
           if(i < t) x = x -> L;
           else x = x -> R, i -= t;
        }
        return x;
    }
    void PushDown(PNode& x) {
        if(x == nil) return;
        if(!(x -> node.s) && !(x -> node.p) && !(x -> node.tq)) return;
        PNode& lef = x -> L; PNode& rig = x -> R;
        if(x -> node.tq) x -> sum = x -> val = 0;
        x -> sum += x -> node.calc(x -> sz);
        x -> val += x -> node.val(lef -> sz);
        lef -> node += x -> node;
        x -> node.s += x -> node.p * (lef -> sz + 1);
        rig -> node += x -> node;
        x -> node = TVal();
    }
    void PushNode(PNode& x) {
        if(x == nil) return;
        PushNode(x -> P); PushDown(x -> L); PushDown(x -> R);
    }
    void UpTree(PNode x) {
        PNode y = x -> P, z = y -> P;
        if(y -> L == x) Link(y, x -> R, false), Link(x, y, true);
        else Link(y, x -> L, true), Link(x, y, false);
        Link(z, x, z -> R == y);
        Update(y); Update(x);
    }
    void Splay(PNode x) {
        PushNode(x);
        for (; ;) {
            PNode y = x -> P, z = y -> P;
            if (y == nil) return;
            if (z != nil)
                if ((z -> L == y) == (y -> L == x)) UpTree(y);
                else UpTree(x);
            UpTree(x);
        }
    }
    void Split(PNode T, int i, PNode& A, PNode& B) {
        PushNode(T);
        if(i == 0) {A = nil; B = T; return;}
        A = Locate(T, i);
        Splay(A);
        B = A -> R;
        A -> R = B -> P = nil;
        Update(A);
    }
    PNode Join(PNode A, PNode B) {
        PushNode(A); PushNode(B);
        if(A == nil) return B;
        A = Locate(A, A -> sz);
        Splay(A);
        Link(A, B, true);
        Update(A);
        return A;
    }
    void Print(PNode x) {
        if(x == nil) return;
        PushNode(x);
        Print(x -> L);
        cout << x -> val << ' ';
        Print(x -> R);
    }
    void Insert(int pos, int x) {
        PNode T1, T2, T3;
        Split(root, pos - 1, T1, T3);
        T2 = new TNode(nil, nil, nil, 1, x, x);
        root = Join(Join(T1, T2), T3);
        ++n;
    }
    void CoverUpdate(int l, int r, int val) {
        PNode T1, T2, T3;
        Split(root, l - 1, T1, T2);
        Split(T2, r - l + 1, T2, T3);
        T2 -> node += TVal(val, 0, 0, 1);
        PushNode(T2);
        root = Join(Join(T1, T2), T3);
    }
    void AddUpdate(int l, int r, int add) {
        PNode T1, T2, T3;
        Split(root, l - 1, T1, T2);
        Split(T2, r - l + 1, T2, T3);
        T2 -> node += TVal(0, add, add, 0);
        PushNode(T2);
        root = Join(Join(T1, T2), T3);
    }
    ll GetSum(int l, int r) {
        PNode T1, T2, T3;
        Split(root, l - 1, T1, T2);
        Split(T2, r - l + 1, T2, T3);
        ll res = T2 -> sum;
        root = Join(Join(T1, T2), T3);
        return res;
    }
    void Test() {
        CoverUpdate(1, 3, 3);
        cout << GetSum(1, 5);
    }
} tree;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define Task        "sq"
    if(fopen(Task".inp", "r")) {
        freopen(Task".inp", "r", stdin);
        freopen(Task".out", "w", stdout);
    }
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) cin >> base[i];
    tree = SplayTree(n);
    while(q --) {
        int cmd, a, b, x;
        cin >> cmd >> a >> b;
        if(cmd == 1) cin >> x, tree.CoverUpdate(a, b, x);
        else if(cmd == 2) cin >> x, tree.AddUpdate(a, b, x);
        else if(cmd == 3) tree.Insert(a, b);
        else cout << tree.GetSum(a, b) << '\n';
    }
}
