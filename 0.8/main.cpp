#include <iostream>
#include <vector>
#include <deque>

std::vector<std::vector<int>> v;
std::vector<int> marks;
std::vector<bool> visited;
int mark = 1;

void fillMatrix(int n);
void bfs(const int &vertex);

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    fscanf(stdin, "%i", &n);

    marks.resize(n, -1);
    visited.resize(n, false);
    fillMatrix(n);

    for (int vertex = 0; vertex < n; vertex++) {
        if(!visited[vertex]) {
            bfs(vertex);
        }
    }

    for(int item : marks) {
        fprintf(stdout, "%i", item);
        fprintf(stdout, "%c", ' ');
    }

    return 0;
}

void bfs(const int &vertex) {
    std::deque<int> d;

    visited[vertex] = true;
    d.push_back(vertex);

    int tVertex;
    while (!d.empty()) {
        tVertex = d[0];
        d.pop_front();

        marks[tVertex] = mark++;

        for(int i = 0; i < v.size(); i++) {
            if(v[tVertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                d.push_back(i);
            }
        }
    }
}

void fillMatrix(int n) {
    v.resize(n, std::vector(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fscanf(stdin, "%i", &v[i][j]);
        }
    }
}