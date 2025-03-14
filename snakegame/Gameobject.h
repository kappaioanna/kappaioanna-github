#pragma once
#include "util.h"
class Collidable {
public:
	virtual Disk getCollisionHull() const = 0;
};
class Gameobject
{
protected:
	const class Game & game;
public:
	Gameobject(const class Game & mygame);
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
};