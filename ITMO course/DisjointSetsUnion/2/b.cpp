#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ll> vll;

struct UnionFind {
    vi dad;
    UnionFind(int n): dad(n) {
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
        if (u != v)
            dad[u] = dad[v];
        return v;
    }

    bool Connected(int u, int v) {
        return FindSet(u) == FindSet(v);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    UnionFind Uf(n);
    vi ans(n);
    for(int i = 0; i < n; i++) {
        int p; 
        cin >> p;
        --p;
        p = Uf.FindSet(p);
        ans[i] = p;
        Uf.UnionSet(p, (p+1)%n);
    } 
    for(int res : ans)
        cout << res + 1 << ' ';
    cout << endl;
}