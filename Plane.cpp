#include "Plane.h"
int Plane::score = 0;
#include "BackGround.h"

void Plane::drawPlayerPlane(window& w, int x, int screenWidth=1300) {
	w.SetPen(RED, 5);
	w.SetBrush(BLACK);
	w.DrawTriangle((screenWidth / 2 - 20) + x, 600, (screenWidth / 2) + x, 535, (screenWidth / 2 + 20) + x, 600);
	w.SetPen(RED, 3);
	w.SetBrush(BLACK);
	w.DrawRectangle((screenWidth / 2 - 40) + x, 600, (screenWidth / 2 + 40) + x, 610);
	w.SetPen(RED, 3);
	w.SetBrush(BLACK);
	w.DrawRectangle((screenWidth / 2 - 45) + x, 620, (screenWidth / 2 + 45) + x, 630);
	w.DrawTriangle((screenWidth / 2 - 30) + x, 640, (screenWidth / 2) + x, 570, (screenWidth / 2 + 30) + x, 640);
}

void Plane::moveright(window& w) {
            xplace += 20;
    }

void Plane::moveleft(window& w) {
    xplace -= 20;
}

void Plane::drawFuelDepot(window& w, int baseX, int baseY, bool isActive) {
    int width = 30;
    int height = 40;
    if (!isActive) return;
    w.SetBrush(DARKGRAY);
    w.SetPen(DARKGRAY, 1);
    w.DrawRectangle(baseX - 8, baseY + height + 2, baseX + width + 8, baseY + height + 8, FILLED);
    w.SetBrush(0.65, 0.65, 0.65);
    w.SetPen(DARKGRAY, 1);
    w.DrawArc(baseX + 2, baseY + 2, baseX + width + 2, baseY + height / 10 + 2, 180, 360, FILLED);
    w.DrawArc(baseX + 2, baseY + height * 9 / 10 + 2, baseX + width + 2, baseY + height + 2, 0, 180, FILLED);
    w.DrawRectangle(baseX + 2, baseY + height / 10 + 2, baseX + width + 2, baseY + height * 9 / 10 + 2, FILLED);
    w.SetBrush(0.75, 0.75, 0.75);
    w.SetPen(BLACK, 2);
    w.DrawArc(baseX, baseY, baseX + width, baseY + height / 10, 180, 360, FILLED);
    w.DrawArc(baseX, baseY + height * 9 / 10, baseX + width, baseY + height, 0, 180, FILLED);
    w.DrawRectangle(baseX, baseY + height / 10, baseX + width, baseY + height * 9 / 10, FILLED);
    w.SetPen(BLACK, 2);
    w.DrawLine(baseX - 15, baseY + height / 4, baseX, baseY + height / 4);
    w.DrawLine(baseX - 15, baseY + height / 2, baseX, baseY + height / 2);
    w.SetBrush(GRAY);
    w.DrawRectangle(baseX + width + 3, baseY + height, baseX + width + 10, baseY + height + 15, FILLED);
    w.DrawRectangle(baseX + width + 12, baseY + height, baseX + width + 19, baseY + height + 15, FILLED);
    w.SetPen(BLACK, 1);
    w.DrawLine(baseX + width + 19, baseY + height + 15, baseX + width + 25, baseY + height + 15);
    w.DrawLine(baseX + width + 25, baseY + height + 15, baseX + width + 25, baseY + height + 20);
    w.SetBrush(YELLOW);
    w.DrawTriangle(baseX + width / 2 - 8, baseY - 8, baseX + width / 2, baseY - 20, baseX + width / 2 + 8, baseY - 8, FILLED);
    w.SetBrush(RED);
    w.DrawCircle(baseX + width / 2, baseY - 12, 3, FILLED);
}

int Plane::getxplace() const{
    return xplace;
}
void Plane::setxplace(int x = 0) {
    xplace = x;
}


void Plane::decreaselives() {
	lives--;
}

int Plane::getlives() const {
	return lives;
}
void Plane::setlives(int l) {
    lives = l;
}

void Plane::restartactivity() {
	lives = 3;
	xplace = 0;
    score = 0;
}

int Plane::getFuel() const {
    return fuel;
}

void Plane::setFuel(int f) {
    fuel = f;
    if (fuel < 0) fuel = 0;
    if (fuel > 100) fuel = 100;
}

void Plane::decreaseFuel(int amount) {
    fuel -= amount;
    if (fuel < 0) fuel = 0;
}

