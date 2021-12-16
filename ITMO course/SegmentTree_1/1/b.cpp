#include <bits/stdc++.h>
//#define endl '\n'
using namespace std;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ll> vll;

inline int fe(int x) {
    return 2*x;
}
inline int fd(int x) {
    return 2*x+1;
}
const ll INF = numeric_limits<ll>::max();
struct SegmentTree {
    #define mid ((l+r)>>1)
    vector<ll> tree;
    int n;
    SegmentTree(int n): n(n), tree(n << 2) {}

    void build(int x, int l, int r, vll &v) {
        if(l == r) {
            tree[x] = v[l];
            return;
        }
        build(fe(x), l, mid, v);
        build(fd(x), mid+1, r, v);
        tree[x] = min(tree[fe(x)], tree[fd(x)]);
    }

    void update(int x, int l, int r, int p, ll k) {
        if(l == r){
            tree[x] = k;
            return;
        }
        if(p <= mid)
            update(fe(x), l, mid, p, k);
        else 
            update(fd(x), mid+1, r, p, k);
        tree[x] = min(tree[fe(x)], tree[fd(x)]);
    }

    ll query(int x, int l, int r, int ql, int qr) {
        if(l > qr or r < ql) return INF;
        if(ql <= l and r <= qr) return tree[x];
        return min(query(fe(x), l, mid, ql, qr), query(fd(x), mid+1, r, ql, qr));
    }

    void Update(int p, ll k) {
        update(1, 0, n-1, p, k);
    }

    ll Query(int ql, int qr){
        return query(1, 0, n-1, ql, qr);
    }
};
int main() {
    int n, q;
    cin >> n >> q;
    SegmentTree T(n);
    vll v(n);
    for(int i = 0; i < n; i++)
        cin >> v[i];
    T.build(1, 0, n-1, v);
    
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int p;
            ll k;
            cin >> p >> k;
            T.Update(p, k);
        }
        else {
            int ql, qr;
            cin >> ql >> qr;
            cout << T.Query(ql, qr-1) << endl;
        }
    }


}