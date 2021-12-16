#include <bits/stdc++.h>
#define endl '\n'
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
struct SegmentTree {
    #define mid ((l+r) >>  1)
    vector<ll> tree, lazy;
    int n;
    SegmentTree(int n): n(n), tree(n << 2), lazy(n << 2, 0) {}

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
    cin >> n >> q;
    SegmentTree T(n);
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int ql, qr;
            ll k;
            cin >> ql >> qr >> k;
            T.Update(ql, qr-1, k);
        }
        else {
            int p;
            cin >> p;
            cout << T.Query(p) << endl;
        }
    }
}