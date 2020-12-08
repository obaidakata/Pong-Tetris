#pragma once
#include "KeyboardManager.h"
#include"userPaddle.h"
#include "pcPaddle.h"
#include "Ball.h"
class gameObj
{
private:
	enum { numBoard = 2 };
	KeyboardManager kbManager;
	userPaddle userPaddle[numBoard];
	pcPaddle pcPaddle[numBoard];
	paddle* playerPaddle[numBoard];
	Ball ball;
	int becomingAbombCount = 0, bombcount = 0, Leftmidcount = 0, Rightmidcount = 0;
	bool leftagreedtobecomeabomb = false;
	bool rightagreedtobecomeabomb = false;
	bool IfBombHitlimits = false;
	bool paused = false;
	bool thereIsALoser = false;
	void setObjects();
	void startGame();
	void ballHit(int hit, const Point& phl, const Point& phr);
	void continuePause();
	void instructions();
	void exit();
	void myCls();
	bool checkLose();
	bool checkESC();
	void printMenuFrame();
	void printGameFrame(eColors color = WHITE);
public:
	void showMenu();
	void levlesMenu(int side);
};