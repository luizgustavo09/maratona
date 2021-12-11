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

struct Data {
    ll sum, pref, suff, ans;
};
Data make_data(ll val) {
    Data res;
    res.sum = val;
    res.pref = res.suff = res.ans = max(0LL, val);
    return res;
}
Data combine(Data a, Data b) {
    Data res;
    res.sum = a.sum + b.sum;
    res.pref = max(a.pref, a.sum + b.pref);
    res.suff = max(b.suff, b.sum + a.suff);
    res.ans = max({a.ans, b.ans, a.suff + b.pref});
    return res;
}
const ll INF = numeric_limits<ll>::max();
struct SegmentTree {
    #define mid ((l+r)>>1)
    vector<Data> tree;
    int n;
    SegmentTree(int n): n(n), tree(n << 2) {}

    void build(int x, int l, int r, vll &v) {
        if(l == r) {
            tree[x] = make_data(v[l]);
            return;
        }
        build(fe(x), l, mid, v);
        build(fd(x), mid+1, r, v);
        tree[x] = combine(tree[fe(x)], tree[fd(x)]);
    }

    void update(int x, int l, int r, int p, ll k) {
        if(l == r){
            tree[x] = make_data(k);
            return;
        }
        if(p <= mid)
            update(fe(x), l, mid, p, k);
        else 
            update(fd(x), mid+1, r, p, k);
        tree[x] = combine(tree[fe(x)], tree[fd(x)]);
    }

    Data query(int x, int l, int r, int ql, int qr) {
        if(l > qr or r < ql) return make_data(0);
        if(ql <= l and r <= qr) return tree[x];
        return combine(query(fe(x), l, mid, ql, qr), query(fd(x), mid+1, r, ql, qr));
    }

    void Update(int p, ll k) {
        update(1, 0, n-1, p, k);
    }

    Data Query(int ql, int qr){
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
    cout << T.Query(0, n-1).ans << endl;
    while(q--) {
        int p;
        ll k;
        cin >> p >> k;
        T.Update(p, k);
        cout << T.Query(0, n-1).ans << endl;
    }
}