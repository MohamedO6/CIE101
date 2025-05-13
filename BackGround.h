#pragma once
#include "Plane.h"
#include "Enemy.h"

class BackGround {
private:
	int* x = &(Plane::score);
	int left_border;
	int right_border;

public:
	int getleft_border();
	int getright_border();
	void setleft_border(int x);
	void setright_border(int x);

	void drawBackGround(window& w);
	void calcright(int x);
	void calcleft(int x);
	void planebkg_collision(Plane &plane);


};
