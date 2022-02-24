#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ll> vll;

int n, q;

int firstGreaterEqual(int l, int r, int *v, int x) {
    if(l > r) {
        return l == n ? n + 1 : l + 1;
    }
    int mid = l + (r - l) / 2;
    if(v[mid] >= x)
        return firstGreaterEqual(l, mid - 1, v, x);
    else
        return firstGreaterEqual(mid + 1, r, v, x);
}

int lastLessEqual(int l, int r, int *v, int x) {
    if(l > r) {
        return r == -1 ? 0 : r + 1;
    }
    int mid = l + (r - l) / 2;
    if(v[mid] > x)
        return lastLessEqual(l, mid - 1, v, x);
    else
        return lastLessEqual(mid + 1, r, v, x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    int v[n];
    for(int i = 0; i < n; i++)
        cin >> v[i];
    sort(v, v + n);
    cin >> q;
    while(q--) {
        int l, r;
        cin >> l >> r;
        int left = firstGreaterEqual(0, n - 1, v, l);
        int right = lastLessEqual(0, n - 1, v, r);
        cout << right - left + 1 << ' ';
    }
    cout << endl;

}