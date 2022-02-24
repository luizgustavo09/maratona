//I suspect this complexity is not good for this problem, but the verdict is accepted
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ll> vll;

struct UnionFind {
    vi dad, sizes, dc;

    UnionFind(int n): dad(n), sizes(n, 1), dc(n, 0){
        for (int i = 0; i < n; ++i)
            dad[i] = i;
    }

    int Update(int u) {
        if(u == dad[u])
            return u;
        int prev = dad[u];
        dad[u] = Update(dad[u]);
        dc[u] = dc[ prev ] + dc[u];
        return dad[u];
    }

    int UnionSet(int u, int v) {
        dc[u] = 1;
        dad[u] = v;
        return u;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    UnionFind Uf(n);
    while(q--){
        int op;
        cin >> op;
        if(op == 1) {
            int u, v;
            cin >> u >> v;
            Uf.UnionSet(u - 1, v - 1);
        } else {
            int u;
            cin >> u;
            --u;
            Uf.Update(u);
            cout << Uf.dc[u] << endl;
        }
    }
}