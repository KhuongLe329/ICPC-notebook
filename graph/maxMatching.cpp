struct MaxMatching {
    int nx, ny;
    vector<vector<int>> adj;
    vector<int> S, match, lv;
    bool found;
    MaxMatching() {}
    MaxMatching(int nx, int ny): nx(nx), ny(ny), adj(nx + 1), match(ny + 1), lv(ny + 1) {}
    void add(int x, int y) {adj[x].pb(y);}
    bool layering() {
        fill(lv.begin(), lv.end(), 0);
        queue<int> q;
        for(int x: S) {
            for(int y: adj[x])
                if(lv[y] == 0) lv[y] = 1, q.push(y);
        }
        for(; q.size(); q.pop()) {
            int y = q.front(), x, lvy = lv[y] + 1;
            if((x = match[y]) == 0) return 1;
            for(int y: adj[x])
                if(lv[y] == 0) lv[y] = lvy, q.push(y);
        }
        return 0;
    }
    void augmentmatching(int x, int lvx) {
        for(int y: adj[x]) {
            if(lv[y] == lvx + 1) {
                lv[y] = 0;
                if(match[y] == 0) found = 1;
                else augmentmatching(match[y], lvx + 1);
                if(found) {match[y] = x; return;}
            }
        }
    }
    int get() {
        for(int i = 1; i <= nx; ++i) S.pb(i);
        while(layering()) {
            for(auto it = S.rbegin(); it != S.rend(); ++it) {
                found = 0;
                augmentmatching(*it, 0);
                if(found) *it = S.back(), S.pop_back();
            }
        }
        return nx - (int)S.size();
    }
};
