//LIBRERIE
#include <iostream>
#include "raylib.h"

//CLASSI
#include "Palla.h"



using namespace std;




//METODI CLASSE PALLA
//costruttore
Palla::Palla(Vector2 posizione_palla)
{
	this->posizione_palla = posizione_palla;
}

//stampa palla
void Palla::stampaPalla()
{
	DrawCircle(posizione_palla.x, posizione_palla.y, raggio, WHITE);
}

//aggiorna la posizione della palla
void Palla::aggiornaPalla()
{
	posizione_palla.x += direzione_x;
	posizione_palla.y += direzione_y;
}

//calcola hitbox della palla
Rectangle Palla::hitbox()
{
	return {posizione_palla.x - raggio, posizione_palla.y - raggio, (float)raggio * 2, (float)raggio * 2};
}