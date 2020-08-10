//Gym 101982 F -> area of point that are cover by odd rectangle
#include<bits/stdc++.h>

using namespace std;
#define taskname "A"
#define pb	push_back
#define mp 	make_pair
#ifndef LOCAL
#define cerr if(0)cout
#endif

typedef long double ld;
typedef long long ll;
typedef pair<int,int> ii;

const int N = 2e5 + 5;
#define y1 aspoifjaps
#define x1 apfjaos
#define y2 aiopdjf
#define x2 aiopsfjaiopdfj

struct Rec{
    int x1 , y1 , x2 , y2;
    Rec(int a , int b , int c , int d):x1(a) , y1(b) , x2(c) , y2(d){
        if(x1 > x2)swap(x1 , x2);
        if(y1 > y2)swap(y1 , y2);
    };
    Rec(){};
}R[N];

struct Event{
    int x , y1 , y2;
    Event(){};
    Event(int x , int y1 , int y2):x(x) , y1(y1) , y2(y2){};
    bool operator < (const Event & other)const{
        return x < other.x;
    }
};

struct Node{
    int ans , sum;
    bool lz;
    Node(){lz = 0;ans = sum = 0;};
};

vector<int> Y;
vector<Event> E;
vector<Node> S;

int n , m;

void Enter(){
    cin >> n;
    for(int i = 1 ; i <= n ; ++i){
        int a , b , c , d;cin >> a >> b >> c >> d;
        R[i] = Rec(a , b , c , d);
    }
}

void Build(int x , int l , int r){
    if(l == r){
        S[x].sum = Y[l] - Y[l - 1];
        return;
    }
    int mid = l + r >> 1;
    Build(x * 2 , l , mid);
    Build(x * 2 + 1 ,mid + 1 , r);
    S[x].sum = S[x * 2].sum + S[x * 2 + 1].sum;
}

void Push(int x , bool key){
    if(S[x].lz)S[x].ans = S[x].sum - S[x].ans;
    if(!key){
        S[x * 2].lz ^= S[x].lz;
        S[x * 2 + 1].lz ^= S[x].lz;
    }
    S[x].lz = 0;
}

int TrueVal(int x){
    if(S[x].lz)return S[x].sum - S[x].ans;
    return S[x].ans;
}

void Update(int x , int l , int r , int L , int R){
    Push(x , l == r);
    if(l > R || L > r)return;
    if(L <= l && r <= R){
        S[x].lz ^= 1;
        Push(x , l == r);
        return;
    }
    int mid = l + r >> 1;
    Update(x * 2 , l , mid , L , R);
    Update(x * 2 + 1 , mid + 1 , r , L , R);
    S[x].ans = S[x * 2].ans + S[x * 2 + 1].ans;
}

void Process(){
    for(int i = 1 ; i <= n ; ++i){
        Y.pb(R[i].y1);
        Y.pb(R[i].y2);
    }
    sort(Y.begin(),Y.end());
    Y.erase(unique(Y.begin(),Y.end()),Y.end());
    m = Y.size();
    S.resize(m * 4);
    for(int i = 1 ; i <= n ; ++i){
        E.pb(Event(R[i].x1 ,R[i].y1 , R[i].y2));
        E.pb(Event(R[i].x2, R[i].y1,R[i].y2));
    }
    sort(E.begin(),E.end());
    Build(1 , 1 , m - 1);
}

void Solve(){
    int last = 0;
    ll res = 0;
    for(auto c : E){
        res += 1ll * (c.x - last) * TrueVal(1);
        last = c.x;
//        cout << TrueVal(1) << " " << c.x << " " << c.y1 << " " << c.y2 << endl;
        Update(1 , 1 , m - 1 ,
        lower_bound(Y.begin(),Y.end(),c.y1) - Y.begin() + 1 ,
        lower_bound(Y.begin(),Y.end(),c.y2) - Y.begin());
    }
    cout << res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if(fopen(taskname".INP","r")){
		freopen(taskname".INP", "r",stdin);
		freopen(taskname".OUT", "w",stdout);
    }
    Enter();
    Process();
    Solve();
}
