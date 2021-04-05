#include <iostream>
#include <vector>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    unsigned long long value;
    std::vector<int> res;

    fscanf(stdin,  "%llu", &value);

    if(value % 2 == 1) {
        value--;
        fprintf(stdout, "%s", "0\n");
    }

    while(value > 0) {
        int step = -1;
        unsigned long long num = 1;
        while(num <= value) {
            step++;
            num <<= 1;
        }
        res.push_back(step);
        num >>= 1;
        value -= num;
    }

    for (long i = res.size() - 1; i >= 0; --i) {
        fprintf(stdout, "%i", res[i]);
        fprintf(stdout, "%c", '\n');
    }

    return 0;
}
