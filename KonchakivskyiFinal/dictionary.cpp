#include "screen.h"
#include"dictionary.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <sstream>

Dictionary::Dictionary(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Unable to open file: " + filename);
	}

	std::string word;
	while (file >> word) {
		word.erase(std::remove_if(word.begin(), word.end(),
			[](char c) { return std::ispunct(static_cast<unsigned char>(c)); }),
			word.end());

		std::transform(word.begin(), word.end(), word.begin(),
			[](unsigned char c) { return std::tolower(c); });

		if (!word.empty()) {
			wordFrequency[word]++;
		}
	}

	file.close();
}


Dictionary::Dictionary(const Screen& screen) {
	for (const auto& paragraph : screen.getText()) {
		std::istringstream iss(paragraph);
		std::string word;
		while (iss >> word) {
			word.erase(std::remove_if(word.begin(), word.end(),
				[](char c) { return std::ispunct(static_cast<unsigned char>(c)); }),
				word.end());

			std::transform(word.begin(), word.end(), word.begin(),
				[](unsigned char c) { return std::tolower(c); });

			if (!word.empty()) {
				wordFrequency[word]++;
			}
		}
	}
}

Dictionary& Dictionary::operator+=(const Dictionary& other) {
	for (const auto& [word, freq] : other.wordFrequency) {
		wordFrequency[word] += freq;
	}

	for (const auto& [word, status] : other.foreignWords) {
		if (foreignWords.find(word) == foreignWords.end() ||
			static_cast<int>(foreignWords[word]) < static_cast<int>(status)) {
			foreignWords[word] = status;
		}
	}

	return *this;
}

Dictionary Dictionary::operator+(const Dictionary& other) const {
	Dictionary result = *this;
	result += other;
	return result;
}

Dictionary Dictionary::intersection(const Dictionary& other) const {
	Dictionary result;

	for (const auto& [word, freq] : wordFrequency) {
		auto it = other.wordFrequency.find(word);
		if (it != other.wordFrequency.end()) {
			result.wordFrequency[word] = std::min(freq, it->second);

			auto foreignIt = foreignWords.find(word);
			auto otherForeignIt = other.foreignWords.find(word);

			if (foreignIt != foreignWords.end() && otherForeignIt != other.foreignWords.end()) {
				result.foreignWords[word] = static_cast<int>(foreignIt->second) <
					static_cast<int>(otherForeignIt->second) ?
					foreignIt->second : otherForeignIt->second;
			}
		}
	}

	return result;
}

void Dictionary::setWordStatus(const std::string& word, WordStatus status) {
	foreignWords[word] = status;
}

void Dictionary::display(bool byFrequency) const {
	std::cout << "--------------- Dictionary (" << (byFrequency ? "by frequency" : "alphabetically") << ") ---------------" << std::endl;

	if (byFrequency) {
		std::vector<std::pair<std::string, size_t>> sortedWords(wordFrequency.begin(), wordFrequency.end());
		std::sort(sortedWords.begin(), sortedWords.end(),
			[](const auto& a, const auto& b) { return a.second > b.second; });

		for (const auto& [word, freq] : sortedWords) {
			std::cout << word << ": " << freq;

			auto it = foreignWords.find(word);
			if (it != foreignWords.end()) {
				std::cout << " (";
				switch (it->second) {
				case WordStatus::New: std::cout << "New"; break;
				case WordStatus::Learning: std::cout << "Learning"; break;
				case WordStatus::Learned: std::cout << "Learned"; break;
				case WordStatus::Ignored: std::cout << "Ignored"; break;
				}
				std::cout << ")";
			}

			std::cout << std::endl;
		}
	}
	else {
		for (const auto& [word, freq] : wordFrequency) {
			std::cout << word << ": " << freq;

			auto it = foreignWords.find(word);
			if (it != foreignWords.end()) {
				std::cout << " (";
				switch (it->second) {
				case WordStatus::New: std::cout << "New"; break;
				case WordStatus::Learning: std::cout << "Learning"; break;
				case WordStatus::Learned: std::cout << "Learned"; break;
				case WordStatus::Ignored: std::cout << "Ignored"; break;
				}
				std::cout << ")";
			}

			std::cout << std::endl;
		}
	}

	std::cout << "--------------- End of Dictionary ---------------" << std::endl;
}

std::vector<std::string> Dictionary::getWordsByStatus(WordStatus status) const {
	std::vector<std::string> result;

	for (const auto& [word, wordStatus] : foreignWords) {
		if (wordStatus == status) {
			result.push_back(word);
		}
	}

	return result;
}