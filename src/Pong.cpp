//LIBRERIE
#include <iostream>
#include "raylib.h"



using namespace std;



#include "Game.h"


//MAIN
int main() 
{
	Image logo = LoadImage("data/sprite/logo.png");


	InitWindow(800, 500, "Pong");
	SetWindowIcon(logo);
	UnloadImage(logo);

	InitAudioDevice();
	SetTargetFPS(60);
	HideCursor();


	Game game = Game();

	system("clear");

	while (!WindowShouldClose())
	{
		BeginDrawing();

		game.stampaGioco();
		game.aggiornaGioco();


		ClearBackground(BLACK);

		game.controlloInput();


		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();

	return 0;
}