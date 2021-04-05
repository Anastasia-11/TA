#include <string>
#include <iostream>

int main() {
    int arraySize, value;

    std::cin >> arraySize;

    int* arr = new int[arraySize];

    for (int i = 0; i < arraySize; ++i) {
        std::cin >> value;
        arr[i] = value;
    }

    int requestCount;
    std::string result;

    std::cin >> requestCount;

    int k, l, r;
    bool itemInArr;
    for (int i = 0; i < requestCount; ++i) {
        std::cin >> value;
        itemInArr = false;
        l = 0, r = arraySize;
        while(l < r) {
            k = floor((l + r) / 2);
            if(value <= arr[k]) {
                if(!itemInArr && value == arr[k]) {
                    itemInArr = true;
                }
                r = k;
            } else {
                l = k + 1;
            }
        }
        result += itemInArr ? "1" : "0";
        result += " " + std::to_string(l);
        l = 0, r = arraySize;
        while(l < r) {
            k = floor((l + r) / 2);
            if(value < arr[k]) {
                r = k;
            } else {
                l = k + 1;
            }
        }
        result += " " + std::to_string(l) + '\n';
    }
    std::cout << result;
    return 0;
}