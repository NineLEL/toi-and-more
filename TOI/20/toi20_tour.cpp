#include <bits/stdc++.h>
#define int long long
using namespace std;

int nodeCount, edgeCount, shopCount;
int shops[11];
vector<pair<int, int>> graph[300300];
vector<pair<int, int>> pointList;

void traverse(int node, int distSum, int weightSum) {
    if (node == nodeCount) {
        pointList.emplace_back(distSum, weightSum);
        return;
    }
    for (auto& edge : graph[node]) {
        int next = edge.first;
        int weight = edge.second;
        if (weight < 0)
            traverse(next, distSum - weight, weightSum);
        else
            traverse(next, distSum, weightSum + weight);
    }
}

int processStrip(vector<pair<int, int>>& region, int bestDist) {
    sort(region.begin(), region.end(), [](auto& a, auto& b) {
        return a.second < b.second;
    });

    for (size_t i = 0; i < region.size(); ++i) {
        for (size_t j = i + 1; j < region.size(); ++j) {
            int dy = region[j].second - region[i].second;
            if (dy * dy >= bestDist) break;
            int dx = region[i].first - region[j].first;
            bestDist = min(bestDist, dx * dx + dy * dy);
        }
    }
    return bestDist;
}

int findClosest(int left, int right) {
    if (right - left + 1 <= 3) {
        int minDist = LLONG_MAX;
        for (int i = left; i < right; ++i) {
            for (int j = i + 1; j <= right; ++j) {
                int dx = pointList[i].first - pointList[j].first;
                int dy = pointList[i].second - pointList[j].second;
                minDist = min(minDist, dx * dx + dy * dy);
            }
        }
        return minDist;
    }

    int mid = (left + right) / 2;
    int leftDist = findClosest(left, mid);
    int rightDist = findClosest(mid + 1, right);
    int minDist = min(leftDist, rightDist);

    vector<pair<int, int>> nearMid;
    int xCenter = pointList[mid].first;
    for (int i = left; i <= right; ++i) {
        int dx = pointList[i].first - xCenter;
        if (dx * dx < minDist)
            nearMid.emplace_back(pointList[i]);
    }

    return processStrip(nearMid, minDist);
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> nodeCount >> edgeCount >> shopCount;
    for (int i = 1; i <= shopCount; ++i) {
        cin >> shops[i];
    }

    while (edgeCount--) {
        int from, to, type, weight;
        cin >> from >> to >> type >> weight;
        int effectiveWeight = (type == 2 ? -weight : weight);
        graph[from].emplace_back(to, effectiveWeight);
    }

    traverse(1, 0, 0);
    sort(pointList.begin(), pointList.end());
    cout << findClosest(0, pointList.size() - 1) << '\n';
}