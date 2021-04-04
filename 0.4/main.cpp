#include <iostream>
#include <vector>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    fscanf(stdin, "%i", &n);
    fscanf(stdin, "%i", &m);

    std::vector<std::vector<bool>> v(n, std::vector(n, false));

    int x, y;
    for (int i = 0; i < m; ++i) {
        fscanf(stdin, "%i", &x);
        fscanf(stdin, "%i", &y);
        v[x - 1][y - 1] = true;
        v[y - 1][x - 1] = true;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            v[i][j] ? fprintf(stdout, "%i", 1)
                    : fprintf(stdout, "%i", 0);
            fprintf(stdout, "%c", ' ');
        }
        fprintf(stdout, "%c", '\n');
    }
    return 0;
}
