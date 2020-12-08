#pragma once
#include "paddle.h"
class pcPaddle :public paddle
{
private:
	enum eLeveles{BEST,GOOD,NOVICE};
	int paddLevel = 0;
	int ballHeight;
	int ballX;
	bool bomb = false;
public:
	void move()override;
	void setBp(int h, int x) { ballHeight = h; ballX = x; }
	void setPcPaddle(int x, int y);
	void setLevel(int level){paddLevel = level;}
	void bombMode() { bomb = true; }
};