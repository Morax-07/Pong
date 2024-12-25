#pragma once






//CLASSE PALLA
class Palla
{
	//elementi pubblici
	public:
		Vector2 posizione_palla;
		int raggio = 7;

		int direzione_x = 4;
		int direzione_y = 5;

		Palla(Vector2 posizione_palla);
		void stampaPalla();
		void aggiornaPalla();
		Rectangle hitbox();
};