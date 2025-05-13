#include "WordLoader.h"

std::vector<std::string> loadWordFile(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file: " + filename);
	}

	std::vector<std::string> words;
	std::string word;

	while (std::getline(file, word)) {
		if (word.length() == 5) {
			words.push_back(word);
		}
	}

	if (words.empty()) {
		throw std::runtime_error("No valid 5-letter words found in file");
	}

	return words;
}