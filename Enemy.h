#pragma once
class BackGround;
#include "Plane.h"


class Enemy {
private:
	int x[100];
	double y[100];
	bool active[100];
	int enemyCount;
	int types[100];
	int direction[100];
	void drawShip(window& w, int x, int y, bool isActive, int width, int height);
	void drawTank(window& w, int x, int y, bool isActive, int width, int height );
	void drawBridge(window& w, int x, int y, bool isActive, int width, int height );
	void drawHelicopter(window& w, int x, int y, bool isActive, int width, int height);
	void drawJet(window& w, int x, int y, bool isActive, int width, int height);
	int kills=0;


public:
	void setenemycount(int x);
	void restartactivity();
	int getspeed();
	enum enemy_type { TANK, HELICOPTER, SHIP,JET ,BRIDGE };
	Enemy();
	int getenemycount() const;
	void Movenemy(int i, int speed);
	void generate_random_enemy(window& w, BackGround* background, int index);
	void MoveAllenemy(BackGround* background,int hspeed, int vspeed);
	void RemoveOffScreenenemy();
	void draw_all_enemies(window& w);
	void MoveJet(int index, BackGround* background, int hspeed);
	void MoveHelicopterandTank(int index, BackGround* background, int hspeed);
	void CollisionDetection(Plane plane);
	void remove_enemy();
	void plane_enemycollision(Plane& plane, BackGround& bkg);
	int getkills() const;
	void setkills(int x);
};