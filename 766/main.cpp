#include <iostream>
#include <vector>

using namespace std;

vector<int> a;

int n;

void merge(int l, int r) {
    if (r == l)
        return;
    if (r - l == 1) {
        if (a[r] < a[l])
            swap(a[r], a[l]);
        return;
    }
    int m = (r + l) / 2;
    merge(l, m);
    merge(m + 1, r);
    vector<int> buf(r - l + 1);
    int xl = l;
    int xr = m + 1;
    int cur = 0;
    while (r - l + 1 != cur) {
        if (xl > m)
            buf[cur++] = a[xr++];
        else if (xr > r)
            buf[cur++] = a[xl++];
        else if (a[xl] > a[xr])
            buf[cur++] = a[xr++];
        else buf[cur++] = a[xl++];

    }
    for (int i = 0; i < cur; i++)
        a[i + l] = buf[i];
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        a.push_back(t);
    }

    merge(0, n - 1);

    for (int i = 0; i < n; i++)
        cout << a[i] << " ";

    return 0;
}