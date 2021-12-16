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
    SegmentTree(int n): n(n), tree(n << 2) {}

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

    int query(int x, int l, int r, ll k) {
        if(l == r)
            return l;
        if(tree[fd(x)] >= k)
            return query(fd(x), mid+1, r, k);
        else
            return query(fe(x), l, mid, k - tree[fd(x)]);
    }

    void Update(int p, ll k) {
        update(1, 0, n-1, p, k);
    }

    int Query(ll k){
        return query(1, 0, n-1, k);
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
        T.Update(i, 1LL);
    }
    vi ans(n);
    reverse(v.begin(), v.end());
    for(int i = 0; i < n; i++) {
        int p = T.Query(v[i] + 1);
        ans[i] = p + 1;
        T.Update(p, 0LL);
    }
    reverse(ans.begin(), ans.end());
    for(int val : ans) {
        cout << val << ' ';
    }
    cout << endl;
}