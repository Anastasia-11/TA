#include <iostream>
#include <vector>

std::vector<std::vector<int>> v;
std::vector<bool> visited;
std::vector<int> ord;
int index = 0;

void dfs(int vertex);

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    fscanf(stdin, "%i", &n);

    v.resize(n, std::vector(n, 0));
    visited.resize(n, false);
    ord.resize(n, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fscanf(stdin, "%i", &v[i][j]);
        }
    }

    for (int i = 0; i < n; ++i) {
        if(!visited[i]) {
            dfs(i);
        }
    }

    for (int item : ord) {
        fprintf(stdout, "%i", item);
        fprintf(stdout, "%c", ' ');
    }

    return 0;
}

void dfs(int vertex) {
    visited[vertex] = true;

    ord[vertex] = ++index;

    for(int i = 0; i < ord.size(); i++) {
        if(v[vertex][i] == 1 && !visited[i]) {
            dfs(i);
        }
    }
}
