#include "CMUgraphicsLib\CMUgraphics.h"
#include "CMUgraphicsLib\auxil.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Plane.h"
#include "background.h"
#include <cstdlib>

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void playcollisionSound1() {
    PlaySound(TEXT("explosion.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void playcollisionSound2() {
    PlaySound(TEXT("soundc.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

Enemy::Enemy() {
    enemyCount = 0;
}
void Enemy::drawShip(window& w, int x, int y ,bool isActive, int width=60, int height=30) {
    if (!isActive) return;
    int hullX[] = { x, x + width, x + width * 8 / 10, x + width * 2 / 10 };
    int hullY[] = { y, y, y + height, y + height };
    w.SetBrush(DARKGREY);
    w.SetPen(BLACK, 2);
    w.DrawPolygon(hullX, hullY, 4, FILLED);
    int topX[] = { x + 5, x + width - 5, x + width * 85 / 100, x + width * 15 / 100 };
    int topY[] = { y + 5, y + 5, y + height * 7 / 10, y + height * 7 / 10 };
    w.SetBrush(GRAY);
    w.DrawPolygon(topX, topY, 4, FILLED);
    w.SetBrush(BLACK);
    w.DrawRectangle(x + width * 3 / 10, y - height * 5 / 10,
        x + width * 7 / 10, y, FILLED);
    w.SetBrush(WHITE);
    w.DrawRectangle(x + width * 4 / 10, y - height * 4 / 10,
        x + width * 45 / 100, y - height * 2 / 10, FILLED);
    w.DrawRectangle(x + width * 55 / 100, y - height * 4 / 10,
        x + width * 6 / 10, y - height * 2 / 10, FILLED);
    w.SetBrush(BLACK);
    w.DrawRectangle(x + width * 65 / 100, y - height * 7 / 10,
        x + width * 7 / 10, y - height * 5 / 10, FILLED);
    w.SetBrush(GRAY);
    w.DrawCircle(x + width * 675 / 1000, y - height * 9 / 10, 5, FILLED);
    w.DrawCircle(x + width * 7 / 10, y - height * 11 / 10, 3, FILLED);
}

void Enemy::drawTank(window& w, int x, int y,bool isActive, int width=60, int height=30) {
    if (!isActive) return;
    w.SetBrush(0.33, 0.42, 0.18);
    w.SetPen(DARKGREY, 2);
    w.DrawRectangle(x, y,
        x + width, y + height, FILLED);
    w.SetBrush(0.25, 0.32, 0.14);
    w.DrawRectangle(x + 5, y + 5,
        x + width - 5, y + height * 8 / 10, FILLED);
    w.SetBrush(DARKGREY);
    w.DrawPolygon(new int[4] {x + width * 3 / 10, x + width * 7 / 10,
        x + width * 65 / 100, x + width * 25 / 100},
        new int[4] {y - height * 3 / 10, y - height * 3 / 10,
        y + height * 2 / 10, y + height * 2 / 10},
        4, FILLED);
    w.SetPen(BLACK, 3);
    w.DrawLine(x + width * 65 / 100, y - height * 5 / 100,
        x + width * 12 / 10, y - height * 3 / 10);
    w.SetBrush(BLACK);
    for (int i = 0; i < 5; i++) {
        w.DrawRectangle(x - 5, y + i * height * 2 / 10,
            x, y + (i + 1) * height * 2 / 10 - 2, FILLED);
        w.DrawRectangle(x + width, y + i * height * 2 / 10,
            x + width + 5, y + (i + 1) * height * 2 / 10 - 2, FILLED);
    }
    w.SetPen(BLACK, 1);
    w.DrawLine(x + width * 3 / 10, y - height * 3 / 10,
        x + width * 3 / 10, y - height * 8 / 10);
    w.SetBrush(0.20, 0.25, 0.10);
    w.DrawCircle(x + width * 2 / 10, y + height * 3 / 10, 5, FILLED);
    w.DrawCircle(x + width * 8 / 10, y + height * 7 / 10, 4, FILLED);
}

void Enemy::drawBridge(window& w, int x, int y,bool isActive, int width=300, int height=20 ) {
    if (!isActive) return;
    w.SetBrush(BROWN);
    w.SetPen(DARKGREY, 2);
    w.DrawRectangle(x, y,
        x + width, y + height, FILLED);
    w.SetBrush(KHAKI);
    w.DrawRectangle(x + 5, y + 5,
        x + width - 5, y + height - 5, FILLED);
    w.SetBrush(MAROON);
    w.SetPen(BLACK, 3);
    w.DrawArc(x, y - height * 5 / 10,
        x + width, y + height * 5 / 10, 180, 360, FILLED);
    w.SetPen(DARKGREY, 1);
    w.DrawArc(x + 3, y - height * 5 / 10 + 3,
        x + width + 3, y + height * 5 / 10 + 3, 180, 360, FRAME);
    w.SetPen(BLACK, 1);
    for (int i = 0; i < width; i += 10) {
        w.DrawLine(x + i, y,
            x + i + 5, y);
        w.DrawLine(x + i, y + height,
            x + i + 5, y + height);
        w.DrawLine(x + i + 2, y,
            x + i + 2, y - height * 3 / 10);
        w.DrawLine(x + i + 2, y + height,
            x + i + 2, y + height + height * 3 / 10);
    }
    for (int i = 1; i <= 3; i++) {
        int supportX = x + (width / 4) * i;
        w.DrawLine(supportX, y,
            x + width / 2, y + height);
        w.DrawLine(supportX, y + height,
            x + width / 2, y);
    }
    w.SetPen(LIGHTBLUE, 1);
    for (int i = 0; i < 5; i++) {
        int waveY = y + height + 5 + i * 3;
        for (int j = 0; j < width; j += 20) {
            w.DrawLine(x + j, waveY,
                x + j + 10, waveY + 2);
            w.DrawLine(x + j + 10, waveY + 2,
                x + j + 20, waveY);
        }
    }
}

void Enemy::drawHelicopter(window& w, int x, int y ,bool isActive, int width=40, int height=20) {
    if (!isActive) return;
    w.SetBrush(GRAY);
    w.SetPen(BLACK, 2);
    w.DrawEllipse(x, y,
        x + width, y + height, FILLED);
    w.SetBrush(DARKGREY);
    w.DrawEllipse(x + 3, y + 3,
        x + width - 3, y + height - 3, FILLED);
    w.SetPen(BLACK, 3);
    w.DrawLine(x - 5, y - 5,
        x + width + 5, y - 5);
    w.DrawLine(x, y - 10,
        x + width, y);
    w.SetPen(BLACK, 1);
    w.DrawLine(x + width, y + height / 2,
        x + width + 15, y + height / 2);
    w.DrawLine(x + width + 15, y + height / 2 - 5,
        x + width + 15, y + height / 2 + 5);
    w.SetBrush(LIGHTBLUE);
    w.DrawArc(x + width * 2 / 10, y,
        x + width * 5 / 10, y + height * 5 / 10, 0, 180, FILLED);
    w.SetBrush(DARKGREY);
    w.DrawRectangle(x + width * 7 / 10, y + height,
        x + width * 9 / 10, y + height + 7, FILLED);
    w.SetBrush(RED);
    w.DrawCircle(x + width * 75 / 100, y + height + 3, 2, FILLED);
    w.DrawCircle(x + width * 85 / 100, y + height + 3, 2, FILLED);
    w.SetPen(BLACK, 1);
    w.DrawLine(x + width * 3 / 10, y + height,
        x + width * 3 / 10, y + height + 5);
    w.DrawLine(x + width * 7 / 10, y + height,
        x + width * 7 / 10, y + height + 5);
    w.SetPen(RED, 2);
    w.DrawLine(x + width * 5 / 10, y + height,
        x + width, y + height);
}

void Enemy::drawJet(window& w, int x, int y,bool isActive,int width=50, int height=30) {
    if (!isActive) return;
    w.SetBrush(BLACK);
    w.SetPen(BLACK, 1);
    w.DrawTriangle(x - width * 2 / 10, y + height * 5 / 10,
        x + width, y,
        x + width, y + height, FILLED);
    w.SetBrush(DARKGREY);
    w.DrawTriangle(x, y + height * 5 / 10,
        x + width * 8 / 10, y + height * 2 / 10,
        x + width * 8 / 10, y + height * 8 / 10, FILLED);
    w.SetBrush(DARKGREY);
    w.DrawTriangle(x + width * 3 / 10, y + height * 5 / 10,
        x + width * 5 / 10, y - height * 3 / 10,
        x + width * 7 / 10, y + height * 5 / 10, FILLED);
    w.DrawTriangle(x + width * 3 / 10, y + height * 5 / 10,
        x + width * 5 / 10, y + height * 13 / 10,
        x + width * 7 / 10, y + height * 5 / 10, FILLED);
    w.SetBrush(LIGHTBLUE);
    w.DrawArc(x + width * 5 / 10, y + height * 2 / 10,
        x + width * 7 / 10, y + height * 5 / 10, 0, 180, FILLED);
    w.SetBrush(WHITE);
    w.DrawCircle(x + width * 6 / 10, y - height * 1 / 10, 5, FILLED);
    w.DrawCircle(x + width * 6 / 10, y + height * 11 / 10, 5, FILLED);
    w.SetBrush(ORANGE);
    w.DrawTriangle(x - width * 2 / 10, y + height * 5 / 10,
        x - width * 5 / 10, y + height * 3 / 10,
        x - width * 5 / 10, y + height * 7 / 10, FILLED);
    w.SetBrush(YELLOW);
    w.DrawTriangle(x - width * 2 / 10, y + height * 5 / 10,
        x - width * 4 / 10, y + height * 4 / 10,
        x - width * 4 / 10, y + height * 6 / 10, FILLED);
}

void Enemy::generate_random_enemy(window& w ,BackGround* background ,int index) {
    background->calcleft(Plane::score);
    background->calcright(Plane::score);
    if (index >= 100) return;  

    int enemy = TANK + rand() % (BRIDGE - TANK + 1);
    int xcoo =  ((background->getleft_border()+50) + rand() % 
        ((background->getright_border() - 50) - (background->getleft_border() + 50) + 1));
    int ycoo = -100;    
    x[index] = xcoo;
    y[index] = ycoo;
    active[index] = true;
    types[index] = enemy;
    direction[index] = -1;
    enemyCount++;


    if (enemy == JET) {
        xcoo = background->getright_border() - 40;
        y[index] = ycoo;
        active[index] = true;
        types[index] = enemy;
        direction[index] = -1;
        enemyCount++;
    }
}

int Enemy::getenemycount() const {
    return enemyCount;
}

void Enemy::Movenemy(int index, int vspeed) {
    if (active[index]) {
        y[index] += vspeed;
    }
}

void Enemy::MoveHelicopterandTank(int index,BackGround* background,int hspeed) {
    if (y[index] > 200) {

        x[index] += (direction[index] * 10);
        if (x[index] <= background->getleft_border() ) {
            direction[index] *= -1;
            x[index] += hspeed;
        }
        else if (x[index] >= background->getright_border()) {
            direction[index] *= -1;
            x[index] -= hspeed;
        }
    }


    
}

void Enemy::MoveJet(int index, BackGround* background, int hspeed) {
    if (y[index] > 200) {
        x[index] -= hspeed;
    }
}

void Enemy::MoveAllenemy(BackGround* background, int vspeed, int hspeed) {
    for (int i = 0; i < 100; ++i) {

        if (active[i]) {
            if ((types[i] == HELICOPTER) || (types[i] == TANK)) {
                MoveHelicopterandTank(i, background,hspeed);
            }
            else if ((types[i] == JET)) {
                MoveJet(i, background, hspeed);
            }
                Movenemy(i, vspeed);

        }
    }
}

void Enemy::draw_all_enemies(window& w) {
    for (int i = 0; i < 100; i++) {
        if (active[i]) {
            int xcoo = x[i];
            int ycoo = y[i];
            int type = types[i];
            bool isActive = active[i];

            if (type == TANK) {
                drawTank(w, xcoo, ycoo, isActive);
            }
            else if (type == HELICOPTER) {
                drawHelicopter(w, xcoo, ycoo, isActive);
            }
            else if (type == SHIP) {
                drawShip(w, xcoo, ycoo, isActive);
            }
            else if (type == JET) {
                drawJet(w, xcoo, ycoo, isActive);
            }
            else if (type == BRIDGE) {
                drawBridge(w, xcoo, ycoo, isActive);
            }
        }
    }
}





void Enemy::RemoveOffScreenenemy() {
    for (int i = 0; i < enemyCount; ++i) {
        if (y[i] > 800 || x[i] > 1300) {
            active[i] = false;
        }
    }
    int j = 0;
    for (int i = 0; i < enemyCount; ++i) {
        if (active[i]) {
            x[j] = x[i];
            y[j] = y[i];
            active[j] = active[i];
            types[j] = types[i];
            direction[j] = direction[i];
            ++j;
        }
    }
    enemyCount = j;
}



void Enemy::CollisionDetection(Plane plane)
{
    for (int i = 0; i < Bullet::bulletCount; i++) {
            for (int j = 0; j < enemyCount; j++) {
                if (active[j]) {

                    int enemyWidth = 0;
                    int enemyHeight = 0;

                    switch (types[j]) {
                    case BRIDGE:
                        enemyWidth = 290;
                        enemyHeight = 20;
                        break;

                    case SHIP:
                        enemyWidth = 60;
                        enemyHeight = 30;
                        break;

                    case HELICOPTER:
                        enemyWidth = 60;
                        enemyHeight = 20;
                        break;

                    case TANK:
                        enemyWidth = 60;
                        enemyHeight = 30;
                        break;

                    case JET:
                        enemyWidth = 50;
                        enemyHeight = 30;
                        break;
                    }


                    if (Bullet::x[i] + 644 >= x[j] && Bullet::x[i] + 644 <= x[j] + enemyWidth &&
                        Bullet::y[i] >= y[j] && Bullet::y[i] < y[j] + enemyHeight) {
                        playcollisionSound2();
                        kills++;
                        Bullet::active[i] = false;
                        active[j] = false;

                        if (types[j] == BRIDGE) {
                            Plane::score += 500;
                        }
                        else if (types[j] == SHIP) {
                            Plane::score += 30;
                        }
                        else if (types[j] == HELICOPTER) {
                            Plane::score += 60;
                        }
                        else if (types[j] == TANK) {
                            Plane::score += 30;
                        }
                        else if (types[j] == JET) {
                            Plane::score += 100;
                        }
                        int newEnemyCount = 0;
                        for (int ei = 0; ei < enemyCount; ++ei) {
                            if (active[ei]) {
                                x[newEnemyCount] = x[ei];
                                y[newEnemyCount] = y[ei];
                                active[newEnemyCount] = active[ei];
                                types[newEnemyCount] = types[ei];
                                direction[newEnemyCount] = direction[ei];
                                ++newEnemyCount;
                            }
                        }
                        enemyCount = newEnemyCount;
                        int newBulletCount = 0;
                        for (int bi = 0; bi < Bullet::bulletCount; ++bi) {
                            if (Bullet::active[bi]) {
                                Bullet::x[newBulletCount] = Bullet::x[bi];
                                Bullet::y[newBulletCount] = Bullet::y[bi];
                                Bullet::c[newBulletCount] = Bullet::c[bi];
                                Bullet::active[newBulletCount] = Bullet::active[bi];
                                ++newBulletCount;
                            }
                        }
                        Bullet::bulletCount = newBulletCount;
                    }
                }
            }
        }
    }
    

void Enemy::plane_enemycollision(Plane& plane, BackGround& bkg) {
        for (int j = 0; j < enemyCount; j++) {
            if (active[j]) {

                int enemyWidth = 0;
                int enemyHeight = 0;

                switch (types[j]) {
                case BRIDGE:
                    enemyWidth = 290;
                    enemyHeight = 20;
                    break;

                case SHIP:
                    enemyWidth = 60;
                    enemyHeight = 30;
                    break;

                case HELICOPTER:
                    enemyWidth = 60;
                    enemyHeight = 20;
                    break;

                case TANK:
                    enemyWidth = 60;
                    enemyHeight = 30;
                    break;

                case JET:
                    enemyWidth = 50;
                    enemyHeight = 30;
                    break;
                }

                int planeY = 535;
                int planewidth = 60;
                int planeheight = 65;
                int planecenterX = plane.getxplace();

                int planeX = planecenterX - planewidth / 2;

                if ((planeX +650< x[j] + enemyWidth&&
                    planeX +650+ planewidth > x[j] &&
                    planeY < y[j] + enemyHeight &&
                    planeY + planeheight > y[j])){
                    playcollisionSound1();

                    active[j] = false;
                    if (Plane::score < 100) {
                        Plane::score = 0;

                    }
                    else{
                        Plane::score -= 100;
                    }
                    plane.decreaselives();
                    plane.setxplace(0);

                    int newEnemyCount = 0;
                    for (int ei = 0; ei < enemyCount; ++ei) {
                        if (active[ei]) {
                            x[newEnemyCount] = x[ei];
                            y[newEnemyCount] = y[ei];
                            active[newEnemyCount] = active[ei];
                            types[newEnemyCount] = types[ei];
                            direction[newEnemyCount] = direction[ei];
                            ++newEnemyCount;
                        }
                    }
                    enemyCount = newEnemyCount;

                }
                
            }
        }
    }


void Enemy::remove_enemy() {
    int j = 0;
    for (int i = 0; i < enemyCount; ++i) {
        if (active[i]) {
            x[j] = x[i];
            y[j] = y[i];
            active[j] = active[i];
            types[j] = types[i];
            direction[j] = direction[i];
            ++j;
        }

        enemyCount = j;
    }
}

int Enemy::getspeed() {
    int speed = kills * 0.1+2;
    return speed;
}


int Enemy::getkills()const {
    return kills;
}

void Enemy::setkills(int x) {
	kills = x;
}

void Enemy::setenemycount(int x) {
    enemyCount = x;
}

void Enemy::restartactivity() {
    setkills(0);
    setenemycount(0);
    for (int i = 0; i < 100; i++) {
        active[i] = false;
    }
}