#include<bits/stdc++.h>
 
using namespace std;
#define taskname "TEST"
#define pb	push_back
typedef long double ld;
typedef long long ll;
const int maxn = 1e5 + 5;
 
int n , m;
int a[maxn];
 
struct node
{
    ll sum , lz;
    node * l , * r;
    node(ll sum , ll lz , node * l , node * r): sum(sum) , lz(lz) , l(l) , r(r) {};
};
 
void enter()
{
    cin >> n >> m;
    for(int i = 1 ; i <= n ; ++i)cin >> a[i];
}
 
int L , R, W;
int nTime = 0;
node * root[maxn] , * curr;
node * null = new node(0 , 0 , 0 , 0);
node * build(int l , int r)
{
    if(l == r){
        return new node(a[l] , 0 , null,null);
    }
    int mid = l + r >> 1;
    node * res = new node(0,0,null,null);
    res->l = build(l,mid);
    res->r = build(mid+1,r);
    res->sum = res->l->sum + res->r->sum;
    return res;
}
 
void update(node * & x , int l , int r)
{
//    if(l > R || L > r)return;
    node * res = new node(0,0,0,0);
    *res = *x;
    x = res;
    if(L <= l && r <= R)
    {
        x->lz += W;
        return;
    }
    int mid = l + r >> 1;
//    L = max(L , l);
//    R = min(R , r);
    x->sum += (ll)(min(R,r) - max(L,l) + 1) * W;
//    assert(R >= L);
    if(mid >= L)
        update(x->l,l,mid);
    if(mid < R)
        update(x->r,mid+1,r);
}
 
ll query(node * & x , int l , int r , int W = 0)
{
//    cout << l << " " << r << " " << L << " " << R << endl;
//    assert(x != 0);
    W += x->lz;
    if(L <= l && r <= R)
        return x->sum + (ll)W * (r - l + 1);
    int mid = l + r >> 1;
    ll res = 0;
    if(mid >= L)res += query(x->l,l,mid,W);
    if(mid < R)res += query(x->r,mid+1,r,W);
    return res;
}
 
void solve()
{
    null->l = null->r = null;
    root[0] = build(1,n);
    curr = root[0];
    for(int i = 1 ; i <= m ; ++i)
    {
        char key;cin >> key;
        if(key == 'C')
        {
            int l , r , d;
            cin >> l >> r >> d;
            L = l;R = r;W = d;
            update(curr,1,n);
            root[++nTime] = curr;
        }
        else if(key == 'Q')
        {
            int l , r;cin >> l >> r;
            L = l;R = r;
            cout << query(curr,1,n,0) << '\n';
        }
        else if(key == 'H')
        {
            int l , r , t;cin >> l >> r >> t;
            L = l;R = r;
            cout << query(root[t],1,n,0) << '\n';
        }
        else {
            int t;cin >> t;
            nTime = t;
            curr = root[t];
        }
    }
}
 
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	if(fopen(taskname".INP","r"))
        freopen(taskname".INP", "r",stdin) ,
        freopen(taskname".OUT", "w",stdout);
    enter();
    solve();
}
