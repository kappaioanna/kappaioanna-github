#include "Apple.h"
#include "graphics.h"
#include "config.h"
#include<random>
#include "util.h"
#include "Game.h"



void Apple::update()
{	
}

void Apple::draw()
{
	brush.texture = std::string(ASSET_PATH) + "apple.png";
	graphics::drawRect(pos_x, pos_y, size, size, brush);
	graphics::resetPose();
}

void Apple::init()
{
	pos_x = CANVAS_HEIGHT*randapple();
	if (pos_x-60< 0) pos_x = 60;
	if (pos_x+60 > CANVAS_WIDTH) pos_x = CANVAS_WIDTH-60;
	pos_y = CANVAS_HEIGHT *randapple();
	if (pos_y-60< 0) pos_y = 60;
	if (pos_y+120 > CANVAS_HEIGHT) pos_y = CANVAS_HEIGHT-120;
	size = 50.0;
	brush.outline_opacity = 0.0f;
}

Apple::Apple(const Game& mygame)
	:Gameobject(mygame)
{
	init();
}

Apple::~Apple()
{
}

Disk Apple::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size * 0.40f;
	return disk;
}