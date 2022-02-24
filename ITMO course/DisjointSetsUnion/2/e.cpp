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
    bool operator < (const Edge &e2) const { return w < e2.w; }
};

struct MST {
    UnionFind Uf;
    vector<Edge> edges;
    
    MST(int n): Uf(n) {}
    
    inline void addEdge(int u, int v, ll w) {
        edges.push_back(Edge(u, v, w));
    }

    ll solve() {
        ll ans = 0;
        sort(edges.begin(), edges.end());
        for(auto e : edges) {
            if(!Uf.Connected(e.u, e.v)) {
                ans += e.w;
                Uf.UnionSet(e.u, e.v);
            }
        }
        return ans;
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    MST T(n);
    int u, v;
    ll w;
    for(int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        T.addEdge(u - 1, v - 1, w);
    }
    cout << T.solve() << endl;
}