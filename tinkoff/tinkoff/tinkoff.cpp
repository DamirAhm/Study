#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int beauty(vector<int> a) {
    int sum = 0;
    for (int i = 0; i < a.size(); i++) sum += (i+1) * a[i];

    return sum;
}

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n);

    for (int i = 0; i < n; i++) a[i] = i + 1;

    int res = 0;

    while (true) {
        int s = beauty(a);

        if (s % k == 0)
            res++;

        int i = n - 2;

        while (i >= 0 && a[i] > a[i + 1]) i--;

        if (i < 0) break;

        int j = n - 1;

        while (a[j] < a[i]) j--;

        swap(a[i], a[j]);

        sort(a.begin() + i + 1, a.begin() + n);
    }

    cout << res;

    return 0;
}