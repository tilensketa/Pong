#include "Game.h"

int main() {
	Game game(1000, 600);
	game.Init();
	game.Run();
	game.Close();
	return 0;
}