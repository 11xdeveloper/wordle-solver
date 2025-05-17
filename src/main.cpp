#include <iostream>

#include "raylib.h"
#include "WordleSolver.h"
#include "Utils.h"

int main()
{
	const int TILE_SIZE = 64;
	const int SPACING = 10;

	// 5 letters, 6 guesses with spacing
	const int TILES_WIDTH = TILE_SIZE * 5 + SPACING * 6;
	const int WINDOW_WIDTH = TILES_WIDTH + 300;
	const int WINDOW_HEIGHT = TILE_SIZE * 6 + SPACING * 7;

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Wordle");

	// Taken from official game
	const Color textColor = GetColor(0xf8f8f8ff);
	const Color bgColor = GetColor(0x121213ff);
	const Color absentColor = GetColor(0x3a3a3cff);
	const Color presentColor = GetColor(0xb59f3bff);
	const Color correctColor = GetColor(0x538d4eff);

	const Font font = GetFontDefault();

	std::vector<std::string> words;
	words.reserve(12972);

	std::vector<std::pair<std::string, double>> nextGuesses;
	nextGuesses.reserve(12972);

	std::vector<std::string> nextGuessesLines;
	nextGuesses.reserve(12972);

	loadFile(words, "resources/allowed_guesses.txt");
	loadFile(nextGuessesLines, "resources/results.txt");

	for (const auto& line : nextGuessesLines) {
		std::string word = line.substr(0, 5);
		double entropy = std::stod(line.substr(7));

		nextGuesses.emplace_back(word, entropy);
	}

	WordleSolver solver(words);


	std::string input;
	Result characterResults[5] = { Result::PENDING, Result::PENDING, Result::PENDING, Result::PENDING, Result::PENDING };
	Vector2 mousePosition = { 0, 0 };

	Guess guesses[6] = {};
	int currentRow = 0;

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(bgColor);

		mousePosition = GetMousePosition();

		int key = GetCharPressed();
		size_t inputLength = input.length();

		// a-z, A-Z
		if (((key >= 65 && key <= 90) || (key >= 97 && key <= 122)) && (inputLength < 5))
		{
			input.push_back(std::tolower(key));
		}

		if (IsKeyPressed(KEY_BACKSPACE) && inputLength > 0)
		{
			input.pop_back();
		}

		if (IsKeyPressed(KEY_ENTER) && inputLength == 5 && currentRow < 6 && std::find(words.begin(), words.end(), input) != words.end())
		{
			Guess guess;
			guess.word = input;

			bool valid = true;

			for (int i = 0; i < 5; ++i) {
				std::cout << characterResults[i] << std::endl;
				if (characterResults[i] == Result::PENDING) {
					valid = false;
					break;
				}

				guess.results[i] = characterResults[i];
			}

			if (valid) {
				solver.addGuess(guess);
				guesses[currentRow] = guess;
				input = "";
				std::fill(std::begin(characterResults), std::end(characterResults), Result::PENDING);
				currentRow++;

				size_t guessesNo = nextGuesses.size();
				for (int i = 0; i < 10; i++) {
					if (guessesNo <= i) break;
					std::cout << "#" << i + 1 << ": " << nextGuesses[i].first << " - " << nextGuesses[i].second << std::endl;
				}
			}
		}

		for (int i = 0; i < 6; i++) {
			std::string word = i == currentRow ? input : guesses[i].word;
			for (int j = 0; j < 5; j++) {
				Rectangle rect = { static_cast<float>(j * TILE_SIZE + SPACING * (j + 1)), static_cast<float>(i * TILE_SIZE + SPACING * (i + 1)), TILE_SIZE, TILE_SIZE };

				// Input tile clicked
				if (i == currentRow && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mousePosition.x > rect.x && mousePosition.x < rect.x + rect.width) {
					Result r;
					bool isValid = true;

					if (i == currentRow) {
						if (characterResults[j] == Result::PENDING) {
							isValid = false;
						}
						else {
							r = characterResults[j];
						}
					}
					else {
						r = guesses[i].results[j];
					}

					if (isValid) {
						if (r == Result::CORRECT) {
							DrawRectangleRec(rect, correctColor);
						}
						else if (r == Result::PRESENT) {
							DrawRectangleRec(rect, presentColor);
						}
						else if (r == Result::ABSENT) {
							DrawRectangleRec(rect, absentColor);
						}
					}
				}


				DrawRectangleLinesEx(rect, 2, absentColor);

				if (j < word.length()) {
					std::string temp = word.substr(j, 1);
					const char* letter = temp.c_str();
					char lower = tolower(letter[0]);

					Vector2 offset = MeasureTextEx(font, letter, TILE_SIZE * 0.75, 0);

					DrawTextEx(font, letter, { rect.x + TILE_SIZE / 2 - offset.x / 2 , rect.y + TILE_SIZE / 2 - offset.y / 2 }, TILE_SIZE * 0.75, 0, textColor);

				}
			}
		}

		EndDrawing();
	}


	CloseWindow();
	return 0;
}
