#include <iostream>
#include <fstream>
#include <string>
#include <stack>

std::pair<std::string, int> checkBraces(const std::string& str);

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    std::string str;
    std::getline(in, str);
    in.close();

    std::pair<std::string, int> answer = checkBraces(str);

    if(answer.first == "YES") {
        out << answer.first;
    } else {
        out << answer.first << '\n' << answer.second;
    }

    out.close();
    return 0;
}

std::pair<std::string, int> checkBraces(const std::string &str) {
    std::stack<char> stack;
    size_t size = (int)str.size();

    int i = 0;
    while (i < size) {
        if(str[i] == '(' || str[i] == '[' || str[i] == '{') {
            stack.push(str[i]);
        } else {
            switch (str[i]) {
                case ')': {
                    if(!stack.empty() && stack.top() == '(') {
                        stack.pop();
                        break;
                    } else {
                        return std::pair("NO", i);
                    }
                }
                case ']': {
                    if(!stack.empty() && stack.top() == '[') {
                        stack.pop();
                        break;
                    } else {
                        return std::pair("NO", i);
                    }
                }
                case '}': {
                    if(!stack.empty() && stack.top() == '{') {
                        stack.pop();
                        break;
                    } else {
                        return std::pair("NO", i);
                    }
                }
            }
        }
        i++;
    }
    size = stack.size();
    if(size == 0) {
        return std::pair("YES", 0);
    }
    else {
        if(i == str.size()) {
            return std::pair("NO", i);
        }
        if(i != size) {
            i -= size;
        }
        return std::pair("NO", i);
    }
}
