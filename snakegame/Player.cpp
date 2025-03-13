#include "Player.h"
#include "graphics.h"
#include "Game.h"
#include "config.h"

Player::Player(const Game & mygame)
	:Gameobject(mygame)
{
	
}

void Player::update()
{
	float a = tailX[0];
	float b = tailY[0];
	float c, d;
	tailX[0] = pos_x;
	tailY[0] = pos_y;
	for (int i = 1; i < lengthtail; i++) {
		c = tailX[i];
		d = tailY[i];
		tailX[i] = a;
		tailY[i] = b;
		a = c;
		b = d;
	}


	if (start == 1) {
		pos_x -= speed * graphics::getDeltaTime() / 10.0f;
	}
	else if (start == 2) {
		pos_x += speed * graphics::getDeltaTime() / 10.0f;
	}
	else if (start == 3) {
		pos_y -= speed * graphics::getDeltaTime() / 10.0f;
	}
	else {
		pos_y += speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_LEFT) && !graphics::getKeyState(graphics::SCANCODE_RIGHT) && !graphics::getKeyState(graphics::SCANCODE_UP) && !graphics::getKeyState(graphics::SCANCODE_DOWN)) {
		start = 1;
	}
	if (graphics::getKeyState(graphics::SCANCODE_RIGHT) && !graphics::getKeyState(graphics::SCANCODE_LEFT) && !graphics::getKeyState(graphics::SCANCODE_UP) && !graphics::getKeyState(graphics::SCANCODE_DOWN)) {
		start = 2;
	}
	if (graphics::getKeyState(graphics::SCANCODE_UP) && !graphics::getKeyState(graphics::SCANCODE_LEFT) && !graphics::getKeyState(graphics::SCANCODE_RIGHT) && !graphics::getKeyState(graphics::SCANCODE_DOWN)) {
		start = 3;
	}
	if (!graphics::getKeyState(graphics::SCANCODE_LEFT) && !graphics::getKeyState(graphics::SCANCODE_RIGHT) && !graphics::getKeyState(graphics::SCANCODE_UP) && graphics::getKeyState(graphics::SCANCODE_DOWN)) {
		start = 4;
	}

	if (pos_x < 0) pos_x = CANVAS_WIDTH;
	if (pos_x > CANVAS_WIDTH) pos_x = 0;
	if (pos_y < 0) pos_y = CANVAS_HEIGHT;
	if (pos_y > CANVAS_HEIGHT) pos_y = 0;

}

void Player::draw()
{

	graphics::Brush br;
	
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.5f;
	br.fill_color[2] = 0.0f;
	br.outline_opacity = 1.0f;

	if (start == 1) {
		opa = 0;
		for (int j = 0; j < lengthtail; j++) {
			graphics::drawDisk(tailX[j] + opa, tailY[j], 10, br);
			opa = opa + 20;
		}
	}
	else if (start == 2) {
		opa = 0;
		for (int j = 0; j < lengthtail; j++) {
			graphics::drawDisk(tailX[j] - opa, tailY[j], 10, br);
			opa = opa + 20;
		}
	}
	else if (start == 3) {
		opa = 0;
		for (int j = 0; j < lengthtail; j++) {
			graphics::drawDisk(tailX[j], tailY[j] + opa, 10, br);
			opa = opa + 20;
		}
	}
	else {
		opa = 0;
		for (int j = 0; j < lengthtail; j++) {
			graphics::drawDisk(tailX[j], tailY[j] - opa, 10, br);
			opa = opa + 20;
		}
	}
	/*if (game.getDebugMode()) {
	br.outline_opacity = 1.0f;
	br.texture = "";
	br.fill_color[0] = 0.3f;
	br.fill_color[0] = 1.0f;
	br.fill_color[0] = 0.3f;
	br.fill_opacity = 0.3f;
	br.gradient = false;
	Disk hull = getCollisionHull();
	graphics::drawDisk(hull.cx, hull.cy,hull.radius, br);
	}*/
}


void Player::init()
{
}

Disk Player::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 10.0f;
	return disk;
}
