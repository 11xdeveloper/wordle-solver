#include "WordleSolver.h"

WordleSolver::WordleSolver(const std::vector<std::string>& words) {
	for (int i = 0; i < 5; i++) {
		for (int c = 0; c < 26; c++) {
			allowed[i][c] = true;
		}
	}

	solutions = words;
}

void WordleSolver::addGuess(const Guess& guess) {
	int countThisGuess[26] = {};

	for (int i = 0; i < 5; i++) {
		char ch = guess.word[i];
		Result r = guess.results[i];
		int idx = ch - 'a';

		if (r == CORRECT) {
			for (int c = 0; c < 26; c++) {
				allowed[i][c] = false;
			}

			allowed[i][idx] = true;
			countThisGuess[idx]++;
		}
		else if (r == PRESENT) {
			allowed[i][idx] = false;
			countThisGuess[idx]++;
		}
		else {
			allowed[i][idx] = false;

			bool presentElsewhere = false;

			for (int j = 0; j < 5; j++) {
				if (guess.word[j] == ch && (guess.results[j] == CORRECT || guess.results[j] == PRESENT)) {
					presentElsewhere = true;
					break;
				}
			}

			if (!presentElsewhere) {
				absent[idx] = true;
			}
		}
	}

	for (int c = 0; c < 26; c++) {
		requiredCount[c] = std::max(requiredCount[c], countThisGuess[c]);
	}

	std::vector<std::string> newSolutions;

	for (auto& w : solutions) {
		int freq[26] = {};

		bool ok = true;

		for (int i = 0; i < 5; i++) {
			int idx = w[i] - 'a';

			if (!allowed[i][idx]) {
				ok = false;
				break;
			}

			freq[idx]++;
		}

		if (!ok) continue;

		for (int c = 0; c < 26; c++) {
			if (absent[c] && freq[c] > 0) {
				ok = false;
				break;
			}
		}

		if (!ok) continue;

		for (int c = 0; c < 26; c++) {
			if (freq[c] < requiredCount[c]) {
				ok = false;
				break;
			}
		}

		if (!ok) continue;

		newSolutions.push_back(w);
	}

	solutions = std::move(newSolutions);
}

std::vector<std::pair<std::string, double>> WordleSolver::getNextGuesses() {
	std::vector<std::pair<std::string, double>> wordEntropyPairs;

	int n = solutions.size();
	std::vector<int> counts(243);

	for (const auto& guessWord : solutions) {
		std::fill(counts.begin(), counts.end(), 0);

		for (const auto& solutionWord : solutions) {
			int letterCount[26] = {};
			Result feedback[5] = {};

			for (int i = 0; i < 5; ++i) {
				if (guessWord[i] == solutionWord[i]) {
					feedback[i] = CORRECT;
				}
				else {
					feedback[i] = ABSENT;
					letterCount[solutionWord[i] - 'a']++;
				}
			}

			for (int i = 0; i < 5; ++i) {
				if (feedback[i] == ABSENT) {
					int idx = guessWord[i] - 'a';

					if (letterCount[idx] > 0) {
						feedback[i] = PRESENT;
						letterCount[idx]--;
					}
				}
			}

			int pattern = 0;
			int factor = 1;

			for (int i = 0; i < 5; ++i) {
				pattern += feedback[i] * factor;
				factor *= 3;
			}

			counts[pattern]++;
		}

		double entropy = 0.0;

		for (int count : counts) {
			if (count > 0) {
				double p = static_cast<double>(count) / n;
				entropy += p * (-std::log2(p));
			}
		}

		wordEntropyPairs.emplace_back(guessWord, entropy);
	}

	std::sort(wordEntropyPairs.begin(), wordEntropyPairs.end(), [](const auto& a, const auto& b) {
		return a.second > b.second;
		});


	return wordEntropyPairs;
}