#include <iostream>

#include "raylib.h"
#include "WordLoader.h"

#define TILE_SIZE 64
#define SPACING 10

int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// 5 letters, 6 guesses with spacing
	InitWindow(TILE_SIZE * 5 + SPACING * 6, TILE_SIZE * 6 + SPACING * 7, "Wordle");

	std::vector<std::string> possibleAnswers = loadWordFile("resources/possible_answers.txt");
	std::vector<std::string> allowedGuesses = loadWordFile("resources/allowed_guesses.txt");


	std::cout << "Possible Answers: " << possibleAnswers.size() << std::endl;
	std::cout << "Allowed Guesses: " << allowedGuesses.size() << std::endl;

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
			for (int j = 0; j < 5; j++) {
				Rectangle rect = { j * TILE_SIZE + SPACING * (j + 1), i * TILE_SIZE + SPACING * (i + 1), TILE_SIZE, TILE_SIZE };

				DrawRectangleLinesEx(rect, 2, absentColor);
			}
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
