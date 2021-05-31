#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

unsigned long long
getMinSeconds(const std::vector<unsigned int> &sec1, const std::vector<unsigned int> &sec2, const std::vector<unsigned int> &sec3);

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int size;
    fscanf_s(stdin, "%i", &size);

    std::vector<unsigned int> sec1(size, 0), sec2(size, 0), sec3(size, 0);

    for (int i = 0; i < size; ++i) {
        fscanf_s(stdin, "%i", &sec1[i]);
        fscanf_s(stdin, "%i", &sec2[i]);
        fscanf_s(stdin, "%i", &sec3[i]);
    }

    fprintf(stdout, "%llu", getMinSeconds(sec1, sec2, sec3));
    return 0;
}

unsigned long long
getMinSeconds(const std::vector<unsigned int> &sec1, const std::vector<unsigned int> &sec2, const std::vector<unsigned int> &sec3) {
    int size = sec1.size();
    std::vector<unsigned long long> seconds(size, 0);

    seconds[0] = sec1[0];

    if(size >= 2) {
        seconds[1] = std::min(sec1[0] + sec1[1], sec2[0]);
    }
    if(size >= 3) {
        seconds[2] = std::min(seconds[1] + sec1[2], (unsigned long long)sec3[0]);
        seconds[2] = std::min((unsigned long long)(sec2[1] + seconds[0]), seconds[2]);
    }

    for (int i = 3; i < size; ++i) {
        seconds[i] = std::min(seconds[i - 1] + sec1[i], seconds[i - 3] + sec3[i - 2]);
        seconds[i] = std::min((unsigned long long)(sec2[i - 1] + seconds[i - 2]), seconds[i]);
    }

    return seconds[size - 1];
}
