#pragma once






//CLASSE PLAYER
class Pad
{
	//elementi pubblici
	public:
		Pad(Vector2 posizione);
		void stampaPad();
		void aggiornaPad(int direzione);
		void collisioneBordi();
		void resetPosizione(bool reset_player);
		Vector2 getPosizione();
		Rectangle hitbox();

	protected:
		Vector2 posizione;
};