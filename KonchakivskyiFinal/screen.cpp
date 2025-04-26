#include "screen.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <sstream>

Screen::Screen(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string line;
    std::string paragraph;

    while (std::getline(file, line)) {
        if (line.empty() && !paragraph.empty()) {
            text.push_back(paragraph);
            paragraph.clear();
        }
        else if (!line.empty()) {
            if (!paragraph.empty()) {
                paragraph += " ";
            }
            paragraph += line;
        }
    }

    if (!paragraph.empty()) {
        text.push_back(paragraph);
    }

    file.close();
}

Screen::Screen(const Screen& other)
    : text(other.text),
    position(other.position),
    linesPerScreen(other.linesPerScreen) {
    std::cout << "Screen copy constructor called" << std::endl;
}

Screen::Screen(Screen&& other) noexcept
    : text(std::move(other.text)),
    position(other.position),
    linesPerScreen(other.linesPerScreen) {
    other.position = 0;
    std::cout << "Screen move constructor called" << std::endl;
}

Screen& Screen::operator=(const Screen& other) {
    if (this != &other) {
        text = other.text;
        position = other.position;
        linesPerScreen = other.linesPerScreen;
    }
    std::cout << "Screen copy assignment called" << std::endl;
    return *this;
}

Screen& Screen::operator=(Screen&& other) noexcept {
    if (this != &other) {
        text = std::move(other.text);
        position = other.position;
        linesPerScreen = other.linesPerScreen;
        other.position = 0;
    }
    std::cout << "Screen move assignment called" << std::endl;
    return *this;
}

void Screen::scrollForward() {
    if (position + linesPerScreen < text.size()) {
        position++;
    }
}

void Screen::scrollBackward() {
    if (position > 0) {
        position--;
    }
}

void Screen::insertLine(const std::string& line) {
    text.insert(text.begin() + position, line);
}

void Screen::deleteLine() {
    if (position < text.size()) {
        text.erase(text.begin() + position);
    }
}

void Screen::modifyLine(const std::string& newLine) {
    if (position < text.size()) {
        text[position] = newLine;
    }
}

void Screen::display() const {
    std::cout << "--------------- Screen Content (position " << position << ") ---------------" << std::endl;

    size_t endPosition = std::min(position + linesPerScreen, text.size());

    for (size_t i = position; i < endPosition; ++i) {
        std::cout << "[" << i - position << "] " << text[i] << std::endl;
    }

    std::cout << "--------------- End of Screen ------------------" << std::endl;
}