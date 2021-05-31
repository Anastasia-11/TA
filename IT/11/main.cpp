#pragma comment(linker, "/STACK:167772160")
#include <vector>
#include <deque>
#include <iostream>

const int dx[] = {2, 1, -1, -2, -2, -1, 1, 2};
const int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
std::vector<std::vector<int>> board;
std::vector<std::pair<int, int>> path;
std::pair<int, int> start, target;
long long n, m;
std::vector<std::vector<bool>> visited;
std::vector<std::vector<std::pair<int, int>>> paths;
std::vector<std::vector<int>> marks;
int mark = 0;

void findWays(int x, int y);
bool isValid(int x, int y);
void printPaths(const std::vector<std::vector<std::pair<int, int>>>& vector);
void updateMinPaths();
void bfs(int x, int y);

bool isOptimal(int fromX, int fromY, int toX, int toY);

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    long long k;
    fscanf(stdin, "%lli %lli %lli", &n, &m, &k);

    board.resize(m, std::vector<int>(n, 0));
    visited.resize(m, std::vector<bool>(n, false));
    marks.resize(m, std::vector<int>(n, 0));

    for (int i = 0; i < k; ++i) {
        int x, y;
        fscanf(stdin, "%i %i", &y, &x);
        board[x][y] = 1;
        marks[x][y] = -1;
    }

    fscanf(stdin, "%i %i", &start.first, &start.second);
    fscanf(stdin, "%i %i", &target.first, &target.second);

    if(start == target) {
        fprintf(stdout, "%s", "no_solutions");
        return 0;
    }

    bfs(start.first, start.second);
    visited.clear();
    visited.resize(m, std::vector<bool>(n, false));
    findWays(start.first, start.second);

    if(paths.empty()) {
        fprintf(stdout, "%s", "no_solutions");
    } else {
        printPaths(paths);
    }
}

void printPaths(const std::vector<std::vector<std::pair<int, int>>>& vector) {
    for (const auto & currPath : vector) {
        fprintf(stdout, "%i", currPath.size() - 1);
        for (const auto & item : currPath) {
            fprintf(stdout, "%c", '\n');
            fprintf(stdout, "%i %i", item.first, item.second);
        }
        fprintf(stdout, "%c", '\n');
    }
}

void findWays(int x, int y) {
    visited[y][x] = true;
    path.emplace_back(x, y);
    if(x == target.first && y == target.second) {
        updateMinPaths();
    } else {
        int currX, currY;
        for (int i = 0; i < 8; ++i) {
            currX = x + dx[i];
            currY = y + dy[i];
            if(isValid(currX, currY) && board[currY][currX] != 1 && !visited[currY][currX] && isOptimal(x, y, currX, currY)) {
                findWays(currX, currY);
            }
        }
    }
    visited[path.back().second][path.back().first] = false;
    path.pop_back();
}

bool isOptimal(int fromX, int fromY, int toX, int toY) {
    return (marks[toY][toX] - marks[fromY][fromX]) == 1;
}

void updateMinPaths() {
    if(paths.empty() || paths[0].size() == path.size()) {
        paths.push_back(path);
    } else if(path.size() < paths[0].size()) {
        paths.clear();
        paths.push_back(path);
    }
}

bool isValid(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < m;
}

void bfs(int x, int y) {
    std::deque<std::pair<int, int>> d;

    visited[y][x] = true;
    d.emplace_back(x, y);

    std::pair<int, int> pair;
    while (!d.empty()) {
        pair = d[0];
        d.pop_front();

        mark = marks[pair.second][pair.first] + 1;

        for (int i = 0; i < 8; ++i) {
            int currX = pair.first + dx[i];
            int currY = pair.second + dy[i];
            auto temp = std::pair<int, int>(currX, currY);
            if(isValid(currX, currY) && board[currY][currX] != 1 && !visited[currY][currX]
                && temp != start) {
                visited[currY][currX] = true;
                marks[currY][currX] = mark;
                d.emplace_back(currX, currY);
            }
        }
    }
}
