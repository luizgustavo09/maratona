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
    #define mid ((l+r)>>1)
    vector<ll> tree;
    int n;
    SegmentTree(int n): n(n), tree(n << 2, 0) {}
    void update(int x, int l, int r, int p, ll k) {
        if(l == r){
            tree[x] = k;
            return;
        }
        if(p <= mid)
            update(fe(x), l, mid, p, k);
        else 
            update(fd(x), mid+1, r, p, k);
        tree[x] = tree[fe(x)] + tree[fd(x)];
    }

    ll query(int x, int l, int r, int ql, int qr) {
        if(l > qr or r < ql) return 0LL;
        if(ql <= l and r <= qr) return tree[x];
        return query(fe(x), l, mid, ql, qr) + query(fd(x), mid+1, r, ql, qr);
    }

    void Update(int p, ll k) {
        update(1, 0, n-1, p, k);
    }

    ll Query(int ql, int qr){
        return query(1, 0, n-1, ql, qr);
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    SegmentTree T(n);
    vll v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
        --v[i];
    }
    for(ll k : v) {
        cout << T.Query(k+1, n-1) << ' ';
        T.Update(k, 1LL);
    }
    cout << endl;
}