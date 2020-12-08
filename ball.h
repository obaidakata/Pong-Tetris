#pragma once
#include "Point.h"

class Ball
{
	enum { SIZE = 2 };
	Point ball_arr[SIZE];
	Point pmostright, pmostleft, pmostup, pmostdown;
	int movement;
	int state = GREEN; // GREEN = regular ball, YELLOW = becoming a bomb, RED = bomb
public:
	void newBall(int *hit);
	void setstate(int s) { state = s; }
	int getX() { return ball_arr[0].getX(); }
	void setMovement();
	int GetBallHeight();
	int getBallX();
	void setMovementWhenLeftLoses();
	void setMovementWhenRightLoses();
	void setpmostright(Point p);
	void setpmostleft(Point p);
	void setpmostdown(Point p);
	void setpmostup(Point p);
	void setedges();
	void setBall(Point & start);
	int getstate();
	void printBall();
	void ballmoveS();
	void ballmoveZ();
	Point getBombLimits()
	{
		if (movement == 1 || movement == 3)
		{
			return pmostright;
		}
		else
			return pmostleft;
	}
	void drawupright(Point p);
	void drawupleft(Point p);
	void eraseBack(Point p);
	void eraseFront(Point p);
	void eraseBall();
	void drawZ(Point p);
	void drawS(Point p);
	void moveball0();
	void moveball1();
	void moveball2();
	void moveball3();
	bool IsBallBetweenBoards(Point pl, Point pr);
	bool IfBombHitLimit();
	void BombLimitsManager();
	void deleteZ(Point p);
	void drawZdown(Point p);
	void deleteS(Point p);
	void drawSdown(Point p);
	void drawdownright(Point p);
	void checkOnlimits(Point pl, Point pr);
	void executeballmovement(Point pl, Point pr, int *hit);
	int ballHitLeftPaddle(Point p);
	int ballHitRightPaddle(Point p);
};
