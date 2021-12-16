//Usei seg interativa aqui mas não tem necessidade, apenas não utilize
//vector para representar a matriz pois isso suja muito o cache e 
//então dá tle
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;

int MOD;
struct MINT{
    int v;

    MINT(ll val = 0){
        v = (-MOD <= val && val < MOD) ? val : val % MOD;
        if(v < 0) v += MOD;
    }

	MINT operator - () const { return MINT(-v); }
	MINT operator * (const MINT& m2) const { return v * 1LL * m2.v % MOD; }
	MINT operator / (const MINT& m2) const { return (*this) * inv(m2); }
	MINT& operator *= (const MINT& m2){ return (*this) = (*this) * m2; }
	MINT& operator /= (const MINT& m2){ return (*this) = (*this) / m2; }
	MINT& operator += (const MINT& m2){ return (*this) = (*this) + m2; }
	MINT& operator -= (const MINT& m2){ return (*this) = (*this) - m2; }
	bool operator == (const MINT& m2) const { return v == m2.v; }
	bool operator != (const MINT& m2) const { return v != m2.v; }
	bool operator < (const MINT& m2) const { return v < m2.v; }
	friend istream& operator >> (istream &is, MINT &a) { ll t; is >> t; a = MINT(t); return is; }
	friend ostream& operator << (ostream &os, const MINT &a) { return os << a.v; }
	friend MINT inv(const MINT& a) { return pw(a, MOD - 2); } // only if MOD is prime

	MINT operator + (const MINT& m2) const{
    	int tmp = v + m2.v;
    	return tmp >= MOD ? tmp - MOD : tmp;
  	}

  	MINT operator - (const MINT& m2) const{
    	int tmp = v - m2.v;
    	return tmp < 0 ? tmp + MOD : tmp;
  	}

  	friend MINT pw(MINT a, ll b){
    	MINT ret = 1;
    	while(b){
      		if(b & 1) ret *= a;
      		b >>= 1; a *= a;
    	}
    	return ret;
  	}
};

struct Matrix {
	MINT a[2][2] = {{1, 0}, {0, 1}};

	MINT* operator[](int i) {
    	return a[i];
    }
	
	Matrix operator*(Matrix other) {
		Matrix ans;
		ans[0][0] = ans[1][1] = 0;
		for(int i = 0; i < 2; i++)
			for(int j = 0; j < 2; j++)
				for(int k = 0; k < 2; k++)
					ans[i][j] += a[i][k] * other.a[k][j];
		return ans;
	}
};

struct SegmentTree {
  	int n;
  	vector<Matrix> t;

  	SegmentTree(int n): n(n), t(n << 1) {}

  	void Set(int i, Matrix vl) {
    	t[i + n] = vl;
  	}

  	void Build() {
    	for (int i = n - 1; i > 0; --i)
      	t[i] = t[i << 1] * t[i << 1 | 1];
  	}

  	Matrix Query(int l, int r) {
    	Matrix resl, resr;
    	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      		if (l & 1) resl = resl * t[l++];
      		if (r & 1) resr = t[--r] * resr;
    	}
    	return resl * resr;
  	}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> MOD;
    int n, q;
    cin >> n >> q;
    SegmentTree T(n);
    for(int k = 0; k < n; k++) {
    	Matrix m;
    	for(int i = 0; i < 2; i++)
    		for(int j = 0; j < 2; j++)
    			cin >> m.a[i][j];
    	T.Set(k, m);
    }
    T.Build();
    while(q--) {
    	int ql, qr;
    	cin >> ql >> qr;
    	--ql, --qr;
    	Matrix ans = T.Query(ql, qr+1);
    	for(int i = 0; i < 2; i++) {
    		for(int j = 0; j < 2; j++){
    			cout << ans.a[i][j] << ' ';
    		}
    		cout<<endl;
    	}
    	cout << endl;
    }
}