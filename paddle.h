#pragma once
#include "point.h"
#include <list>
const char paddChar = '#';
struct grave
{
	enum { rows = Point::MAX_Y - Point::MIN_Y + 1 };//grave size
	char ch[rows];
	int numFull = 0;
	grave();
};
class paddle
{
protected:
	enum { paddSize = 3, lifeSize=16 };//size and more
private:
	enum { left = 1 , right = -1 };//side options
	enum { Columns = 20 , lifes =16};//grave size
	enum { loseRange = 20 };//loos Constants
	sInt paddSide;
	Point body[paddSize];
	sInt curHead = 0, curTail = paddSize - 1, curr = 0;
	list<grave> grs;
	sInt completion = 0;
	eColors paddleColor;
	bool canIDrawThere(int& col);
	void moveOnYAxis();
	eColors Lifes[lifeSize];
	int currPosition = 0;
protected:
	enum eDir { UP = 0, DOWN = 1, KEY = 2 };//direction options
	void paddleCHangeDir(eDir op);
	bool keyBomb = false;
	bool checkYLim(int y)
	{
		y += body[curr].getY();
		return (y <= Point::MAX_Y + 2) && (y >= Point::MIN_Y - 2);
	}
public:
	enum { give = 1, TAKE = -1 };//misses options
	enum {FORWARD=1,backward=-1};//move options
	bool IsSorKPressed() {return keyBomb;}
	paddle();
	void drawLifes();
	void setPadd(int x, int y);
	void drawPadd();
	void lifesManager(int life);
	eColors getColor() { return paddleColor; }
	virtual void move() = 0;
	int getHeadY() { return body[0].getY(); }
	int getHeadX() { return body[0].getX(); }
	Point getPaddHead() { return body[curHead % 3]; }
	void moveOnXAxis(int dir);
	void movePaddleToGrave();
	bool thereiStranger(const Point& p);
	bool IfBombHitDeadPaddleOrLimit(int ballX, int ballY);
	void printGrave();
};
