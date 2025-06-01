// 541 ms - 13396 kB

#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

int stringToMask(const string& s) {
    int mask = 0;
    for (char c : s) {
        mask = (mask << 1) | (c - '0');
    }
    return mask;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    int size = 1 << N;
    vector<int> pattern_weights(size);

    string pattern_str;
    for (int i = 0; i < size; ++i) {
        int weight_val;
        cin >> pattern_str >> weight_val;
        pattern_weights[stringToMask(pattern_str)] = weight_val;
    }

    const long long NEG_INF = numeric_limits<long long>::min();
    vector<long long> dp(size, NEG_INF);
    dp[0] = 0;

    for (int mask = 1; mask < size; ++mask) {
        long long weight = pattern_weights[mask];
        long long best = NEG_INF;

        for (int i = 0; i < N; ++i) {
            if ((mask >> i) & 1) {
                int next = mask ^ (1 << i);
                long long val = dp[next];
                if (val != NEG_INF) {
                    long long temp = weight + val;
                    best = (temp > best) ? temp : best;
                }
            }
        }

        for (int i = 0; i < N - 1; ++i) {
            if (((mask >> i) & 3) == 3) {
                int next = mask ^ (3 << i);
                long long val = dp[next];
                if (val != NEG_INF) {
                    long long temp = weight + val;
                    best = (temp > best) ? temp : best;
                }
            }
        }

        dp[mask] = best;
    }

    for (int q = 0; q < Q; ++q) {
        cin >> pattern_str;
        int query_mask = stringToMask(pattern_str);
        cout << dp[query_mask] << '\n';
    }

    return 0;
}

// Low memory version
// 594 ms - 5175 kB

#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

int stringToMask(const string& s) {
    int mask = 0;
    for (char c : s)
        mask = (mask << 1) | (c - '0');
    return mask;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    int size = 1 << N;
    const int NEG_INF = numeric_limits<int>::min();
    vector<int> dp(size, NEG_INF);

    string s;
    for (int i = 0; i < size; ++i) {
        int w;
        cin >> s >> w;
        dp[stringToMask(s)] = w;
    }

    for (int mask = 1; mask < size; ++mask) {
        int best = NEG_INF;
        for (int i = 0; i < N; ++i)
            if (mask & (1 << i))
                best = max(best, dp[mask ^ (1 << i)]);
        for (int i = 0; i < N - 1; ++i)
            if ((mask >> i & 3) == 3)
                best = max(best, dp[mask ^ (3 << i)]);
        if (best != NEG_INF)
            dp[mask] += best;
        else
            dp[mask] = NEG_INF;
    }

    while (Q--) {
        cin >> s;
        int mask = stringToMask(s);
        cout << dp[mask] << '\n';
    }

    return 0;
}
