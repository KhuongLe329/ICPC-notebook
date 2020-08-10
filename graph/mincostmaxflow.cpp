template<typename T> class mincost_maxflow {
   struct edge {
       int to;
       T cf, cost;
   };
   int s, t;
   vector<vector<int>> adj;
   vector<edge> edges;
   vector<T> dist, trace;
   vector<bool> inq;
public:
   const T inf = numeric_limits<T>::max();
   mincost_maxflow(int n, int s, int t):
        s(s), t(t), adj(n), dist(n), inq(n), trace(n) {}
   inline void add(int u, int v, const T& cap, const T& cost) {
        adj[u].push_back(edges.size()); edges.push_back({v, cap, cost});
        adj[v].push_back(edges.size()); edges.push_back({u, 0, -cost});
   }
   bool spfa() {
        fill(dist.begin(), dist.end(), inf);
        fill(inq.begin(), inq.end(), 0);
        queue<int> q; q.push(s);
        inq[s] = 1; dist[s] = 0;
        while(q.size()) {
           int u = q.front();
           inq[u] = 0; q.pop();
           for(int i: adj[u]) {
               edge& e = edges[i];
               if(e.cf > 0 && dist[e.to] > dist[u] + e.cost) {
                  dist[e.to] = dist[u] + e.cost, trace[e.to] = i;
                  if(!inq[e.to]) q.push(e.to), inq[e.to] = 1;
               }
           }
        }
        return dist[t] < inf;
   }
   pair<T, T> get() {
       T cost = 0, flow = 0;
       while(spfa()) {
         T delta = inf;
         for(int u = t, i; u != s; u = edges[i ^ 1].to) {
            i = trace[u];
            delta = min(delta, edges[i].cf);
         }
         for(int u = t, i; u != s; u = edges[i ^ 1].to) {
            i = trace[u];
            edges[i].cf -= delta, edges[i ^ 1].cf += delta;
         }
         cost += dist[t] * delta, flow += delta;
       }
       return make_pair(cost, flow);
   }
};
mincost_maxflow<ll> f(n + 1, 0, n);
