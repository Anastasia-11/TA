#include <iostream>
#include <string>
#include <algorithm>

bool isMatchesPattern(const std::string& word, const std::string& pattern);
void checkInput(std::string &word, std::string &pattern);

int main() {
    std::string word, pattern;
    std::cin >> word >> pattern;
    checkInput(word, pattern);
    isMatchesPattern(word, pattern) ? std::cout << "YES" : std::cout << "NO";
    return 0;
}

void checkInput(std::string &word, std::string &pattern) {
    int p1 = std::count(pattern.begin(), pattern.end(), '*');
    if(p1) { return; }
    int p2 = std::count(pattern.begin(), pattern.end(), '?');
    if(!p2) { 
        std::swap(word, pattern); 
    }
}

bool isMatchesPattern(const std::string &word, const std::string &pattern) {
    if(!word.empty()) {
        if(pattern.empty()) {
            return false;
        }
        std::string w = word, p = pattern;
        if(word[word.size() - 1] == pattern[pattern.size() - 1] || pattern[pattern.size() - 1] == '?') {
            w.pop_back();
            p.pop_back();
            return isMatchesPattern(w, p);
        } else if(pattern[pattern.size() - 1] == '*') {
            std::string newPattern = pattern, newWord = word;
            newPattern.pop_back();
            newWord.pop_back();
            return isMatchesPattern(newWord, pattern) || isMatchesPattern(word, newPattern);
        } else {
            return false;
        }
    }
    return std::count(pattern.begin(), pattern.end(), '*') == pattern.size();
}
