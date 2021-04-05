#include <vector>
#include <algorithm>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int size, value;
    std::vector<int> n;

    fscanf(stdin,  "%i", &size);
    fscanf(stdin, "%i", &value);

    n.push_back(value);

    for (int i = 0; i < size; ++i) {
        fscanf(stdin, "%i", &value);
        n.push_back(value);
        fscanf(stdin, "%i", &value);
    }

    std::vector<std::vector<long>> F;

    for (int i = 0; i < size; ++i) {
        std::vector<long> v(size, 0);
        F.push_back(v);
    }

    for (int p = 1; p < size; ++p) {
        for (int i = 0; i < size - p; ++i) {
            long min = LONG_MAX;
            int j = p + i;
            for (int k = i; k < j; ++k) {
                long current = F[i][k] + F[k + 1][j] + n[i] * n[k + 1] * n[j + 1];
                if(min > current) {
                    min = current;
                }
            }
            F[i][j] = min;
        }
    }
    fprintf(stdout, "%ld", F[0][size - 1]);
    return 0;
}

/*std::F<std::pair<int, int>> v;

    fscanf(stdin, "%i", &size);

    for (int i = 0; i < size; ++i) {
        fscanf(stdin, "%i", &value);
        v.emplace_back(value);
        fscanf(stdin, "%i", &value);
        v.emplace_back(value);
    }
    long result = 0, minSum = LONG_MAX, sum = 0;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < 2; j++) {
            sum +=v[i].;
            if(minSum > sum) {
                minSum = sum;
            }
            sum = 0;
        }
    }
    fprintf(stdout, "%s", std::to_string(result).c_str());*/