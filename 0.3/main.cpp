#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    long value, size;
    std::vector<long> nodes(1, 0);

    fscanf(stdin, "%ld", &size);

    for(long i = 0; i < size; i ++) {
        fscanf(stdin, "%ld ", &value);
        nodes.push_back(value);
    }

    for (int i = 1; 2 * i <= size; ++i) {
        if(2 * i + 1 <= size) {
            if(nodes[2 * i + 1] < nodes[i] || nodes[2 * i] < nodes[i]) {
                fprintf(stdout, "%s", "No");
                return 0;
            }
        } else if(2 * i <= size) {
            if(nodes[2 * i] < nodes[i]) {
                fprintf(stdout, "%s", "No");
                return 0;
            }
        }
    }
    fprintf(stdout, "%s", "Yes");
    return 0;
}
