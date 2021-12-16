#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ll> vll;

const int mx = 41;

inline int fe(int x) {
    return 2*x;
}
inline int fd(int x) {
    return 2*x+1;
}

struct Data {
    ll inv = 0LL, sz = 0;
	int freq[41] = {0};
};

Data make_data (int val) {
	Data no;
	no.freq[val] = no.sz = 1;
	return no;
}

Data combine(Data a, Data b) {
	Data no;
    no.inv = a.inv + b.inv;
    no.sz = a.sz + b.sz;
    //Guarda o tamanho do intervalo a esquerda de b que tem inversões
    int sz = a.sz;

    for(int i = 1; i < mx; i++) {
        no.inv += (ll)b.freq[i - 1] * (ll)sz;
        sz -= a.freq[i];
    }

	for(int i = 1; i < mx; i++)
		no.freq[i] = a.freq[i] + b.freq[i];
    return no; 
}

struct SegmentTree {
    #define mid ((l+r)>>1)
    vector<Data> tree;
    int n;
    SegmentTree(int n): n(n), tree(n << 2) {}

    void build(int x, int l, int r, vi &v) {
        if(l == r) {
            tree[x] = make_data(v[l]);
            return;
        }
        build(fe(x), l, mid, v);
        build(fd(x), mid+1, r, v);
        tree[x] = combine(tree[fe(x)], tree[fd(x)]);
    }

    void update(int x, int l, int r, int p, int k) {
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
        if(l > qr or r < ql) return Data();
        if(ql <= l and r <= qr) return tree[x];
        return combine(query(fe(x), l, mid, ql, qr), query(fd(x), mid+1, r, ql, qr));
    }

    void Update(int p, int k) {
        update(1, 0, n-1, p, k);
    }

    Data Query(int ql, int qr){
        return query(1, 0, n-1, ql, qr);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    SegmentTree T(n);
    vi v(n);
    for(int i = 0; i < n; i++)
        cin >> v[i];
    T.build(1, 0, n-1, v);
    while(q--) {
        int op;
        cin >> op;
        if(op == 2) {
            int p;
            int k;
            cin >> p >> k;
            --p;
            T.Update(p, k);
        }
        else {
            int ql, qr;
            cin >> ql >> qr;
            --ql, --qr;
            Data ans = T.Query(ql, qr);
           	cout << ans.inv << endl;
        }
    }
}