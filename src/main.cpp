#include <iostream>

#include "raylib.h"
#include "WordLoader.h"

int main ()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(1280, 800, "Wordle");

	std::vector<std::string> possibleAnswers = loadWordFile("resources/possible_answers.txt");
	std::vector<std::string> allowedGuesses = loadWordFile("resources/allowed_guesses.txt");


	std::cout << "Possible Answers: " << possibleAnswers.size() << std::endl;
	std::cout << "Allowed Guesses: " << allowedGuesses.size() << std::endl;

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
