#include "paddle.h"

// draw the lifes.
void paddle::drawLifes()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	(paddSide == right) ? gotoxy(70, 1):gotoxy(5, 1);
	cout << "LIFES";
	int h = paddSide == right ? 80 : 0;
	for (int i = 0; i < lifeSize; i++)
	{
		gotoxy(h+(i*paddSide), 2);
		if (!Lifes[i])
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
		}
			cout << '*';
	}
}

// paddle constructor
paddle::paddle()
{
	for (int i = 0; i < Columns; i++)
	{
		grs.push_back(grave());
	}
	for (int i = 0; i < lifeSize; i++)
	{
		Lifes[i] = GREEN;
	}
}

// This function checks if the paddle is the left one or the right one and then it's sets the paddle
// according to his position.
void paddle::setPadd(int x, int y)
{
	curHead = curr = 0;
	curTail = paddSize - 1;
	paddSide = (x < Point::MAX_X / 2 ? 1 : -1);
	paddleColor = (paddSide == right) ? RED : BLUE;
	completion = (paddSide == right) ? 60 : 0;
	auto l_front = grs.begin();
	l_front++;
	int size = grs.size();
	for (int i = Point::MIN_X; i < size; i++)
	{
		for (int j = 0; j < grave::rows; j++)
		{
			l_front->ch[j]=' ';
		}
		l_front->numFull = 0;
		l_front++;
	}
	for (int i = 0; i < paddSize; i++)
	{
		body[i].set(x, y + i, paddChar);
	}
	for (int i = 0; i < lifeSize; i++)
	{
		Lifes[i] = GREEN;
	}
	currPosition = 0;
}
// This function moves the paddle on Y Axis.
void paddle::moveOnYAxis()
{
	body[curr].draw(' ');
	body[curr].moveUp();
	body[curr].draw();
}

// This function changes the paddle direction.
void paddle::paddleCHangeDir(eDir op)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), paddleColor);
	switch (op)
	{
	case UP:
		curr = curTail % paddSize;
		body[curr].changeDir(0, paddSize*-1);
		curHead = curTail;
		curTail += 2;
		moveOnYAxis();
		break;
	case DOWN:
		curr = curHead % paddSize;
		body[curr].changeDir(0, paddSize);
		curTail = curHead;
		curHead++;
		moveOnYAxis();
		break;
	}

}

// This function moves the paddle on X Axis.
void paddle::moveOnXAxis(int step)
{
	int q;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), paddleColor);
	for (int i = 0; i < paddSize; i++)
	{
		body[i].changeDir(paddSide*step, 0);
		body[i].draw(' ');
		q = body[i].getX() + body[i].getDirX();
		if (q <= Point::MAX_X && q >= Point::MIN_X)
		{
			body[i].moveRight();
		}
		body[i].draw();
	}
}

// This function checks if a recently "dead paddle" can die on the back.
bool paddle::canIDrawThere(int& col)
{
	auto l_front = grs.begin();
	advance(l_front, col);
	for (int j = 0; j < paddSize; j++)
	{
		//means if in that given col not all the 3 cells is empty so return false
		if (l_front->ch[body[j].getY() - Point::MIN_Y] != ' ')
		{
			return false;
		}
	}
	return true;
}

 //This function sends a "dead paddle" to the "grave".
void paddle::movePaddleToGrave()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), paddleColor);
	Point tmpBody[paddSize];
	for (int i = 0; i < paddSize; i++) { tmpBody[i] = body[i]; }
	int start = (body[0].getX() - paddSide) % loseRange;
	while ((start >=Point::MIN_X) && (start < loseRange)&& (canIDrawThere(start)))
	{
		for (int i = 0; i < paddSize; i++)
		{
			gotoxy(tmpBody[i].getX(), body[i].getY());
			cout << ' ';
			tmpBody[i].changeDir(paddSide*-1, 0);
			tmpBody[i].moveRight();
			tmpBody[i].draw();
		}
		Sleep(50);
		start -= paddSide;
	}
	start += paddSide;
	auto l_front = grs.begin();
	advance(l_front, start);
	for (int i = 0; i < paddSize; i++)
	{
		l_front->ch[body[i].getY() - 4] = '#';
		l_front->numFull++;
	}
	if (l_front->numFull == grave::rows)
	{
		grs.erase(l_front);
		if (paddSide == left)
			grs.push_back(grave());
		if (paddSide == right)
			grs.push_front(grave());
		lifesManager(give * 5);
		for (int i = 0; i < 5; i++)
		{
			moveOnXAxis(backward);
		}
		printGrave();
	}
}

// This function sends the mid, down and up points of the edges of the ball to the IfBombHitDeadPaddleOrLimit function.
bool paddle::thereiStranger(const Point& p)
{
	int ballX = p.getX(), ballY = p.getY();
	int ballXup, ballYup, ballXdown, ballYdown;
	if (ballX < Point::MAX_X/2)
	{
		ballXup = ballX + 1;
		ballYup = ballY - 1;
		ballXdown = ballX + 1;
		ballYdown = ballY + 1;
	}
	else
	{
		ballXup = ballX - 1;
		ballYup = ballY - 1;
		ballXdown = ballX - 1;
		ballYdown = ballY + 1;
	}
	return 
		IfBombHitDeadPaddleOrLimit(ballX,ballY)||IfBombHitDeadPaddleOrLimit(ballXup,ballYup)||IfBombHitDeadPaddleOrLimit(ballXdown,ballYdown);
		
}

// checks if the bomb hits the dead paddle o the limit and does the job.
bool paddle::IfBombHitDeadPaddleOrLimit(int ballX, int ballY)
{
	auto it = grs.begin();
	if ((ballX - body[0].getX())*paddSide < 0)
	{
		if (ballX == Point::MAX_X || ballX == Point::MIN_X)
		{
			if (paddSide == left)
				it++;
			if (paddSide == right)
				advance(it, grs.size()-1);
			if (it->numFull > 0)
			{
				grs.erase(it);
				if (paddSide == left)
					grs.push_back(grave());
				if (paddSide == right)
					grs.push_front(grave());
				lifesManager(give);
				moveOnXAxis(backward);
				return true;
			}
			return false;
		}
		advance(it, ballX % loseRange);
		if (it->ch[ballY - Point::MIN_Y] == '#')
		{
			grs.erase(it);
			if (paddSide == left)
				grs.push_back(grave());
			if (paddSide == right)
				grs.push_front(grave());
			lifesManager(give);
			moveOnXAxis(backward);
			return true;
		}
	}
	return false;
}

// This function moves all the columns one step behind if we have done a tetris.
void paddle::printGrave()
{
	auto l_front=grs.begin();
	l_front++;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), paddleColor);
	for (int i = 1; i < grs.size(); i++)
	{
		for (int j = 0; j < grave::rows; j++)
		{
			gotoxy(i+ completion, j + 4);
			cout << l_front->ch[j];
		}
		l_front++;
	}
}
// This function draws the paddles.( left and right )
void paddle::drawPadd()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), paddleColor);
	for (int i = 0; i < paddSize; i++)
	{
		body[i].draw();
	}
}

// This function upragdes the Lifes.
//if life=-1 (red) sets one * to red.
//if life=1	 (green) sets one * to green.
void paddle::lifesManager(int life)
{
	eColors color = life > 0 ? GREEN : RED;
	int absLife = abs(life);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
	int completion = paddSide == right ? 80 : 0;
	while (absLife-- > 0)
	{
		if (color==GREEN){currPosition--;}
		gotoxy(currPosition*paddSide + completion, 2);
		cout << '*';
		Lifes[currPosition] = color;
		if(color == RED){currPosition++;}
	}
}

// grave constructor.
grave::grave()
{
	for (int i = 0; i < rows; i++)
	{
		ch[i] = ' ';
	}
	numFull = 0;
}