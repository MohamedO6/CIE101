#pragma once
#include "CMUgraphicsLib\CMUgraphics.h"

class Bullet {
private:
 

public:
    static  int x[100];
    static  int y[100];
    static  color c[100];
    static  bool active[100];
    static  int bulletCount;

    Bullet(); 
    void DrawBullet(window& w, int i); 
    void MoveBullet(int i);       
    void LaunchBullet(window& w, int startX,color col=GOLD); 
    void MoveAllBullets(window& w); 
    void RemoveOffScreenBullets(); 
};
