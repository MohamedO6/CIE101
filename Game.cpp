#include "Game.h"
#include "GameConfig.h"
#include "Plane.h"
#include "Enemy.h"
#include "BackGround.h"
#include "Bullet.h"
#include "Statuesbar.h"
#include "Toolbar.h"
#include "CMUgraphicsLib\CMUgraphics.h"
#include <fstream>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void playRefuelSound() {
	PlaySound(TEXT("fuel.wav"), NULL, SND_FILENAME | SND_ASYNC);
}


Game::Game()
{
	//1 - Create the main window
	pWind = CreateWind(config.windWidth, config.windHeight, config.wx, config.wy);

	//2 - create and draw the toolbar
	createToolbar();

	//3 - create and draw the backgroundPlayingArea
	background = BackGround();
	//4- Create the Plane
	plane = Plane();
	plane.setxplace(0);
	//TODO: Add code to create and draw the Plane 

	//5- Create the Bullet
	bullet = Bullet();
	//TODO: Add code to create and draw the Bullet

	//6-
	// ..Create the enemies
	enemy = Enemy();

	//TODO: Add code to create and draw enemies in random places
	responerate = 200;
	frameCount = 1;

	//7- Create and clear the status bar
	clearStatusBar();

}

Game::~Game()
{
	delete pWind;
	pWind = nullptr;
	delete gameToolbar;
	gameToolbar = nullptr;
}

clicktype Game::getMouseClick(int& x, int& y) const
{
	return pWind->WaitMouseClick(x, y);	//Wait for mouse click

}






string Game::getSrting() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else
			Label += Key;
		printMessage(Label);
	}
}

window* Game::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(config.bkGrndColor);
	pW->SetPen(config.bkGrndColor, 1);
	pW->DrawRectangle(0, 0, w, h);
	return pW;
}

void Game::createToolbar() 
{
	point toolbarUpperleft;
	toolbarUpperleft.x = 0;
	toolbarUpperleft.y = 0;

	gameToolbar = new Toolbar(this, toolbarUpperleft, 0, config.toolBarHeight);
	gameToolbar->draw();
}

void Game::clearStatusBar() const
{
	//Clear Status bar by drawing a filled rectangle
	pWind->SetPen(config.statusBarColor, 1);
	pWind->SetBrush(config.statusBarColor);
	pWind->DrawRectangle(0, config.windHeight - config.statusBarHeight, config.windWidth, config.windHeight);
}

void Game::printMessage(string msg) const
{
	clearStatusBar();	//First clear the status bar

	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, config.windHeight - (int)(0.85 * config.statusBarHeight), msg);

}

window* Game::getWind() const
{
	return pWind;
}

void Game::go()
{
	int x, y;
	bool isExit = false;
	bool isPlaying = false;
	char cKeyData;
	keytype kType;
	plane.setlives(5);
	// Change the title
	pWind->ChangeTitle("- - - - - - - - - - River Raid (CIE101-project) - - - - - - - - - -");


	do
	{

		if (!isPaused) {

			background.drawBackGround(*pWind);
			stbar.drawstatuesbar(*pWind, plane.getlives(), plane.getFuel(), Plane::score, enemy.getspeed());


			background.planebkg_collision(plane);
			background.calcleft(Plane::score);
			background.calcright(Plane::score);
			plane.drawPlayerPlane(*pWind, plane.getxplace(), 1300);
			bullet.MoveAllBullets(*pWind);
			enemy.MoveAllenemy(&background, enemy.getspeed(), enemy.getspeed());
			enemy.CollisionDetection(plane);
			enemy.plane_enemycollision(plane, background);
			bullet.RemoveOffScreenBullets();
			enemy.draw_all_enemies(*pWind);
			enemy.RemoveOffScreenenemy();
			gameToolbar->draw();

			if (frameCount % 10 == 0) {
				plane.decreaseFuel(1);
			}

			// Check for fuel depletion
			if (plane.getFuel() == 0 && plane.getlives() > 0) {
				plane.decreaselives();
				plane.setFuel(100);
				plane.setxplace(0);
			}

			// Fuel depot spawning and movement
			if (frameCount % (300 - (Plane::score / 100)) == 0) {
				for (int i = 0; i < 10; i++) {
					if (!fuelDepots[i]) {
						depotX[i] = background.getleft_border() + rand() % (background.getright_border() - background.getleft_border() - 30);
						depotY[i] = -40;
						fuelDepots[i] = true;
						break;
					}
				}
			}

			// Move, draw, and check collisions with fuel depots
			for (int i = 0; i < 10; i++) {
				if (fuelDepots[i]) {
					depotY[i] += 5;
					if (depotY[i] > 800) {
						fuelDepots[i] = false;
					}
					else {
						plane.drawFuelDepot(*pWind, depotX[i], depotY[i], true);

						// Check collision with plane for refueling
						int planeY = 535;
						int planewidth = 60;
						int planeheight = 65;
						int planecenterX = plane.getxplace();
						int planeX = planecenterX - planewidth / 2;
						int depotWidth = 30;
						int depotHeight = 40;

						if (planeX + 650 < depotX[i] + depotWidth &&
							planeX + 650 + planewidth > depotX[i] &&
							planeY < depotY[i] + depotHeight &&
							planeY + planeheight > depotY[i]) {
							playRefuelSound();
							plane.setFuel(100);
							fuelDepots[i] = false;
						}

						// Check collision with bullets to destroy depot
						for (int j = 0; j < Bullet::bulletCount; j++) {
							if (Bullet::active[j] &&
								Bullet::x[j] + 644 >= depotX[i] &&
								Bullet::x[j] + 644 <= depotX[i] + depotWidth &&
								Bullet::y[j] >= depotY[i] &&
								Bullet::y[j] <= depotY[i] + depotHeight) {

								Bullet::active[j] = false;
								fuelDepots[i] = false;
								break;
							}
						}
					}
				}
			}

			if (frameCount % responerate == 0) {
				enemy.generate_random_enemy(*pWind, &background, enemy.getenemycount());
				if (responerate > 50) {
					responerate--;
				}
			}

			kType = pWind->GetKeyPress(cKeyData);
			if (kType == ARROW || kType == ASCII) {
				if (cKeyData == 6 || cKeyData == 'D' || cKeyData == 'd') {
					plane.moveright(*pWind);
				}
				else if (cKeyData == 4 || cKeyData == 'A' || cKeyData == 'a') {
					plane.moveleft(*pWind);
				}
				else if (cKeyData == ' ') {
					bullet.LaunchBullet(*pWind, plane.getxplace());
				}
				else if (cKeyData == 8 || cKeyData == 'W' || cKeyData == 'w') {
					enemy.MoveAllenemy(&background, enemy.getspeed() * 2, enemy.getspeed() * 0.5);
				}
				else if (cKeyData == 2 || cKeyData == 'S' || cKeyData == 's') {
					enemy.MoveAllenemy(&background, -enemy.getspeed() * 0.5, -2 - enemy.getspeed() * 0.3);
				}
				else if (cKeyData == 27) {  // ESC key to exit
					isPlaying = false;
					isExit = true;
				}
			}
			frameCount++;
			int x, y;
			pWind->UpdateBuffer();
			Sleep(5);
			if (plane.getlives() < 1) {
				restartgame();	
				printMessage("Game Over, click start to restart");
				isPaused = true;
			}
		
		}
		if (pWind->GetMouseClick(x, y)) {
			bool Click = gameToolbar->handleClick(x, y);
		}
		


	} while (!isExit);

}


     
void Game::restartgame() {
	plane.restartactivity();
	enemy.restartactivity();
	Bullet::bulletCount = 0;
	plane.setFuel(100);
	for (int i = 0; i < 100; i++) {
		Bullet::active[i] = false;
	}
}
void Game::pausegame() {
	isPaused = true;
	printMessage("Game Paused");
}

void Game::requestexit() {
	printMessage("Exiting...");
	Sleep(500);  
	exit(0);
}

void Game::resumegame() {
	if (isPaused) {
		isPaused = false;
		printMessage("Game Resumed.");
	}
}


void Game::saveGame(string filename)
{
	ofstream out(filename);
	if (!out.is_open()) {
		printMessage("Unable to save data");
		return;
	}
	out << Plane::score << endl;
	out << enemy.getkills() << endl;
	out << plane.getlives() << endl;
	out << plane.getxplace()<< endl;
	out << plane.getFuel() << endl;

	out.close();
}

void Game::loadGame(string filename)
{
	ifstream in(filename);
	if (!in.is_open()) {
		return;
	}

	in >> Plane::score;
	int kills;
	int lives;
	float xPlace;
	int fuel;

	in >> kills;  
	in >> lives;     
	in >> xPlace;
	in >> fuel;

	plane.setFuel(fuel);
	enemy.setkills(kills);   
	plane.setlives(lives);   
	plane.setxplace(xPlace);
	in.close();
}