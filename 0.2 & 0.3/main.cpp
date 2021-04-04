#include <iostream>
#include <vector>
#include <algorithm>

int amountOfCities, amountOfWays, amountOfCollapses;
std::vector<std::pair<int, int>> ways;
std::vector<int> collapsesIndexes;

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

void preBuild(DSU &dsu, int& components);
void fillVectors();

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    fscanf(stdin, "%i", &amountOfCities);
    fscanf(stdin, "%i", &amountOfWays);
    fscanf(stdin, "%i", &amountOfCollapses);

    DSU dsu(amountOfCities);
    collapsesIndexes.resize(amountOfCollapses);

    fillVectors();

    int components = amountOfCities, counter = 0;

    preBuild(dsu, components);

    if(components == 1) {
        for (int i = 0; i < amountOfCollapses; ++i) {
            fprintf(stdout, "%i", 1);
        }
        return 0;
    }

    for (int i = amountOfCollapses - 1; i >= 0; i--) {
        counter++;
        auto ind = collapsesIndexes[i] - 1;
        if(dsu.Union(ways[ind].first - 1, ways[ind].second - 1)) {
            components--;
        }
        if(components == 1) {
            for (int k = 0; k < amountOfCollapses - counter; ++k) {
                fprintf(stdout, "%i", 1);
            }
            for (int j = 0; j < counter; ++j) {
                fprintf(stdout, "%i", 0);
            }
            return 0;
        }
    }
    return 0;
}

void fillVectors() {
    int city1, city2;
    for (int i = 0; i < amountOfWays; ++i) {
        fscanf(stdin, "%i", &city1);
        fscanf(stdin, "%i", &city2);
        ways.emplace_back(city1, city2);
    }

    for (int i = 0; i < amountOfCollapses; ++i) {
        fscanf(stdin, "%i", &collapsesIndexes[i]);
    }
}

void preBuild(DSU &dsu, int& components) {
    std::vector<int> sortedIndexes = collapsesIndexes;
    std::sort(sortedIndexes.begin(), sortedIndexes.end());

    if(amountOfCollapses < amountOfWays) {
        for (int i = 0; i < amountOfWays; i++) {
            if(!std::binary_search(sortedIndexes.begin(), sortedIndexes.end(), i + 1)) {
                if(dsu.Union(ways[i].first - 1, ways[i].second - 1)) {
                    components--;
                }
            }
        }
    }
}