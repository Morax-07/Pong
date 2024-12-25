//LIBRERIE
#include <iostream>
#include "raylib.h"

//CLASSI
#include "Pad.h"


using namespace std;





//METODI CLASSE PLAYER
//costruttore
Pad::Pad(Vector2 posizione)
{
	this->posizione = posizione;
}

//stampa pad
void Pad::stampaPad()
{
	DrawRectangle(posizione.x, posizione.y, 10, 80, WHITE);
}

//aggiorna pad
void Pad::aggiornaPad(int direzione)
{
	posizione.y += direzione;
}

//collisione con i bordi dello schermo
void Pad::collisioneBordi()
{
	if (posizione.y < 0)
	{
		posizione.y = 0;
	}
	if (posizione.y > GetScreenHeight() - 150)
	{
		posizione.y = GetScreenHeight() - 150;
	}
}

//resetta la posizione quando il gioco è in stato di score
void Pad::resetPosizione(bool reset_player)
{
	if (reset_player)
	{
		posizione = { (float)GetScreenWidth() - 25, (float)((GetScreenHeight() - 70) / 2) - 40 };
	}
	else
	{
		posizione = { 15, (float)((GetScreenHeight() - 70) / 2) - 40 };
	}
}

//output della posizione
Vector2 Pad::getPosizione()
{
	return posizione;
}

//hitbox del pad
Rectangle Pad::hitbox()
{
	return { posizione.x, posizione.y, 10, 80 };
}