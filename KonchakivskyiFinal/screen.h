#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <set>
#include <memory>
#include <algorithm>
#include <iostream>
#include <functional>

class Screen {
private:
    std::vector<std::string> text;
    size_t position = 0;
    size_t linesPerScreen = 5;

public:
    Screen(const std::string& filename);

    Screen(const Screen& other);

    Screen(Screen&& other) noexcept;

    const std::vector<std::string>& getText() const { return text; }

    Screen& operator=(const Screen& other);

    Screen& operator=(Screen&& other) noexcept;

    void scrollForward();
    void scrollBackward();

    void insertLine(const std::string& line);
    void deleteLine();
    void modifyLine(const std::string& newLine);

    void display() const;
};

#endif