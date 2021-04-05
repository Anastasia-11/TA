#include <iostream>
#include <vector>

unsigned long long findBinomialCoefficient(int n, int k);

int main() {
    int n, k;
    std::cin >> n >> k;
    std::cout << findBinomialCoefficient(n, k);
    return 0;
}

unsigned long long findBinomialCoefficient(int n, int k) {
    if(n < k) {
        return 0;
    } else if(k == 0) {
        return 1;
    }

    const int MODULE = 1000000007;
    unsigned long long result = 1;

    std::vector<unsigned long long> denoms(k + 1, 0);
    denoms.at(1) = 1;

    for (int i = 2; i < k + 1; ++i) {
        denoms.at(i) = MODULE - (MODULE / i) * denoms[MODULE % i] % MODULE;
    }

    result = ((result % MODULE) * ((n - k + 1) % MODULE)) % MODULE;

    for (int i = 2; i < k + 1; ++i) {
        result = ((result % MODULE) * ((n - k + i) % MODULE)) % MODULE;
        result = ((result % MODULE) * (denoms[i] % MODULE)) % MODULE;
    }

    return result;
}
