#pragma once
#include "CMUgraphicsLib\CMUgraphics.h"
#include "Toolbar.h"
#include "Plane.h"
#include "Enemy.h"
#include "BackGround.h"
#include "Bullet.h"
#include "Statuesbar.h"


class Game
{
private:
	window* pWind;	//Pointer to the CMU graphics window
	Toolbar* gameToolbar;
	Plane plane;      
	Enemy enemy;     
	BackGround background; 
	Bullet bullet;    
	int frameCount;  
	int responerate;
	statuebar stbar;
	bool isPaused = false;

public:
	Game();
	~Game();
	void restartgame();
	void pausegame();
	void requestexit();
	void resumegame();
	void saveGame(string filename);
	void loadGame(string filename);
	bool fuelDepots[10];
	int depotX[10], depotY[10];
	clicktype getMouseClick(int& x, int& y) const; //Get coordinate where user clicks and returns click type (left/right)
	string getSrting() const;	 //Returns a string entered by the user


	window* CreateWind(int, int, int, int) const; //creates the game window
	void createToolbar();
	void clearStatusBar() const;	//Clears the status bar
	


	void printMessage(string msg) const;	//Print a message on Status bar

	void go();

	window* getWind() const;		//returns a pointer to the graphics window
};

