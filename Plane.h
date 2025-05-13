#pragma once
#include "CMUgraphicsLib\CMUgraphics.h"


class Plane {
private:
	int fuel;
	int lives;
	int xplace;
public:
	void restartactivity();
	void decreaselives();
	static int score;
	void moveleft(window& w);
	void moveright(window& w);
	void drawPlayerPlane(window& w, int x, int screenWidth);
	void drawFuelDepot(window& w, int baseX, int baseY, bool isActive);
	void setxplace(int x);
	int getxplace() const;
	int getlives() const;
	void setlives(int l);
	int getFuel() const; // Get current fuel
	void setFuel(int f); // Set fuel value
	void decreaseFuel(int amount); // Decrease fuel by amount

};