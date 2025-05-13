#include "Bullet.h"

int Bullet::x[100] = { 0 };          
int Bullet::y[100] = { 0 };        
color Bullet::c[100] = {};      
bool Bullet::active[100] = { false }; 
int Bullet::bulletCount = 0;    


Bullet::Bullet() {
    bulletCount = 0;  
}

void Bullet::DrawBullet(window& w, int i) {
    if (active[i]) {
        w.SetPen(c[i], 1);
        w.SetBrush(c[i]);
        w.DrawRectangle(x[i]+644, y[i], x[i]+644 + 15, y[i] - 20, FILLED);
        w.DrawEllipse(x[i]+644, y[i] - 2, x[i]+644 + 15, y[i] - 38, FILLED);
    }
}

void Bullet::MoveBullet(int i) {
    if (active[i]) {
        y[i] -= 10;  
    }
}

void Bullet::LaunchBullet(window& w, int startX, color col) {
    if (bulletCount < 100) {
        x[bulletCount] = startX;
        y[bulletCount] = 535;
        c[bulletCount] = col;
        active[bulletCount] = true;
        bulletCount++;
        DrawBullet(w, bulletCount - 1);
    }
}

void Bullet::MoveAllBullets(window& w) {
    for (int i = 0; i < bulletCount; ++i) {
        MoveBullet(i); 
        DrawBullet(w, i); 
    }
}

void Bullet::RemoveOffScreenBullets() {
    for (int i = 0; i < bulletCount; ++i) {
        if (y[i] < 0) {
            active[i] = false;
        }
    }
    int j = 0;
    for (int i = 0; i < bulletCount; ++i) {
        if (active[i]) {
            x[j] = x[i];
            y[j] = y[i];
            c[j] = c[i];
            active[j] = active[i];
            ++j;
        }
    }

    bulletCount = j;
}

