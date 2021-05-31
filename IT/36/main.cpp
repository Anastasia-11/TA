#include <vector>
#include <iostream>
#include <algorithm>

const long SIZE = 300000 * 4;

class IntervalTree {
public:
    IntervalTree(const std::vector<long long>& vector, long n) : n(n) {
        tree.resize(SIZE);
        Build(vector, 1, 0, n - 1);
    }

    long long FindSum(int left, int right) {
        return FindSum(1, 0, n - 1, left, right);
    }

    void Add(int index, int value) {
        Add(1, 0, n - 1, index, value);
    }

private:
    long long FindSum(int i, int treeLeft, int treeRight, int left, int right) {
        if (left > right) {
            return 0;
        }
        if (left == treeLeft && right == treeRight) {
            return tree[i];
        }
        int root = (treeLeft + treeRight) / 2;
        return FindSum(i * 2, treeLeft, root, left, std::min(right, root))
               + FindSum(i * 2 + 1, root + 1, treeRight, std::max(left, root + 1), right);
    }

    void Add(int i, int l, int r, int index, int value) {
        if (l == r) {
            tree[i] += value;
        }
        else {
            int middle = (l + r) / 2;
            if (index <= middle) {
                Add(i * 2, l, middle, index, value);
            }
            else {
                Add(i * 2 + 1, middle + 1, r, index, value);
            }
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
        }
    }

    void Build(const std::vector<long long>& vector, int i, int l, int r) {
        if (l == r)
            tree[i] = vector[l];
        else {
            int middle = (l + r) / 2;
            Build(vector, i * 2, l, middle);
            Build(vector, i * 2 + 1, middle + 1, r);
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
        }
    }

    std::vector<long long> tree;
    long n;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    fscanf(stdin, "%i", &n);

    long value1, value2;
    std::vector<std::pair<long, long>> v;

    long maxX = -1;
    for (int i = 0; i < n; ++i) {
        fscanf(stdin, "%li %li", &value1, &value2);
        v.emplace_back(std::pair(value1, value2));
        if(maxX < value1) {
            maxX = value1;
        }
    }

    std::vector<long> levels(n, 0);
    std::vector<long long> sum(maxX + 1, 0); // +1 bc x is from [0, maxX]

    IntervalTree tree(sum, sum.size());

    for (auto & item : v) {
        unsigned long long summary = tree.FindSum(0, item.first);
        tree.Add(item.first, 1);
        levels[summary]++;
    }

    for(auto item : levels) {
        fprintf(stdout, "%li", item);
        fprintf(stdout, "%c", '\n');
    }

    return 0;
}
