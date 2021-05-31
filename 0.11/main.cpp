#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

int n, m;
std::vector<bool> visited;
std::vector<int> parent;
std::vector<std::vector<long long>> vector;

unsigned long long maxFlow(int start, int target) {
    unsigned long long maxFlow = 0;

    while(true) {
        parent.resize(n, -1);
        std::queue<int> queue;
        visited.clear();
        visited.resize(n, false);

        visited[start] = true;
        queue.push(start);

        while(!queue.empty()) {
            int current = queue.front();
            queue.pop();

            for (int i = 0; i < n; ++i) {
                if(!visited[i] && vector[current][i] > 0) {
                    parent[i] = current;
                    visited[i] = true;
                    queue.push(i);
                }
            }
        }

        if(!visited[target]) {
            break;
        }

        long long currMinCap = LLONG_MAX;
        int curr = target;
        while (curr != start) {
            currMinCap = std::min(currMinCap, vector[parent[curr]][curr]);
            curr = parent[curr];
        }

        curr = target;
        while (curr != start) {
            vector[parent[curr]][curr] -= currMinCap;
            vector[curr][parent[curr]] += currMinCap;
            curr = parent[curr];
        }

        maxFlow += currMinCap;
    }
    return maxFlow;
}

int main() {
    std::cin >> n >> m;

    if(n == 1 || m == 0) {
        std::cout << 0;
        return 0;
    }
    visited.resize(n, false);
    vector.resize(n, std::vector<long long>(n, 0));

    int v1, v2, w;
    for (int i = 0; i < m; ++i) {
        std::cin >> v1 >> v2 >> w;
        vector[v1 - 1][v2 - 1] += w;
    }

    std::cout << maxFlow(0, n - 1);
    return 0;
}
