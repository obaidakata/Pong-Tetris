#include "game.h"

// This function checks which player has lost and types on the screen the player who lost.
bool gameObj::checkLose()
{
	if (playerPaddle[0]->getHeadX() == 20)
	{
		myCls();
		gotoxy(Point::MAX_X / 2, Point::MAX_Y / 2);
		cout << "THE RIGHT PADDLE WON!!!";
		Sleep(1000);
		thereIsALoser = true;
		return true;
	}
	else if (playerPaddle[1]->getHeadX() == 60)
	{
		myCls();
		gotoxy(Point::MAX_X / 2, Point::MAX_Y / 2);
		cout << "THE LEFT PADDLE WON!!!";
		Sleep(1000);
		thereIsALoser = true;
		return true;
	}
	return false;
}

// This function checks if the key "ESC" has been pressed.
// Returns true if the "ESC" has been pressed, else returns false.
bool gameObj::checkESC()
{
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		paused = true;
		return true;
	}
	return false;
}

//This function prints the frame of the game menu.
void gameObj::printMenuFrame()
{
	// both chars presents an Ascii value of Rectangle.
	char ch = (char)219;
	char ch2 = (char)223;
	//---------------------------------------------------
	gotoxy((Point::MAX_X / 4) - 1, (Point::MAX_Y / 2));

	for (int i = 0; i < 45; i++)
		cout << ch2;
	for (int i = 0; i < 8 + paused; i++)
	{
		gotoxy((Point::MAX_X / 4) - 1, (Point::MAX_Y / 2) + i);
		cout << ch;
	}
	for (int i = 0; i < 8 + paused; i++)
	{
		gotoxy((Point::MAX_X / 4) + 44, (Point::MAX_Y / 2) + i);
		cout << ch;
	}
	gotoxy((Point::MAX_X / 4) - 1, (Point::MAX_Y / 2) + 8 + paused);
	for (int i = 0; i < 46; i++)
		cout << ch2;
}

// This function prints the options of the Menu and get input from the user.
// plus it's hides the console cursor.
void gameObj::showMenu()
{
	hideConsoleCursor();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	int l = 1;
	int op = 0;
	printMenuFrame();
	gotoxy((Point::MAX_X / 4) - 5, 10);
	cout << "welcome to the pongTetris 2.0 game by ahmad & obaida";
	gotoxy(Point::MAX_X / 4, (Point::MAX_Y / 2) + (l++));
	cout << "(1) Start a new game - Human vs Human";
	gotoxy(Point::MAX_X / 4, (Point::MAX_Y / 2) + (l++));
	cout << "(2) Start a new game - Human vs Computer";
	gotoxy(Point::MAX_X / 4, (Point::MAX_Y / 2) + (l++));
	cout << "(3) Start a new game - Computer vs Computer";
	if (paused)
	{
		gotoxy(Point::MAX_X / 4, (Point::MAX_Y / 2) + (l++));
		cout << "(4) Continue a paused game";
	}
	gotoxy(Point::MAX_X / 4, (Point::MAX_Y / 2) + (l++));
	cout << "(8) Present instructions and keys";
	gotoxy(Point::MAX_X / 4, (Point::MAX_Y / 2) + (l++));
	cout << "(9) EXIT";
	gotoxy(Point::MAX_X / 4, (Point::MAX_Y / 2) + (l++) + 1);
	cout << "Enter your option please: ";
	cin >> op;
	myCls();
	switch (op)
	{
	case 1:
		setObjects();
		playerPaddle[0] = userPaddle;
		playerPaddle[1] = userPaddle + 1;
		startGame();
		break;
	case 2:
		levlesMenu(1);
		myCls();
		setObjects();
		playerPaddle[0] = userPaddle;
		playerPaddle[1] = pcPaddle + 1;
		startGame();
		break;
	case 3:
		levlesMenu(0);
		myCls();
		levlesMenu(1);
		myCls();
		setObjects();
		playerPaddle[0] = pcPaddle;
		playerPaddle[1] = pcPaddle + 1;
		startGame();
		break;
	case 4:
		if (paused)
			continuePause();
		break;
	case 8:
		instructions();
		break;
	case 9:
		exit();
		break;
	}
}

// This function prints the menu for the levels, (a) best , (b) good, (c) noivce
void gameObj::levlesMenu(int side)
{
	int l = 1;
	char op = 0;
	printMenuFrame();
	gotoxy(Point::MAX_X / 4, (Point::MAX_Y / 2) + (l++));
	cout << "(a) BEST";
	gotoxy(Point::MAX_X / 4, (Point::MAX_Y / 2) + (l++));
	cout << "(b) GOOD ";
	gotoxy(Point::MAX_X / 4, (Point::MAX_Y / 2) + (l++));
	cout << "(c) NOVICE";
	gotoxy(Point::MAX_X / 4, (Point::MAX_Y / 2) + (l++) + 1);
	cout << "Enter your option please: ";
	cin >> op;
	switch (op)
	{
	case'a':
	case'A':
		pcPaddle[side].setLevel(0);
		break;
	case'b':
	case'B':
		pcPaddle[side].setLevel(1);
		break;
	case'c':
	case'C':
		pcPaddle[side].setLevel(2);
		break;
	}
}
// This function sets the objects with their vlues.
// sets the ball, paddles and the keyboard keys.

void gameObj::setObjects()
{
	Point p;
	p.set(60, 6, 'o');
	ball.setBall(p);
	ball.printBall();
	userPaddle[0].setUserPaddle("qas", 4, 10);
	userPaddle[1].setUserPaddle("plk", 76, 11);
	pcPaddle[0].setPcPaddle(4, 10);
	pcPaddle[1].setPcPaddle(76, 11);
	if (!paused && !thereIsALoser)
	{
		for (int i = 0; i < numBoard; i++)
		{
			kbManager.registerKbListener(&userPaddle[i]);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), userPaddle[i].getColor());
			userPaddle[i].drawPadd();
		}
	}
	paused = false;
}

// This function runs the game and runs the functions. ( Controls everything ).
// prints the game frame.
void gameObj::startGame()
{
	int counter = 0;
	printGameFrame();
	playerPaddle[0]->drawLifes();
	playerPaddle[1]->drawLifes();
	Point phl, phr;
	int hit, ballHeight = 0,ballX=0;
	ball.setMovement();
	ball.setedges();
	while (!checkESC() && !checkLose())
	{
		phl = playerPaddle[0]->getPaddHead();
		phr = playerPaddle[1]->getPaddHead();
		ball.executeballmovement(phl, phr, &hit);
		ballHit(hit, phl, phr);
		ballHeight = ball.GetBallHeight();
		ballX = ball.getBallX();
		pcPaddle[0].setBp(ballHeight, ballX);
		pcPaddle[1].setBp(ballHeight, ballX);
		kbManager.handleKeyboard();
		playerPaddle[0]->move();
		playerPaddle[1]->move();
		playerPaddle[0]->drawPadd();
		playerPaddle[1]->drawPadd();
	
	}
	myCls();
	showMenu();
}


// This function checks what heppens when the ball hits the paddle, in all the states of the ball.
// Bomb, regular and becoming a bomb.
void gameObj::ballHit(int hit, const Point& phl, const Point& phr)
{
	Point bombCoord = ball.getBombLimits();
	if (ball.getstate() == RED)
	{
		if (bombCoord.getX() > (Point::MAX_X) / 2)
		{
			pcPaddle[1].bombMode();
			if (playerPaddle[1]->thereiStranger(bombCoord))
			{
				ball.newBall(&hit);
				playerPaddle[1]->printGrave();
				bombcount = 0;
			}
		}
		else
		{
			pcPaddle[0].bombMode();
			if (playerPaddle[0]->thereiStranger(bombCoord))
			{
				ball.newBall(&hit);
				playerPaddle[0]->printGrave();
				bombcount = 0;
			}
		}
	}
	
	if ((hit == 1) && (ball.getstate() != RED)) // if the ball hits the left paddle and is not a bomb.
	{
		playerPaddle[0]->lifesManager(paddle::TAKE);
		printGameFrame(playerPaddle[1]->getColor());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), playerPaddle[0]->getColor());
		playerPaddle[0]->movePaddleToGrave();
		playerPaddle[0]->moveOnXAxis(paddle::FORWARD);
		ball.newBall(&hit);
	}

	if ((hit == 4) && (ball.getstate() != RED))// if the ball hits the right paddle and is not a bomb.
	{
		playerPaddle[1]->lifesManager(paddle::TAKE);
		printGameFrame(playerPaddle[0]->getColor());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), playerPaddle[1]->getColor());
		playerPaddle[1]->movePaddleToGrave();
		playerPaddle[1]->moveOnXAxis(paddle::FORWARD);
		ball.newBall(&hit);
	}

	if (hit == 0 && (ball.getstate() == RED)) // if the ball hits the left paddle while in bomb state.
	{
		printGameFrame(playerPaddle[1]->getColor());
		playerPaddle[0]->lifesManager(paddle::TAKE * 3);
		playerPaddle[0]->movePaddleToGrave();
		playerPaddle[0]->moveOnXAxis(paddle::FORWARD * 3);
		ball.newBall(&hit);
	}

	if (hit == 3 && (ball.getstate() == RED))// if the ball hits the right paddle while in bomb state.
	{
		printGameFrame(playerPaddle[0]->getColor());
		playerPaddle[1]->lifesManager(paddle::TAKE * 3);
		playerPaddle[1]->movePaddleToGrave();
		playerPaddle[1]->moveOnXAxis(paddle::FORWARD * 3);
		ball.newBall(&hit);
	}

	if (ball.IfBombHitLimit()) // if the bomb hits the limits of the game it returns 
	{
		ball.newBall(&hit);
	}

	if (ball.getstate() == RED)// counts the iteration for the bomb before transform back to a regular ball.
	{
		bombcount++;
		if ((bombcount == 4) && (ball.IsBallBetweenBoards(phl, phr)))
		{
			ball.setstate(GREEN);
			ball.printBall();
			bombcount = 0;
		}
	}

	if (ball.getstate() == YELLOW)// counts the iteration for "the becoming a bomb" before transform to a bomb.
	{
		becomingAbombCount++;
		if (becomingAbombCount == 10)
		{
			ball.setstate(RED);
			ball.printBall();
			becomingAbombCount = 0;
		}
	}

	if ((ball.getstate() != YELLOW) && (ball.getX() == 40) && (leftagreedtobecomeabomb == true))
		Leftmidcount++;

	if (Leftmidcount == 4)
	{
		Leftmidcount = 0;
		if (leftagreedtobecomeabomb)
			leftagreedtobecomeabomb = false;
	}

	if ((ball.getstate() != YELLOW) && (ball.getX() == 40) && (rightagreedtobecomeabomb == true))
		Rightmidcount++;

	if (Rightmidcount == 4)
	{
		Rightmidcount = 0;
		if (rightagreedtobecomeabomb)
			rightagreedtobecomeabomb = false;
	}

	if ((playerPaddle[0]->IsSorKPressed()) && (!leftagreedtobecomeabomb) && (ball.getstate() == GREEN)) // if S pressed
	{
		ball.setstate(YELLOW);
		leftagreedtobecomeabomb = true;
		ball.printBall();
	}

	if ((playerPaddle[1]->IsSorKPressed()) && (!rightagreedtobecomeabomb) && (ball.getstate() == GREEN)) // if K pressed
	{
		ball.setstate(YELLOW);
		rightagreedtobecomeabomb = true;
		ball.printBall();
	}
}
// This function continues the paused game, In other words this function draws the previous paused game.
void gameObj::continuePause()
{
	playerPaddle[0]->drawLifes();
	playerPaddle[0]->printGrave();
	playerPaddle[0]->drawPadd();
	playerPaddle[1]->drawLifes();
	playerPaddle[1]->printGrave();
	playerPaddle[1]->drawPadd();
	ball.printBall();
	startGame();
}

// prints the instructions when you choose option (8)
void gameObj::instructions()
{
	printMenuFrame();
	int l = 1;
	gotoxy(Point::MAX_X / 4, (Point::MAX_Y / 2) + (l++));
	cout << "q or Q => Moves the left paddle UP";
	gotoxy(Point::MAX_X / 4, (Point::MAX_Y / 2) + (l++));
	cout << "a or A => Moves the left paddle DOWN";
	gotoxy(Point::MAX_X / 4, (Point::MAX_Y / 2) + (l++));
	cout << "p or P => Moves the right paddle UP";
	gotoxy(Point::MAX_X / 4, (Point::MAX_Y / 2) + (l++));
	cout << "l or L => Moves the right paddle DOWN";
	gotoxy(Point::MAX_X / 4, (Point::MAX_Y / 2) + (l++));
	cout << "ECS    => To pause the game";
	Sleep(10000);
	myCls();
	showMenu();
}

// This function exits the game and prints bye bye.
void gameObj::exit()
{
	gotoxy(Point::MAX_X / 2, Point::MAX_Y / 2);
	cout << "Bye Bye" << endl;
	Sleep(1200);
}

// This functions clears the console in a nice way :D.
void gameObj::myCls()
{
	for (int j = Point::MAX_X / 2 + 1; j >= 0; j--)
	{
		for (int i = 0; i <= 25; i++)
		{
			gotoxy(j, i);
			cout << ' ';
			gotoxy(80 - j + 1, i);
			cout << ' ';
		}
		Sleep(10);
	}
	gotoxy(0, 0);
}

// This function prints the game frame.
void gameObj::printGameFrame(eColors color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	for (int i = 3; i <= Point::MAX_Y + 1; i++)
	{
		gotoxy(0, i);
		cout << (char)(219);
	}
	for (int i = 3; i <= Point::MAX_Y + 1; i++)
	{
		gotoxy(Point::MAX_X + 1, i);
		cout << (char)(219);
	}
	for (int i = 0; i <= Point::MAX_X + 1; i++)
	{
		gotoxy(i, 3);
		cout << (char)(220);
	}
	for (int i = 0; i <= Point::MAX_X + 1; i++)
	{
		gotoxy(i, Point::MAX_Y + 1);
		cout << (char)(223);
	}
}
