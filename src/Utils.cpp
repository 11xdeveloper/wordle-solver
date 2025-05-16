#include "Utils.h"

std::string toUpperCase(std::string word) {
	std::string upperCase;

	for (char c : word) {
		upperCase += std::toupper(c);
	}

	return upperCase;
}

std::string selectRandomWord(std::vector<std::string> words) {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_int_distribution<size_t> distribution(0, words.size() - 1);

	return words[distribution(generator)];
}

void loadFile(std::vector<std::string>& lines, const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file: " + filename);
	}

	std::string line;

	while (std::getline(file, line)) {
		lines.push_back(line);
	}
}

