#include <iostream>
#include <vector>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    fscanf(stdin, "%i", &n);

    std::vector<std::vector<int>> v(n, std::vector(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fscanf(stdin, "%i", &v[i][j]);
        }
    }

    bool flag = false;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(v[j][i]) {
                fprintf(stdout, "%i", j + 1);
                flag = true;
            }
        }
        if(!flag) {
            fprintf(stdout, "%i", 0);
        }
        flag = false;
        fprintf(stdout, "%c", ' ');
    }
    return 0;
}
