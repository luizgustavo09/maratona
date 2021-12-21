#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ll> vll;

struct UnionFind {
    vi dad, sizes;

    UnionFind(int n): dad(n), sizes(n, 1) {
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

struct Query {
    string op;
    int u, v;
    Query(string op, int u, int v): op(op), u(u), v(v) {}
    Query() {}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, q;
    cin >> n >> m >> q;
    UnionFind Uf(n);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
    }
    vector<Query> queries(q);
    for(int i = 0; i < q; i++) {
        Query a;
        cin >> a.op >> a.u >> a.v;
        --a.u, --a.v;
        queries[i] = a;
    }
    reverse(queries.begin(), queries.end());
    vector<string> answers;
    for(auto a : queries) {
        if(a.op == "ask") {
            if(Uf.Connected(a.u, a.v))
                answers.push_back("YES");
            else
                answers.push_back("NO");
        }
        else {
            Uf.UnionSet(a.u, a.v);
        }
    }
    reverse(answers.begin(), answers.end());
    for(auto ans : answers)
        cout << ans << endl;
    
}