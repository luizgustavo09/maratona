#include <bits/stdc++.h>
//#define endl '\n'
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int,ll> pii;

struct Edge {
    int u, v;
    ll w;
    Edge(int u, int v, ll w): u(u), v(v), w(w) {}
    Edge() {}
    bool operator < (const Edge &e2) const { return (e2.w != w) ? w < e2.w : minmax(e2.v, e2.u) < minmax(v, u); }

    bool operator != (const Edge &e2) const { return u != e2.u and v != e2.v and w != e2.w; }
};

const Edge defaultValue = Edge(-1, -1, INF);

struct Graph {
    vector<vector<pii> > adj;
    int n;
    Graph(int n): n(n), adj(n) {}

    void addEdge(int u, int v, ll w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void removeEdge(int u, int v) {
        for(int i = 0; i < adj[u].size(); i++) {
            if(adj[u][i].first == v) {
                adj[u].erase(adj[u].begin() + i);
                break;
            }
        }
    }
    void dfs(int u, int t, int dad, Edge &e) {
        for(auto p : adj[u]) if(p.first != dad) {
            if(p.first == t or (dfs(p.first, t, u, e), e != defaultValue)) {
                if(e.w > p.second) {
                    e = Edge(p.first, u, p.second);
                }
                return;
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    Graph G(n);
    vector<Edge> edges(m);
    int u, v;
    ll w;
    for(int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        edges[i] = Edge(u - 1, v - 1, w);
    }
    sort(edges.begin(), edges.end());
    set<Edge> used;
    ll res = INF;
    for(auto e : edges) {
        if(e.u == e.v)
            continue;
        Edge e2 = defaultValue;
        G.dfs(e.u, e.v, -1, e2);
        auto p = e2;
        if(p != defaultValue) {
            G.removeEdge(p.u, p.v);
            G.removeEdge(p.v, p.u);
            used.erase(p);
            used.erase(Edge(p.v, p.u, p.w));
        }
        used.insert(e);
        G.addEdge(e.u, e.v, e.w);
        if(used.size() == n - 1) {
            res = min(res, used.rbegin()->w - used.begin()->w);
        }
    }
    if(res == INF)
        cout << "NO" << endl;
    else {
        cout << "YES" << endl;
        cout << res << endl;
    }
}