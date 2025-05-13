#include "BackGround.h"
#include "CMUgraphicsLib\CMUgraphics.h"
#include "CMUgraphicsLib\auxil.h"	
#include <sstream>
#include <cmath>
#include "Enemy.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void playcollisionSound4() {
    PlaySound(TEXT("explosion.wav"), NULL, SND_FILENAME | SND_ASYNC);
}


void BackGround::drawBackGround(window& w) {
	int screenHight = w.GetHeight();
	int screenWidth = w.GetWidth();
	w.SetPen(BLACK, 5);
	w.SetBrush(DARKGOLDENROD);
	w.DrawRectangle(0, 0,left_border, screenHight);
	w.DrawRectangle(right_border, 0, screenWidth, screenHight);
	w.SetPen(BLACK, 5);
	w.SetBrush(BLUE);
	w.DrawRectangle(left_border, 0, right_border, screenHight);
}

int BackGround::getleft_border(){
	return left_border;
}
int BackGround::getright_border(){
	return right_border;
}

void BackGround::setright_border(int x) {
	right_border = x;
}
void BackGround::setleft_border(int x) {
	left_border = x;
}

void BackGround::calcright(int x) {
	right_border = (1300 - 50) - 0.02 *x;
}
void BackGround::calcleft(int x) {
	left_border = 50 + 0.02 * x;
}


void BackGround::planebkg_collision(Plane& plane) {
    int planeY = 535;
    int planewidth = 60;
    int planeheight = 65;
    int planecenterX = plane.getxplace();

    int planeX = planecenterX - planewidth / 2;
    if ((planeX + 660 + planewidth >= getright_border()
        || (planeX + 650 - ((planewidth / 2 - 10))) <= getleft_border())) {
        playcollisionSound4();


        if (Plane::score < 100) {
            Plane::score = 0;
        }
        else {
            Plane::score -= 100;
        }
        plane.decreaselives();
        plane.setxplace(0);
    }
}
