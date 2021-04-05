#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

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

class Summator {
public:
    Summator(const std::vector<long>& vector, int size) {
        this->k = (int) sqrt((double)size) + 1;
        sum.resize(k);
        for (int i = 0; i < size; i++) {
            sum[i / k] += vector[i];
        }
    }

    void Add(std::vector<long>& vector, long i, long value) {
        vector[i] += value;
        this->sum[i / k] += value;
    }

    long long FindSum(const std::vector<long>& vector, long l, long r) {
        long sl = l / k;
        long sr = r / k;
        long long result = 0;

        if(sl == sr) {
            for (int i = l; i < r; ++i) {
                result += vector[i];
            }
        } else {
            for(int i = l; i <= (sl + 1) * k - 1; i++) {
                result += vector[i];
            }
            for(int i = sl + 1; i <= sr - 1; i++) {
                result += this->sum[i];
            }
            for(int i = sr * k; i < r; i++) {
                result += vector[i];
            }
        }
        return result;
    }

    const std::vector<long long> &getSum() const {
        return sum;
    }

    void setSum(const std::vector<long long> &vector) {
        this->sum = vector;
    }

    int getK() const {
        return k;
    }

    void setK(int i) {
        this->k = i;
    }

private:
    std::vector<long long> sum;
    int k;
};


int main() {
    long size;

    scanf("%li", &size);

    std::vector<long long> values(size);

    for (int i = 0; i < size; ++i) {
        scanf("%lli", &values[i]);
    }

    IntervalTree tree(values, size);
    //Summator summator(values, size);

    int val1, val2;
    std::string str;

    scanf("%li", &size);

    for (int i = 0; i < size; ++i) {
        std::cin >> str;
        scanf("%i", &val1);
        scanf("%i", &val2);
        if (str == "sum") {
            printf("%lli\n", tree.FindSum(val1, val2 - 1));
            //std::cout << summator.FindSum(values, val1, val2) << '\n';
        } else {
            tree.Add(val1, val2);
            //summator.Add(values, val1, val2);
        }
    }
    return 0;
}