#pragma once
#include "Player.h"
#include "Apple.h"

class Game
{
	typedef enum {STATUS_START, STATUS_PLAYING,STATUS_END} status_t;
	Player* player = nullptr;
	bool player_initialized = false;
	bool debug_mode = false;

	Apple* apple = nullptr;
	void spawnApple();
	void checkApple();
	bool checkCollision();
	status_t status = STATUS_START;

	void updateStartScreen();
	void updateEndScreen();
	void updateLevelScreen();
	void drawStartScreen();
	void drawEndScreen();
	void drawLevelScreen();

public:
	void setDebugMode(bool d) { debug_mode = d; }
	bool getDebugMode() const { return debug_mode ; }
	void update();
	void draw();
	void init();
	Game();
	~Game();
};
