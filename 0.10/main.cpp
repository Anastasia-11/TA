#include <vector>
#include <queue>

std::vector<std::vector<std::pair<unsigned long long, unsigned  long long>>> g;
std::vector<bool> processed;
std::vector<unsigned long long> dist;

void distances(int start);

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    fscanf(stdin, "%i", &n);
    fscanf(stdin, "%i", &m);

    if(m == 0) {
        fprintf(stdout, "%i", 0);
        return 0;
    }

    g.resize(n, std::vector<std::pair<unsigned long long, unsigned long long>>());
    processed.resize(n, false);
    dist.resize(n, LLONG_MAX);

    unsigned long long u, v, w;
    for (int i = 0; i < m; ++i) {
        fscanf(stdin, "%llu %llu %llu", &u, &v, &w);
        g[u - 1].emplace_back(v - 1, w);
        g[v - 1].emplace_back(u - 1, w);
    }

    distances(0);

    fprintf(stdout, "%llu", dist[n - 1]);
    return 0;
}

void distances(int start) {
    auto comparator = [](std::pair<unsigned long long, unsigned long long> a, std::pair<unsigned long long, unsigned long long> b) { return a.second > b.second; };
    std::priority_queue<std::pair<unsigned long long, unsigned long long>, std::vector<std::pair<unsigned long long, unsigned long long>>, decltype(comparator)> q(comparator);
    q.push(std::pair(0, start));

    while (!q.empty()) {
        std::pair<unsigned long long, unsigned long long> p = q.top();
        q.pop();

        if(processed[p.first]) {
            continue;
        }

        processed[p.first] = true;
        dist[p.first] = p.second;

        for (unsigned long long i = 0; i < g[p.first].size(); ++i) {
            unsigned long long u = g[p.first][i].first;
            unsigned long long dv = p.second;
            unsigned long long cu = g[p.first][i].second;
            if(!processed[u] && dv + cu < dist[u]) {
                dist[u] = dv + cu;
                q.push(std::pair(u, dv + cu));
            }
        }
    }
}
