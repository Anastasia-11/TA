#include <queue>
#include <vector>
#include <iostream>

auto comp = [](std::pair<int, int> a, std::pair<int, int> b) {
    return a.first + a.second <= b.first + b.second;
};

std::deque<std::pair<int, int>> deque;
std::vector<std::vector<std::pair<int,int>>> containers;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    fscanf(stdin, "%i", &n);

    int weight, volume;
    for (int i = 0; i < n; ++i) {
        fscanf(stdin, "%i %i", &weight, &volume);
        deque.emplace_back(weight, volume);
    }

    std::sort(deque.begin(), deque.end(), comp);

    /*for (auto p : deque) {
        std::cout << p.first << " " << p.second << '\n';
    }*/

    containers.emplace_back();
    containers[0].push_back(deque.back());
    int currWeight = deque.back().first, currVolume = deque.back().second;
    deque.pop_back();

    int index = 0;
    for (int i = 0; i < n - 1; ++i) {
        if(currWeight + deque.back().first >= 100 || currVolume + deque.back().second >= 100) {
            if(currWeight + deque.front().first >= 100 || currVolume + deque.front().second >= 100) {
                index++;
                currWeight = currVolume = 0;
                containers.emplace_back();
            } else {
                containers[index].push_back(deque.front());
                currWeight += deque.front().first;
                currVolume += deque.front().second;
                deque.pop_front();
                continue;
            }
        }
        containers[index].push_back(deque.back());
        currWeight += deque.back().first;
        currVolume += deque.back().second;
        deque.pop_back();
    }

    std::cout << containers.size();

    for (auto & container : containers) {
        std::cout << '\n';
        for (auto & item : container) {
            std::cout << item.first << ", " << item.second << "; ";
        }
    }

    return 0;
}
