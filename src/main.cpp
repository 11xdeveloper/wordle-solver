#include <iostream>
#include <random>
#include <chrono>

#include "raylib.h"
#include "WordLoader.h"

#define TILE_SIZE 64
#define SPACING 10

std::string toUpperCase(std::string word) {
	std::string upperCase;

	for (char c : word) {
		upperCase += std::toupper(c);
	}

	return upperCase;
}

int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// 5 letters, 6 guesses with spacing
	InitWindow(TILE_SIZE * 5 + SPACING * 6, TILE_SIZE * 6 + SPACING * 7, "Wordle");

	std::vector<std::string> possibleAnswers = loadWordFile("resources/possible_answers.txt");
	std::vector<std::string> allowedGuesses = loadWordFile("resources/allowed_guesses.txt");


	std::cout << "Possible Answers: " << possibleAnswers.size() << std::endl;
	std::cout << "Allowed Guesses: " << allowedGuesses.size() << std::endl;

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_int_distribution<size_t> distribution(0, possibleAnswers.size() - 1);

	const std::string word = possibleAnswers[distribution(generator)];

	std::cout << "Answer: " << word << std::endl;

	std::string guesses[6] = {"tests", "to"};
	int currentRow = 2;

	// Taken from official game
	const Color textColor = GetColor(0xf8f8f8ff);
	const Color bgColor = GetColor(0x121213ff);
	const Color absentColor = GetColor(0x3a3a3cff);
	const Color presentColor = GetColor(0xb59f3bff);
	const Color correctColor = GetColor(0x538d4eff);

	const Font font = GetFontDefault();

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(bgColor);

		for (int i = 0; i < 6; i++) {
			std::string text;

			if (i < currentRow) {
				text = toUpperCase(guesses[i]);
			}

			for (int j = 0; j < 5; j++) {
				Rectangle rect = { j * TILE_SIZE + SPACING * (j + 1), i * TILE_SIZE + SPACING * (i + 1), TILE_SIZE, TILE_SIZE };

				DrawRectangleLinesEx(rect, 2, absentColor);

				if (j < text.length()) {
					std::string temp = text.substr(j, 1);
					const char* letter = temp.c_str();

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
