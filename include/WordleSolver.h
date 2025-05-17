#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>


enum Result {
	ABSENT,
	PRESENT,
	CORRECT,
	PENDING
};

struct Guess {
	std::string word;
	Result results[5];
};


class WordleSolver {
private:
	std::vector<std::string> solutions;

	bool allowed[5][26];
	int requiredCount[26] = {};
	bool absent[26] = {};

public:
	WordleSolver(const std::vector<std::string>& words);

	void addGuess(const Guess& guess);
	std::vector<std::pair<std::string, double>> getNextGuesses();
};
