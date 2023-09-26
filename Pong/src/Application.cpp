#include "Game.h"

int main() {
	Game game(800, 600);
	game.Init();
	game.Run();
	game.Close();
	return 0;
}