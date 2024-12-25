//LIBRERIE
#include <iostream>
#include "raylib.h"

//CLASSI
#include "Game.h"


using namespace std;




//METODI CLASSE GAME
#pragma region game
//costruttore
Game::Game()
{
	stato = menu;

	punteggio_player = 0;
	punteggio_cpu = 0;

	rettangolo_titolo = { (float)(GetScreenWidth() / 2) - (MeasureText("PONG", 60) / 2) - 70, 185, (float)MeasureText("PONG", 60) + 140, 120 };

	float pos_x = GetRandomValue(8, GetScreenWidth() - 8);
	float pos_y = GetRandomValue(8, GetScreenHeight() - 78);

	while (CheckCollisionRecs(rettangolo_titolo, { pos_x - palla.raggio, pos_y - palla.raggio, (float)palla.raggio * 2, (float)palla.raggio * 2}))
	{
		pos_x = GetRandomValue(8, GetScreenWidth() - 8);
		pos_y = GetRandomValue(8, GetScreenHeight() - 78);
	}

	palla.posizione_palla = { pos_x, pos_y };

	hit_palla = LoadSound("data/suoni/palla.mp3");
	punto = LoadSound("data/suoni/score.wav");
}

//distruttore
Game::~Game()
{
	UnloadSound(hit_palla);
	UnloadSound(punto);
}

#pragma endregion

#pragma region stampa
//stampa degli elementi del gioco
void Game::stampaGioco()
{
	//controlla lo stato del gioco
	switch (stato)
	{
		//stampa del menu
		case menu:
			palla.stampaPalla();

			DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), {0, 0, 0, 180});
			DrawText("PONG", (GetScreenWidth() / 2) - (MeasureText("PONG", 60) / 2), 200, 60, WHITE);
			DrawRectangleLinesEx(rettangolo_titolo, 3, WHITE);
			DrawText("PRESS START", (GetScreenWidth() / 2) - (MeasureText("PRESS START", 15) / 2), 275, 15, WHITE);

			break;

		//stampa del gioco in running
		case running:
			stampaRunning();

			break;

		case score:
			stampaRunning();

			break;

		//stampa il gioco in pausa
		case pausa:
			stampaRunning();
			DrawText("Pause ||", (GetScreenWidth() - MeasureText("Puase ||", 20) - 10), GetScreenHeight() - 25, 20, WHITE);

			break;

		default:
			break;
	}
}

//stampa lo stato di running riutilizzato nello stato di pausa
void Game::stampaRunning()
{
	DrawLineEx({ 0, (float)GetScreenHeight() - 70 }, { (float)GetScreenWidth(), (float)GetScreenHeight() - 70 }, 4, WHITE);
	DrawLine(GetScreenWidth() / 2, 50, GetScreenWidth() / 2, GetScreenHeight() - 120, WHITE);
	DrawText(TextFormat("%i", punteggio_player), (GetScreenWidth() / 2) + 30, 60, 20, WHITE);
	DrawText(TextFormat("%i", punteggio_cpu), (GetScreenWidth() / 2) - MeasureText(TextFormat("%i", punteggio_cpu), 20) - 30, 60, 20, WHITE);

	palla.stampaPalla();
	player.stampaPad();
	avversario.stampaPad();
}
#pragma endregion

//aggiornamento degli elementi del gioco
void Game::aggiornaGioco()
{
	switch (stato)
	{
		//aggiornamento del gioco nel menu
		case menu:
			palla.aggiornaPalla();

			break;

		//aggiornamento del gioco durante la partita
		case running:
			tempo_da_inizio_gioco++;

			if (tempo_da_inizio_gioco >= 120)
			{
				palla.aggiornaPalla();
				player.aggiornaPad(direzione_player);
				muoviAvversario();
			}

			break;

		//aggiornamneto del gioco in caso di punto
		case score:
			tempo_da_inizio_score++;

			if (tempo_da_inizio_score >= 80)
			{
				reset();
			}

			break;
		
		//aggiornamento del gioco durante la pausa
		case pausa:
			break;

		default:
			break;
	}

	//controllo dell collisioni sia nel menu che nel gioco
	controlloCollisioni();
}

//AI per muovere avversario
void Game::muoviAvversario()
{
	if (palla.posizione_palla.x < (GetScreenWidth() / 2) - 200)
	{
		if (palla.posizione_palla.y < avversario.getPosizione().y + 40)
		{
			avversario.aggiornaPad(-5);
		}
		else if (palla.posizione_palla.y > avversario.getPosizione().y + 40)
		{
			avversario.aggiornaPad(5);
		}
	}
}

//controllo degli input
void Game::controlloInput()
{
	if (IsKeyPressed(KEY_ENTER) && stato == menu)
	{
		stato = running;
		PlaySound(punto);

		palla.posizione_palla = { (float)GetScreenWidth() / 2, (float)(GetScreenHeight() - 70) / 2 };
		palla.direzione_x = 4;
		palla.direzione_y = 5;
	}
	if (IsKeyDown(KEY_UP))
	{
		direzione_player = -6;
	}
	else if (IsKeyDown(KEY_DOWN))
	{
		direzione_player = 6;
	}
	else
	{
		direzione_player = 0;
	}
	if (IsKeyPressed(KEY_R))
	{
		punteggio_player = 0;
		punteggio_cpu = 0;

		reset();
	}
	if (IsKeyPressed(KEY_P))
	{
		if (stato == running)
		{
			stato = pausa;
		}
		else if (stato == pausa)
		{
			stato = running;
		}
	}
}

//controlla tutte le collisioni del gioco
void Game::controlloCollisioni()
{
	if (stato == menu)
	{
		if (palla.posizione_palla.x + palla.raggio > GetScreenWidth() || palla.posizione_palla.x - palla.raggio < 0)
		{
			PlaySound(hit_palla);
			palla.direzione_x = -palla.direzione_x;
		}
		if (palla.posizione_palla.y - palla.raggio < 0 || palla.posizione_palla.y + palla.raggio > GetScreenHeight())
		{
			PlaySound(hit_palla);
			palla.direzione_y = -palla.direzione_y;
		}
		if (CheckCollisionRecs(palla.hitbox(), rettangolo_titolo) && (palla.posizione_palla.y - palla.raggio < rettangolo_titolo.height + rettangolo_titolo.y || palla.posizione_palla.y + palla.raggio > rettangolo_titolo.y) && (palla.posizione_palla.x > rettangolo_titolo.x && palla.posizione_palla.x < rettangolo_titolo.width + rettangolo_titolo.x))
		{
			PlaySound(hit_palla);
			palla.direzione_y = -palla.direzione_y;
		}
		if (CheckCollisionRecs(palla.hitbox(), rettangolo_titolo) && (palla.posizione_palla.x - palla.raggio < rettangolo_titolo.width + rettangolo_titolo.x || palla.posizione_palla.x + palla.raggio > rettangolo_titolo.x) && (palla.posizione_palla.y > rettangolo_titolo.y && palla.posizione_palla.y < rettangolo_titolo.height + rettangolo_titolo.y))
		{
			PlaySound(hit_palla);
			palla.direzione_x = -palla.direzione_x;
		}
	}
	else if (stato == running)
	{
		player.collisioneBordi();
		avversario.collisioneBordi();


		if (palla.posizione_palla.x + palla.raggio > GetScreenWidth() + palla.raggio * 2)
		{
			PlaySound(punto);
			stato = score;
			punteggio_cpu++;
		}
		if (palla.posizione_palla.x - palla.raggio < -palla.raggio * 2)
		{
			PlaySound(punto);
			stato = score;
			punteggio_player++;
		}
		if (palla.posizione_palla.y - palla.raggio < 0 || palla.posizione_palla.y + palla.raggio > GetScreenHeight() - 70)
		{
			PlaySound(hit_palla);
			palla.direzione_y = -palla.direzione_y;
		}
		if (CheckCollisionRecs(palla.hitbox(), player.hitbox()) || CheckCollisionRecs(palla.hitbox(), avversario.hitbox()))
		{
			PlaySound(hit_palla);
			palla.direzione_x = -palla.direzione_x;
		}
	}
}

//resetta il gioco (non il punteggio)
void Game::reset()
{
	tempo_da_inizio_gioco = 0;
	tempo_da_inizio_score = 0;
	stato = running;

	palla.posizione_palla = { (float)GetScreenWidth() / 2, (float)(GetScreenHeight() - 70) / 2 };
	palla.direzione_x = 4;

	player.resetPosizione(true);
	avversario.resetPosizione(false);

	palla.direzione_y = (GetRandomValue(0, 1) == 1) ? 5 : -5;
}