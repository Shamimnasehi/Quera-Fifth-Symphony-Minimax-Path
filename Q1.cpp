/*
 * Q1 - Fifth Symphony (Minimax Path in a Grid)
 *
 * Given an n x m grid of heights, find a path from (0,0) to (n-1,m-1)
 * (4-directional moves) that minimizes the maximum absolute height
 * difference between two consecutive cells on the path.
 *
 * Approach: Dijkstra with a modified relaxation rule.
 *   dist[v] = smallest possible "maximum jump" over all paths from (0,0) to v.
 *   Relaxation: dist[v] = min(dist[v], max(dist[u], |h[u] - h[v]|))
 * Extending a path never decreases its maximum edge, so Dijkstra's greedy
 * argument still holds.
 *
 * Complexity: O(n*m*log(n*m)) time, O(n*m) memory.
 */

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Grid stored as a flat array: cell (r, c) -> index r * m + c.
    vector<int> height(n * m);
    for (int i = 0; i < n * m; i++) {
        cin >> height[i];
    }

    // dist[i] = best (smallest) maximum jump found so far to reach cell i.
    vector<int> dist(n * m, INT_MAX);

    // Min-heap of (jump, cell index).
    using State = pair<int, int>;
    priority_queue<State, vector<State>, greater<State>> pq;

    dist[0] = 0;
    pq.push({0, 0});

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    const int target = n * m - 1;

    while (!pq.empty()) {
        auto [jump, u] = pq.top();
        pq.pop();

        // Skip stale heap entries.
        if (jump != dist[u]) continue;

        // The first time the target is popped, its answer is final.
        if (u == target) break;

        int r = u / m;
        int c = u % m;

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;

            int v = nr * m + nc;
            int newJump = max(jump, abs(height[u] - height[v]));

            if (newJump < dist[v]) {
                dist[v] = newJump;
                pq.push({newJump, v});
            }
        }
    }

    cout << dist[target] << "\n";
    return 0;
}
