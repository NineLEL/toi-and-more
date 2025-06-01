// 1177 ms - 61176 kB

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, L, S, T;
    cin >> n >> L >> S >> T;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());

    priority_queue<int> topS;
    multiset<int> topT;

    for (int i = 0; i < n; ++i) {
        if (i < S) topS.push(a[i]);
        else if (i < T) topT.insert(a[i]);
    }

    while (L-- && !topS.empty() && !topT.empty()) {
        int A = topS.top(); topS.pop();
        auto itB = topT.end(); --itB;
        int B = *itB;
        topT.erase(itB);

        int X = B - A;
        int Y = (A + B) / 2;

        int small = min(X, Y), large = max(X, Y);

        if (topT.empty() || small < *topT.begin()) {
            topS.push(small);
        } else {
            auto it = topT.begin();
            topS.push(*it);
            topT.erase(it);
            topT.insert(small);
        }

        topT.insert(large);
    }

    vector<int> result;
    while (!topS.empty()) {
        result.push_back(topS.top());
        topS.pop();
    }
    sort(result.begin(), result.end());

    for (int x : result) cout << x << ' ';
    for (int x : topT) cout << x << ' ';
    for (int i = T; i < n; i++) cout << a[i] << ' ';
    cout << '\n';

    return 0;
}