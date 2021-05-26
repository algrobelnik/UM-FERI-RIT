#include "Game.h"

using namespace std;


float randGen(int min, int max) {
  int range = max - min++;
  return rand() % range + min;
}

int main() {
	float dimension = randGen(0, Game::displayWidth);
  Game game;
  game.addPlayer(0, 0, 10, 20, "Brane");
  game.addPlayer(50, 0, 10, 20, "S1mple");
  game.addPlayer(150, 0, 10, 20, "Johnny");
  game.generateRainDrops(10, dimension, 20, 10);
  game.generateRainDrops(10, dimension, 5, -5);

  game.render();
  game.pause();
  game.update();
  game.render();
  game.play();
  game.update();
  game.render();
  game.gameOver();
  game.update();
  game.render();

  return 0;
}
