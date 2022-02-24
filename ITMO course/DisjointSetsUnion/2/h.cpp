#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ll> vll;

struct UnionFind {
    vi dad, sizes;

    UnionFind(int n): dad(n), sizes(n, 1){
        for (int i = 0; i < n; ++i)
            dad[i] = i;
    }

    int FindSet(int u) {
        if(u == dad[u])
            return u;
        return dad[u] = FindSet(dad[u]);
    }

    int UnionSet(int u, int v) {
        u = FindSet(u);
        v = FindSet(v);
        if (u != v){
            if (sizes[u] < sizes[v])
                swap(u, v);
            sizes[u] += sizes[v];
            dad[v] = dad[u];
        }
        return u;
    }

    bool Connected(int u, int v) {
        return FindSet(u) == FindSet(v);
    }
};

struct Edge {
    int u, v;
    ll w;
    Edge(int u, int v, ll w): u(u), v(v), w(w) {}
    Edge() {}

    bool operator < (const Edge &e2) const { return (e2.w != w) ? w < e2.w : minmax(e2.v, e2.u) < minmax(v, u); }
    bool operator != (const Edge &e2) const { return u != e2.u and v != e2.v and w != e2.w; }
};

struct MST {
    UnionFind Uf;
    vector<Edge> edges;
    
    MST(int n): Uf(n) {}
    
    inline void addEdge(int u, int v, ll w) {
        edges.push_back(Edge(u, v, w));
    }

    void buildMST(set<Edge> &notUsed) {
        sort(edges.rbegin(), edges.rend());
        for(auto e : edges) {
            if(!Uf.Connected(e.u, e.v)) {
                notUsed.erase(e);
                Uf.UnionSet(e.u, e.v);
            }
        }
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    ll s;
    cin >> n >> m >> s;
    MST T(n);
    int u, v;
    ll w;
    set<Edge> notUsed;
    map<Edge, int> mapa;
    for(int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        T.addEdge(u - 1, v - 1, w);
        auto e = Edge(u - 1, v - 1, w);
        notUsed.insert(e);
        mapa[e] = i + 1;
    }
    T.buildMST(notUsed);
    vi ans;
    for(auto e : notUsed) {
        if(s - e.w < 0)
            break;
        s -= e.w;
        ans.push_back(mapa[e]);
    }
    cout << ans.size() << endl;
    for(int v : ans) 
        cout << v << ' ';
    cout << endl;

}