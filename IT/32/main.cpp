#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class DSU {
public:
    DSU(int n) {
        for (int i = 0; i < n; ++i) {
            parent.push_back(i);
            size.push_back(1);
        }
    }

    int FindSet(int i) {
        if(i == parent[i]) {
            return i;
        }
        parent[i] = FindSet(parent[i]);
        return parent[i];
    }

    bool Union(int x, int y) {
        x = FindSet(x);
        y = FindSet(y);
        if(x != y) {
            if(size[x] < size[y]) {
                std::swap(x, y);
            }
            parent[y] = x;
            size[x] += size[y];
            return true;
        }
        return false;
    }

private:
    std::vector<int> size;
    std::vector<int> parent;
};

void getValues(char* buf, int& n, int& m);
void getStatement(char* buf, std::vector<std::pair<char, std::pair<int, int>>>& v);

int main() {
    FILE* fin = fopen("equal-not-equal.in", "r");
    FILE* fout = fopen("equal-not-equal.out", "w");

    int n, m;
    const int BUF_SIZE = 20;
    char buf[BUF_SIZE];

    fgets(buf, BUF_SIZE, fin);
    getValues(buf, n, m);

    DSU dsu(n);

    std::vector<std::pair<char, std::pair<int, int>>> v;
    for (int i = 0; i < m; ++i) {
        fgets(buf, BUF_SIZE, fin);
        getStatement(buf, v);
        if(v[i].first == '=')  {
            dsu.Union(v.back().second.first - 1, v.back().second.second - 1);
        }
    }

    int set1, set2;
    for (int i = 0; i < m; ++i) {
        set1 = dsu.FindSet(v[i].second.first - 1);
        set2 = dsu.FindSet(v[i].second.second - 1);
        if(v[i].first == '!' && set1 == set2) {
            fprintf(fout, "%s", "No");
            return 0;
        }
    }
    fprintf(fout, "%s", "Yes");
    return 0;
}

void getStatement(char* buf, std::vector<std::pair<char, std::pair<int, int>>>& v) {
    std::string value1, value2;
    size_t size = strlen(buf);
    int i = 1;
    while (isdigit(buf[i]) && i < size) {
        value1 += buf[i++];
    }

    char sign = buf[++i];
    i += 4;

    while (isdigit(buf[i]) && i < size) {
        value2 += buf[i++];
    }

    v.emplace_back(sign, std::pair(std::stoi(value1), std::stoi(value2)));
}

void getValues(char* buf, int &n, int &m) {
    std::string sn, sm;
    size_t size = strlen(buf);
    int i = 0;
    while (isdigit(buf[i]) && i < size) {
        sn += buf[i++];
    }
    i++;
    while (isdigit(buf[i]) && i < size) {
        sm += buf[i++];
    }
    n = std::stoi(sn);
    m = std::stoi(sm);
}
