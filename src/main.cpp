#include <iostream>
#include <unordered_map>

#include "raylib.h"
#include "Utils.h"

enum class CharacterResult {
	ABSENT,
	PRESENT,
	CORRECT
};

struct Guess {
	std::string value;
	CharacterResult results[5];
};

enum class GameState {
	PLAYING,
	LOST,
	WON
};

int main()
{
	const int TILE_SIZE = 64;
	const int SPACING = 10;

	// 5 letters, 6 guesses with spacing
	const int WINDOW_WIDTH = TILE_SIZE * 5 + SPACING * 6;
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


	std::vector<std::string> possibleAnswers;
	possibleAnswers.reserve(2315);

	std::vector<std::string> allowedGuesses;
	allowedGuesses.reserve(12972);

	loadFile(possibleAnswers, "resources/possible_answers.txt");
	loadFile(allowedGuesses, "resources/allowed_guesses.txt");

	std::cout << "Possible Answers: " << possibleAnswers.size() << std::endl;
	std::cout << "Allowed Guesses: " << allowedGuesses.size() << std::endl;

	const std::string word = selectRandomWord(possibleAnswers);

	std::cout << "Answer: " << word << std::endl;

	std::unordered_map<char, int> freq = {};

	for (char c : word) {
		freq[c]++;
	}

	GameState gameState = GameState::PLAYING;

	std::string input;
	Guess guesses[6] = {};
	int currentRow = 0;

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		switch (gameState)
		{
		case GameState::PLAYING: {
			BeginDrawing();

			ClearBackground(bgColor);

			int key = GetCharPressed();
			int inputLength = input.length();

			// a-z, A-Z
			if (((key >= 65 && key <= 90) || (key >= 97 && key <= 122)) && (inputLength < 5))
			{
				input.push_back(std::tolower(key));
			}

			if (IsKeyPressed(KEY_BACKSPACE) && inputLength > 0)
			{
				input.pop_back();
			}

			if (IsKeyPressed(KEY_ENTER) && inputLength == 5 && currentRow < 6 && std::find(allowedGuesses.begin(), allowedGuesses.end(), input) != allowedGuesses.end())
			{
				Guess* guess = &guesses[currentRow];
				guess->value = input;

				int correct = 0;
				auto freqCopy = freq;

				for (int i = 0; i < 5; i++)
				{
					if (input[i] == word[i])
					{
						guess->results[i] = CharacterResult::CORRECT;
						correct++;
						freqCopy[input[i]]--;
					}
					else if (word.find(input[i]) != std::string::npos && freqCopy[input[i]] != 0)
					{
						guess->results[i] = CharacterResult::PRESENT;
					}
					else
					{
						guess->results[i] = CharacterResult::ABSENT;
					}
				}

				if (correct == 5) {
					gameState = GameState::WON;
					continue;
				}

				if (currentRow == 5) {
					gameState = GameState::LOST;
					continue;
				}

				input = "";
				currentRow++;
			}

			for (int i = 0; i < 6; i++) {
				std::string text;
				Guess* guess = nullptr;

				if (i < currentRow) {
					guess = &guesses[i];
					text = toUpperCase(guess->value);
				}
				else if (i == currentRow) {
					text = toUpperCase(input);
				}

				for (int j = 0; j < 5; j++) {
					Rectangle rect = { j * TILE_SIZE + SPACING * (j + 1), i * TILE_SIZE + SPACING * (i + 1), TILE_SIZE, TILE_SIZE };

					DrawRectangleLinesEx(rect, 2, absentColor);

					if (j < text.length()) {
						if (i < currentRow) {
							Color col = absentColor;

							switch (guess->results[j])
							{
							case CharacterResult::CORRECT:
								col = correctColor;
								break;
							case CharacterResult::PRESENT:
								col = presentColor;
								break;
							case CharacterResult::ABSENT:
								col = absentColor;
								break;
							default:
								break;
							}

							DrawRectangleRec(rect, col);
						}

						std::string temp = text.substr(j, 1);
						const char* letter = temp.c_str();

						Vector2 offset = MeasureTextEx(font, letter, TILE_SIZE * 0.75, 0);

						DrawTextEx(font, letter, { rect.x + TILE_SIZE / 2 - offset.x / 2 , rect.y + TILE_SIZE / 2 - offset.y / 2 }, TILE_SIZE * 0.75, 0, textColor);
					}
				}
			}

			EndDrawing();
			break;
		}

		case GameState::LOST: {
			BeginDrawing();
			ClearBackground(bgColor);

			const char* text = "You lost!";

			Vector2 offset = MeasureTextEx(font, text, 60, NULL);

			DrawTextEx(font, text, { WINDOW_WIDTH / 2 - offset.x / 2, WINDOW_HEIGHT / 2 - offset.y / 2 }, 60, NULL, RED);

			EndDrawing();
			break;
		}

		case GameState::WON: {
			BeginDrawing();
			ClearBackground(bgColor);

			const char* text = "You won!";

			Vector2 offset = MeasureTextEx(font, text, 60, NULL);

			DrawTextEx(font, text, { WINDOW_WIDTH / 2 - offset.x / 2, WINDOW_HEIGHT / 2 - offset.y / 2 }, 60, NULL, GREEN);

			EndDrawing();
			break;
		}
		}
	}

	CloseWindow();
	return 0;
}
