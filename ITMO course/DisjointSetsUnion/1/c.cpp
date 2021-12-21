#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ll> vll;

struct UnionFind {
    vi dad, sizes, score, extra;

    UnionFind(int n): dad(n), sizes(n, 1), score(n, 0), extra(n,0) {
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
            extra[v] += score[u];
        }
        return u;
    }

    bool Connected(int u, int v) {
        return FindSet(u) == FindSet(v);
    }

    void Add(int x, int val) {
        x = FindSet(x);
        score[x] += val;
    }
     
    int Ans(int x){
        if(x!=dad[x])
            return score[x] - extra[x] + Ans(dad[x]); 
        return score[x] - extra[x];
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
        if(op == "add") {
            int s, val;
            cin >> s >> val;
            --s;
            Uf.Add(s, val);
        } else if(op == "join") {
            int a,b;
            cin >> a >> b;
            --a, --b;
            Uf.UnionSet(a, b);
        } else {
            int x;
            cin >> x;
            --x;
            cout << Uf.Ans(x) << endl;
        }
    }
}