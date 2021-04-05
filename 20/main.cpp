#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

std::vector<std::vector<int>> createMatrix(int size);
std::pair<std::string, int> findMaxPalindrom(int i, int j);
int getLengthOfMaxPalindrom(int i, int j);
std::string getMaxPalindrom(int left, int right, int pLeft, int pRight);

std::vector<std::vector<int>> v;
std::string str;

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    std::getline(in, str);
    int size = str.size();

    v = createMatrix(size);
    std::pair<std::string, int> pair = findMaxPalindrom(0, size - 1);
    out << pair.second << '\n' << pair.first;

    in.close();
    out.close();
    return 0;
}

std::pair<std::string, int> findMaxPalindrom(int i, int j) {
    int length = getLengthOfMaxPalindrom(i, j);
    std::string pal = getMaxPalindrom(i, j, 0, length - 1);
    return std::pair<std::string, int>(pal, length);
}

std::vector<std::vector<int>> createMatrix(int size) {
    std::vector<std::vector<int>> vector(size, std::vector<int>(size, 0));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if(i > j) {
                vector[i][j] = 0;
            } else if(i < j) {
                vector[i][j] = -1;
            } else {
                vector[i][j] = 1;
            }
        }
    }

    return vector;
}

int getLengthOfMaxPalindrom(int i, int j) {
    if(v[i][j] == -1) {
        v[i][j] = str[i] == str[j] ?
                  getLengthOfMaxPalindrom(i + 1, j - 1) + 2 :
                  std::max(getLengthOfMaxPalindrom(i + 1, j),
                         getLengthOfMaxPalindrom(i, j - 1));
    }
    return v[i][j];
}

std::string getMaxPalindrom(int left, int right, int pLeft, int pRight) {
    std::string pal;
    pal.resize(pRight + 1, ' ');
    while(left <= right) {
        if(left == right && v[left][right] == 1) {
            pal[pLeft++] = str[left++];
        } else if(str[left] == str[right]) {
            pal[pLeft++] = str[left++];
            pal[pRight--] = str[right--];
        } else if(v[left + 1][right] >= v[left][right - 1]) {
            left++;
        } else {
            right--;
        }
    }
    return pal;
}