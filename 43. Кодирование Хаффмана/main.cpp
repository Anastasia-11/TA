#include <iostream>
#include <queue>
#include <algorithm>

int main() {
    freopen("huffman.in", "r", stdin);
    freopen("huffman.out", "w", stdout);

    int size;
    std::priority_queue<long long,std::vector<long long>,std::greater<>> q;
    long long value;

    fscanf(stdin, "%i", &size);

    for (int i = 0; i < size; ++i) {
        fscanf(stdin, "%lli", &value);
        q.push(value);
    }

    long long result = 0, sum = 0;

    while (q.size() != 1) {
        sum += q.top();
        q.pop();
        sum += q.top();
        q.pop();
        result += sum;
        q.push(sum);
        sum = 0;
    }

    fprintf(stdout, "%lld", result);
    return 0;
}
