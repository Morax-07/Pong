#pragma once

//CLASSI
#include "Palla.h"
#include "Pad.h"
#include "Cpu.h"




//stati del gioco
typedef enum stati_gioco {menu, running, score, pausa};





//CLASSE GAME
class Game
{
	//elementi privati
	private:
		stati_gioco stato;

		Palla palla = Palla({ 0, 0 });
		Pad player = Pad({ (float)GetScreenWidth() - 25, (float)((GetScreenHeight() - 70) / 2) - 40 });
		Cpu avversario = Cpu({15, (float)((GetScreenHeight() - 70) / 2) - 40 });

		Sound hit_palla;
		Sound punto;

		Rectangle rettangolo_titolo;

		unsigned long int tempo_da_inizio_gioco = 0;
		int tempo_da_inizio_score = 0;

		int punteggio_player;
		int punteggio_cpu;

		int direzione_player = 0;

		void stampaRunning();

		void controlloCollisioni();

		void reset();

		void muoviAvversario();


	//elementi pubblici
	public:
		Game();
		~Game();

		//metodi fondamentali
		void stampaGioco();
		void aggiornaGioco();
		void controlloInput();
};