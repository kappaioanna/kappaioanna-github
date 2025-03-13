#pragma once
#include "Gameobject.h"
#include "config.h"

class Player : public Gameobject, public Collidable {
	float pos_x = CANVAS_WIDTH / 2, pos_y = CANVAS_HEIGHT / 2;
	float tailX[100], tailY[100];
	int lengthtail = 1;
	int opa;
	float speed = 0.7f;
	int start = 1;
	float score = 0000.0f;
public:
	Player(const class Game& mygame);
	void update() override;
	void draw() override;
	void init() override;
	Disk getCollisionHull() const override;
	float getRemainingScore() { return score; }
	void turnscore() { score = score + 1.0f; }
	void zeroscore() { score = 0000.0f; }
	void growtail() { lengthtail = lengthtail + 1; }
	void growspeed() { speed = speed + 0.1f; }
};
