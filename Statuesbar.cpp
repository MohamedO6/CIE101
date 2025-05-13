#include "Statuesbar.h"

image fuel75("images\\75 gas fuel.jpg", JPEG);
image fuel50("images\\50 gas fuel.jpg", JPEG);
image fuel25("images\\25 gas fuel.jpg", JPEG);
image fuel0("images\\0 gas fuel.jpg", JPEG);
image heart("images\\heart-green.jpg", JPEG);
image fuel100("images\\fuel full green small.jpg", JPEG);

void statuebar::drawstatuesbar(window& w, int lives, int fuel, int points, int gamespeed)
{
    int x = 0;
    int y = 0;
    w.SetPen(DARKGREEN, 2);
    w.SetBrush(DARKGREEN);
    w.DrawRectangle(0, 680 + y, 1300 + x, 740 + y, FILLED);
    w.SetPen(LIMEGREEN, 2);
    w.SetBrush(LIMEGREEN);
    w.DrawRectangle(5 + x, 685 + y, 1281 + x, 735 + y, FILLED);
    w.SetFont(25, BOLD, BY_NAME, " ");
    w.SetPen(WHITE, 15);
    w.DrawString(95 + x, 697 + y, "Game Speed:" + to_string(gamespeed));
    w.DrawString(385 + x, 697 + y, "Fuel:" + to_string(fuel) + "%");
    if (fuel > 75) { w.DrawImage(fuel100, 473 + x, 685 + y, 29, 39); }
    else if (fuel > 50) { w.DrawImage(fuel75, 475 + x, 685 + y, 50, 50); }
    else if (fuel > 25) { w.DrawImage(fuel50, 475 + x, 685 + y, 50, 50); }
    else if (fuel > 0) { w.DrawImage(fuel25, 475 + x, 685 + y, 50, 50); }
    else if (fuel == 0) {
        w.DrawImage(fuel0, 475 + x, 685 + y, 50, 50);
    }
        w.DrawString(777 + x, 697 + y, "Lives:");
        if (lives == 3) {
            w.DrawImage(heart, 840 + x, 690 + y, 40, 40);
            w.DrawImage(heart, 888 + x, 690 + y, 40, 40);
            w.DrawImage(heart, 936 + x, 690 + y, 40, 40);
        }
        else if (lives == 2) {
            w.DrawImage(heart, 840 + x, 690 + y, 40, 40);
            w.DrawImage(heart, 888 + x, 690 + y, 40, 40);
        }
        else if (lives == 1) {
            w.DrawImage(heart, 840 + x, 690 + y, 40, 40);
        }
        w.DrawString(1040 + x, 697 + y, "Points:" + to_string(points));

    }
