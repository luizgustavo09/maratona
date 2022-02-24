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

inline int fe(int x) {
    return 2*x;
}
inline int fd(int x) {
    return 2*x+1;
}
struct SegmentTree {
    #define mid ((l+r) >>  1)
    vector<ll> tree, lazy;
    UnionFind Uf;
    int n;
    SegmentTree(int n): n(n), tree(n << 2), lazy(n << 2, 0), Uf(n) {}
 
    void push(int x, int l, int r){
        if(lazy[x] != 0) {
            tree[x] += (r - l + 1) * lazy[x];
            if(l != r) {
                lazy[fe(x)] += lazy[x];
                lazy[fd(x)] += lazy[x];
            }
            lazy[x] = 0;
        }
    }
    void update(int x, int l, int r, int ql, int qr, ll k) {
        push(x, l, r);
        if(l > qr or r < ql) return;
        if(ql <= l and r <= qr) {
            lazy[x] += k;
            push(x, l, r);
            return;
        }
        update(fe(x), l, mid, ql, qr, k);
        update(fd(x), mid+1, r, ql, qr, k);
        tree[x] = tree[fe(x)] + tree[fd(x)];
    }
 
    ll query(int x, int l, int r, int p) {
        push(x, l, r);
        if(l == r)
            return tree[x];
        if(p <= mid)
            return query(fe(x), l, mid, p);
        else
            return query(fd(x), mid+1, r, p);
    }
    void Update(int ql, int qr, ll k) {
        update(1, 0, n-1, ql, qr, k);
    }
 
    ll Query(int p){
        return query(1, 0, n-1, p);
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