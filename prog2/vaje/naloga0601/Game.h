#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "RainDrop.h"
#include "Display.h"
#include <vector>

using namespace std;

enum GameState { PLAY, GAME_OVER, PAUSE };

class Game {
private:
  GameState state;
  std::vector<GameObject *> gameObjects;

public:
	constexpr static float displayWidth = 25;
  constexpr static float displayHeight = 80;
  constexpr static Display display;
  Game() { state = GameState::PLAY;};
  ~Game() { 
		for(int i = 0; i < gameObjects.size(); i++){
			delete gameObjects[i];
		}
		gameObjects.clear();
	};
  void addPlayer(float x, float y, float width, float height,
                 const std::string &name) {
    gameObjects.push_back(new Player(x, y, width, height, name));
  };
  void render() {
    for (int i = 0; i < gameObjects.size(); i++) {
      gameObjects[i]->draw();
      cout << endl;
    }
    if (state == GameState::GAME_OVER) {
      cout << "GAME OVER" << endl;
    } else if (state == GameState::PAUSE) {
      cout << "PAUSE" << endl;
    }
  };
  void update() {
    for (int i = 0; i < gameObjects.size(); i++) {
      if (state == GameState::PLAY)
        gameObjects[i]->update();
    }
  };
  void play() { state = GameState::PLAY; };
  void pause() { state = GameState::PAUSE; };
  void gameOver() { state = GameState::GAME_OVER; };
	void generateRainDrops(int numDrops, float dimension, float speedX, float speedY){
		for (int i = 0; i < numDrops; i++){
			gameObjects.push_back(new RainDrop(Game::displayWidth, Game::displayHeight, dimension, dimension, speedX, speedY));
		}
	};
};

#endif // Game_H