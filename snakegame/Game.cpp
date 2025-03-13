#include "Game.h"
#include "graphics.h"
#include "config.h"
#include "Gameobject.h"


void Game::spawnApple()
{
	if (!apple) {
		apple = new Apple(*this);
	}
}

void Game::checkApple()
{
	if (apple && !apple->isActive()) {
		delete apple;
		apple = nullptr;
	}
}
bool Game::checkCollision()
{
	if (!player || !apple) {
		return false;
	}
	Disk d1 = player->getCollisionHull();
	Disk d2 = apple->getCollisionHull();
	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;
	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {
		player->turnscore();
		player->growtail();
		player->growspeed();
		return true;
	}
	else {
		return false;
	}
}

void Game::updateStartScreen()
{
	if(graphics::getKeyState(graphics::SCANCODE_RETURN)){
		status = STATUS_PLAYING;
	}
}

void Game::updateEndScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		status = STATUS_PLAYING;
		player->zeroscore();
		player = new Player(*this);
	}
		
}

void Game::updateLevelScreen()
{
	if (!player_initialized && graphics::getGlobalTime() > 1000) {
		player = new Player(*this);
		player_initialized = true;
	}
	if (player)
		player->update();
		checkApple();
		spawnApple();
	if (apple)
		apple->update();
	if (checkCollision()) {
		delete apple;
		apple = nullptr;
	}
}

void Game::drawStartScreen()
{
	graphics::Brush br;
	br.fill_color[0] = 0.5f;
	br.fill_color[1] = 0.6f;
	br.fill_color[2] = 0.2f;
	br.texture = std::string(ASSET_PATH) + "snk1.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 0.3f;

	br.outline_color[0] = 0.5f;
	br.outline_color[1] = 1.1f;
	br.outline_color[2] = 0.1f;

	br.outline_width = 1.0f;

	graphics::resetPose();
	drawText(350, 250, 130, "SNAKE", br);
	drawText(250, 400, 70, "Press enter to continue", br);
	graphics::setFont(std::string(ASSET_PATH) + "Alaska-Regular.ttf");
}

void Game::drawEndScreen()                                                          
{
	graphics::Brush br;
	br.fill_color[0] = 0.5f;
	br.fill_color[1] = 0.6f;
	br.fill_color[2] = 0.2f;
	br.texture = std::string(ASSET_PATH) + "endim.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 0.3f;

	br.outline_color[0] = 0.5f;
	br.outline_color[1] = 1.1f;
	br.outline_color[2] = 0.1f;

	br.outline_width = 1.0f;

	graphics::resetPose();
	drawText(280, 190, 110, "GAME OVER", br);
	char info2[40];
	sprintf_s(info2, "%0.0f", player->getRemainingScore());
	graphics::drawText(550, 300, 60, info2, br);
	drawText(350, 300, 60, "Score is:", br);
	drawText(270, 410, 50, "Press enter to try again", br);
	graphics::setFont(std::string(ASSET_PATH) + "Alaska-Regular.ttf");
}

void Game::drawLevelScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "bg-green.png";
	br.outline_opacity = 0.0f;

	//draw backround
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	//draw player
	if (player) {
		player->draw();
	}
	if (apple)
		apple->draw();
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.3f;

	br.outline_color[0] = 0.5f;
	br.outline_color[1] = 0.8f;
	br.outline_color[2] = 0.2f;

	if (player) {
		char info2[40];
		sprintf_s(info2, "(%0.0f)", player->getRemainingScore());
		graphics::drawText(CANVAS_WIDTH - 80, CANVAS_HEIGHT - 475, 25, info2, br);
		graphics::drawText(CANVAS_WIDTH - 150, CANVAS_HEIGHT - 475, 25, "Score:", br);

		graphics::setFont(std::string(ASSET_PATH) + "TheGodfather-v2.ttf");
	}
}

void Game::update()
{
	if (status == STATUS_START) {
		updateStartScreen();
	}
	else if (status == STATUS_PLAYING && player->getRemainingScore() == 20) {			//teleiwnei to paixnidi otan to score ginei 20
		updateEndScreen();

	}
	else{
		updateLevelScreen();
	}

	if (!player_initialized && graphics::getGlobalTime() > 1000) {
		player = new Player(*this);
		player_initialized = true;
	}
	if (player)
		player->update();
		checkApple();
		spawnApple();
	if (apple)
		apple->update();
	if (checkCollision()) {
		delete apple;
		apple = nullptr;
	}
}

void Game::draw()
{
	if (status == STATUS_START) {
		drawStartScreen();
	}
	else if (status == STATUS_PLAYING && player->getRemainingScore() == 20) {          //teleiwnei to paixnidi otan to score ginei 20  
		drawEndScreen();                                                                 
	}
	else {
		drawLevelScreen();
	}
}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "PG_Roof Runners_active.ttf");
	graphics::playMusic(std::string(ASSET_PATH) + "Snake.mp3", 0.5f, true, 4000);
}

Game::Game()
{
}

Game::~Game()
{
	if (player)
		delete player;
}
