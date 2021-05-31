#include <vector>
#include <algorithm>

int n, m;
std::vector<bool> visited;
std::vector<int> parent;
std::vector<std::vector<long long>> vector;

void dfs(int vertex) {
    visited[vertex] = true;

    for (int i = 0; i < n; ++i) {
        if(vector[vertex][i] > 0 && !visited[i]) {
            parent[i] = vertex;
            dfs(i);
        }
    }
}

unsigned long long maxFlow(int start, int target) {
    unsigned long long maxFlow = 0;

    while(true) {
        parent.resize(n, -1);
        visited.clear();
        visited.resize(n, false);

        dfs(start);

        // no way from start to target
        // the flow is maximal
        if(!visited[target]) {
            break;
        }

        // finding min capacity on the way
        long long currMinCap = LLONG_MAX;
        int curr = target;
        while (curr != start) {
            currMinCap = std::min(currMinCap, vector[parent[curr]][curr]);
            curr = parent[curr];
        }

        //changing min capacities on the way
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
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    fscanf(stdin, "%i %i", &n, &m);

    if(n == 1 || m == 0) {
        fprintf(stdout, "%i", 0);
        return 0;
    }
    visited.resize(n, false);
    vector.resize(n, std::vector<long long>(n, 0));

    int v;
    for (int i = 0; i < n; ++i) {
        while(true) {
            fscanf(stdin, "%i", &v);
            if(v != 0) {
                vector[i][v - 1] = 1;
            } else {
                break;
            }
        }
    }

    int start, target;
    fscanf(stdin, "%i %i", &start, &target);
    fprintf(stdout, "%lli", maxFlow(start - 1, target - 1));
    return 0;
}
