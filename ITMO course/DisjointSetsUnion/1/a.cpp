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
      return (u == dad[u] ? u : FindSet(dad[u]));
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin>> n >> q;
    UnionFind Uf(n);
    while(q--){
        string op;
        cin >> op;
        if(op == "union") {
            int u, v;
            cin >> u >> v;
            Uf.UnionSet(u - 1, v - 1);
        } else {
            int u, v;
            cin >> u >> v;
            bool ans = Uf.Connected(u - 1, v - 1);
            cout << (ans ? "YES" : "NO") << endl;
        }
    }
}