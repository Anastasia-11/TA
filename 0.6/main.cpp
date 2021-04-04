#include <iostream>
#include <vector>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    fscanf(stdin, "%i", &n);
    fscanf(stdin, "%i", &m);

    std::vector<std::pair<int, std::vector<int>>> v(n, std::pair(0, std::vector<int>()));

    int x, y;
    for (int i = 0; i < m; ++i) {
        fscanf(stdin, "%i", &x);
        fscanf(stdin, "%i", &y);

        v[x - 1].first++;
        v[x - 1].second.push_back(y);
        v[y - 1].first++;
        v[y - 1].second.push_back(x);
    }

    for (int i = 0; i < n; ++i) {
        fprintf(stdout, "%i", v[i].first);
        fprintf(stdout, "%c", ' ');
        for (int j = 0; j < v[i].first; ++j) {
            fprintf(stdout, "%i", v[i].second[j]);
            fprintf(stdout, "%c", ' ');
        }
        fprintf(stdout, "%c", '\n');
    }

    return 0;
}
