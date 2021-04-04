#include <iostream>
#include <vector>

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

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int amountOfCities;
    fscanf(stdin, "%i", &amountOfCities);

    DSU dsu(amountOfCities);

    int amountOfRequests;
    fscanf(stdin, "%i", &amountOfRequests);

    int city1, city2, components = amountOfCities;
    for (int i = 0; i < amountOfRequests; ++i) {
        fscanf(stdin, "%i", &city1);
        fscanf(stdin, "%i", &city2);

        if(dsu.Union(city1 - 1, city2 - 1)) {
            components--;
        }
        fprintf(stdout, "%i", components);
        fprintf(stdout, "%c", '\n');
    }
    fprintf(stdout, "%i", dsu.FindSet(2));
    return 0;
}