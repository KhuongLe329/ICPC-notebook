vector<int> node[maxn];
vector<int> bit[maxn];
 
void fakeup(int x , int y){
    for( ; x <= n ; x += x & -x){
        node[x].pb(y);
    }
}
 
void up(int x , int y){
    for( ; x <= n ; x += x & -x){
        for(int yy = lower_bound(node[x].begin(),node[x].end(),y)-node[x].begin() + 1 ;
            yy <= node[x].size() ; yy += yy & -yy)
                bit[x][yy - 1]++;
    }
}
 
int query(int x , int y){
    int res = 0;
    for( ; x > 0 ; x &= x - 1){
       for(int yy = lower_bound(node[x].begin(),node[x].end(),y)-node[x].begin() + 1 ;
            yy > 0 ; yy &= yy - 1)
                res += bit[x][yy - 1];
    }
    return res;
}
