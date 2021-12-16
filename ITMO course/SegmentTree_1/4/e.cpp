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
const int INF = numeric_limits<int>::max();
struct SegmentTree {
    #define mid ((l+r)>>1)
    vector<int> tree;
    int n;
    SegmentTree(int n): n(n), tree(n << 2, INF) {}

    void update(int x, int l, int r, int p, int k) {
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

    int destroy(int x, int l, int r, int ql, int qr, int p) {
        if(ql > r or qr < l)
            return 0;
        if(l == r and tree[x] <= p) {
            tree[x] = INF;
            return 1;
        }
        int ans = 0;
        if(tree[fe(x)] <= p)
            ans += destroy(fe(x), l, mid, ql, qr, p);
        if(tree[fd(x)] <= p)
            ans += destroy(fd(x), mid+1, r, ql, qr, p);

        tree[x] = min(tree[fe(x)], tree[fd(x)]);
        return ans;
    }

    void Update(int p, ll k) {
        update(1, 0, n-1, p, k);
    }

    int Destroy(int ql, int qr, int p){
        return destroy(1, 0, n-1, ql, qr, p);
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
            int p;
            int k;
            cin >> p >> k;
            T.Update(p, k);
        }
        else {
            int ql, qr, p;
            cin >> ql >> qr >> p;
            cout << T.Destroy(ql, qr-1, p) << endl;
        }
    }


}