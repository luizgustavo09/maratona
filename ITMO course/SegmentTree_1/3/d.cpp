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
    SegmentTree T(2 * n);
    vi in(n, -1), out(n);
    vi nested(n);
    for(int i = 0; i < 2 * n; i++) {
        int val;
        cin >> val;
        --val;
        if(in[val] == -1) {
            in[val] = i;
            continue;
        }
        out[val] = i;
        nested[val] = T.Query(in[val], i);
        T.Update(in[val], 1LL);
    }
    for(int i = 0; i < n; i++) {
        int ans = (out[i] - in[i] - 1) - 2 * nested[i];
        cout << ans << ' ';
    }
    cout << endl;
}