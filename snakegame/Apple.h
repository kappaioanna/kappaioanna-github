#pragma once
#include "Gameobject.h"
#include "graphics.h"
class Apple :public Gameobject, public Collidable {
	float pos_x, pos_y;
	float size;
	graphics::Brush brush;
	bool active = true;
public:
	void update()override;
	void draw()override;
	void init()override;
	bool isActive() { return active; }
	Apple(const class Game & mygame);
	~Apple();
	Disk getCollisionHull() const override;
};