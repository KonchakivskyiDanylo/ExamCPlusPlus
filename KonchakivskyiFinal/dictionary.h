#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <set>
#include <memory>
#include <algorithm>
#include <iostream>
#include <functional>

enum class WordStatus {
    New,
    Learning,
    Learned,
    Ignored
};

class Dictionary {
private:
    std::map<std::string, size_t> wordFrequency;
    std::map<std::string, WordStatus> foreignWords;

public:
    Dictionary(const std::string& filename);

    Dictionary(const Screen& screen);

    Dictionary() = default;

    Dictionary& operator+=(const Dictionary& other);

    Dictionary operator+(const Dictionary& other) const;

    Dictionary intersection(const Dictionary& other) const;

    void setWordStatus(const std::string& word, WordStatus status);

    void display(bool byFrequency = false) const;

    std::vector<std::string> getWordsByStatus(WordStatus status) const;
};

#endif