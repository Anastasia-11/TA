#include <iostream>
#include <vector>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    fscanf(stdin, "%i", &n);

    std::vector<int> v(n, 0);

    int x, y;
    for (int i = 0; i < n - 1; ++i) {
        fscanf(stdin, "%i", &x);
        fscanf(stdin, "%i", &y);

        v[y - 1] = x;
    }

    for(int item : v) {
        fprintf(stdout, "%i", item);
        fprintf(stdout, "%c", ' ');
    }
    return 0;
}