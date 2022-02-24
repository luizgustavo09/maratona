#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ll> vll;

bool find(int l, int r, int *v, int x) {
    if(l > r)
        return false;
    int mid = l + (r - l) / 2;
    if(v[mid] == x)
        return true;
    else if(v[mid] > x)
        return find(l, mid - 1, v, x);
    else
        return find(mid + 1, r, v, x);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    int v[n];
    for(int i = 0; i < n; i++)
        cin >> v[i];
    for(int i = 0; i < k; i++) {
        int x;
        cin >> x;
        if(find(0, n - 1, v, x))
            cout << "YES";
        else
            cout<< "NO";
        cout << endl;
    }
}