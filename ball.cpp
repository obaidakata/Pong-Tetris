#include "Ball.h"
#include <ctime>


// I draw the whole ball from two points which are on the bottom.

//   S=  --                                                               
//      --                                                               --
//                the ball is a combine of S and Z  =>                  ----
//   Z=  --                                                              --
//        --


// This function sets the points for the ball and create it as an object, plus it draws the ball in the center.
void Ball::setBall(Point &start)
{
	int x;
	for (auto& p : ball_arr) {
		start.setDirX(1);
		p = start;
		x = start.getX();
		start.setX(++x);
	}
	printBall();
}

int Ball::getstate()
{
	return state;
}


int Ball::GetBallHeight()
{
	return ball_arr[0].getY()-1;
}


int Ball::getBallX()
{
	return ball_arr[0].getX(); 
}

// This function prints the ball
void Ball::printBall()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), state);
	ball_arr[0].draw();
	ball_arr[1].draw();
	drawupright(ball_arr[1]);
	drawS(ball_arr[0]);
}

// This function create a new ball and draw it in the middle.
void Ball::newBall(int *hit)
{
	eraseBall();
	Point p;
	state = GREEN;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), state);
	p.set(39, 12, 'o');
	setBall(p);
	setedges();
	if (*hit == 1)
		setMovementWhenLeftLoses();
	else
		setMovementWhenRightLoses();
}

// This function erases the whole ball.
void Ball::eraseBall()
{
	ball_arr[0].moveUp();
	deleteZ(ball_arr[0]);
	ball_arr[0].moveUpRight();
	deleteZ(ball_arr[0]);
	pmostdown.erase();
}

// This function, sets randomly the start direction of the ball, there are 4 directions: 0,1,2,3.
// 0 -> down-left
// 1 -> up-right
// 2 -> up-left
//3 -> down-right
void Ball::setMovement()
{
	/*srand((unsigned int)time(NULL));
	movement = rand() % 4;*/
	movement = 0;
}

// if the left player loses, this function sets the direction 1 or 3, cause if a player lost I send the ball
// to the other side. to make it fair.
void Ball::setMovementWhenLeftLoses()
{
	srand((unsigned int)time(NULL));
	movement = (rand() % 2) + 1;
	if (movement == 2)
		movement++;
}


// if the right player loses, this function sets the direction 0 or 2, cause if a player lost I send the ball
// to the other side. to make it fair.
void Ball::setMovementWhenRightLoses()
{
	srand((unsigned int)time(NULL));
	movement = (rand() % 2);
	if (movement == 1)
		movement++;
}


// sets the pmostup data member to the most up right point on the ball.
void Ball::setpmostup(Point p)
{
	p.moveUp();
	p.moveUp();
	pmostup = p;
}


// sets the pmostright data member to the most right point on the ball.
void Ball::setpmostright(Point p)
{
	p.moveUpRight();
	pmostright = p;
}


// sets the pmostleft data member to the most left point on the ball.
void Ball::setpmostleft(Point p)
{
	p.moveUpLeft();
	p.moveLeft();
	pmostleft = p;
}

// sets the pmostdown data member to the most down left point on the ball. (which is ball_arr[0]).
void Ball::setpmostdown(Point p)
{
	pmostdown = p;
}

// This function sets the edges all together.
void Ball::setedges()
{
	setpmostup(ball_arr[1]);
	setpmostright(ball_arr[1]);
	setpmostleft(ball_arr[1]);
	setpmostdown(ball_arr[1]);
}

// This function draws up-right the given point.
void Ball::drawupright(Point p)
{
	p.moveUp();
	p.draw();
	p.moveRight();
	p.draw();
}

// This function draws an S ( as in tetris ) above the given point.
void Ball::drawS(Point p)
{
	p.moveUp();
	p.draw();
	drawupright(p);
	p.moveLeft();
	p.draw();
}

// This function draws up-left the given point.
void Ball::drawupleft(Point p)
{
	p.moveUp();
	p.draw();
	p.moveLeft();
	p.draw();

}

// This function draws an Z ( as in tetris ) above the given point.
void Ball::drawZ(Point p)
{
	p.moveUp();
	p.draw();
	drawupleft(p);
	p.moveRight();
	p.draw();
}

// This function moves the ball up-right like adding an S's ( S in tetris ).
// First, the function deletes the 4 points that in the bottom-left.
// Second, the function adds S on the top right side to the remain points.
void Ball::ballmoveS()
{
	ball_arr[0].erase();
	ball_arr[1].erase();
	ball_arr[0].moveUpLeft();
	ball_arr[1].moveUpLeft();
	eraseFront(ball_arr[1]);
	drawS(ball_arr[0]);
}


// This function moves the ball up - left like adding an Z's ( Z in tetris ).
// First, the function deletes the 4 points that in the bottom-right.
// Second, the function adds Z on the top left side to the remain points.
void Ball::ballmoveZ()
{
	ball_arr[0].erase();
	ball_arr[1].erase();
	ball_arr[0].moveUpRight();
	ball_arr[1].moveUpRight();
	eraseBack(ball_arr[0]);
	drawZ(ball_arr[1]);
	setedges();
}

// This function erases 2 points back (left) of the given point.
void Ball::eraseBack(Point p)
{
	p.moveLeft();
	p.erase();
	pmostleft.erase();
}

// This function erases 2 points ahead (right) of the given point. 
void Ball::eraseFront(Point p)
{
	p.moveRight();
	p.erase();
	pmostright.erase();
}


// This function deletes a Z ( as in tetris ) left-down of the given point.
void Ball::deleteZ(Point p)
{
	p.erase();
	p.moveLeft();
	p.erase();
	p.moveDown();
	p.moveRight();
	p.erase();
	pmostright.erase();
}

// This function deletes a S ( as in tetris ) left-down of the given point.
void Ball::deleteS(Point p)
{
	p.erase();
	p.moveLeft();
	p.erase();
	pmostleft.erase();
	p.moveDown();
	p.erase();
}

// This function draws an 'o' down-right of the given point.
void Ball::drawdownright(Point p)
{
	p.moveDown();
	ball_arr[0] = p;
	p.draw();
	p.moveRight();
	ball_arr[1] = p;
	p.draw();
}

// This function draws a S of points ( S as in tetris ) below the given point.
void Ball::drawSdown(Point p)
{
	p.moveRight();
	p.draw();
	p.moveRight();
	p.draw();
	p.moveDownLeft();
	ball_arr[1] = p;
	p.draw();
	p.moveLeft();
	ball_arr[0] = p;
	p.draw();
}

// This function draws a Z of points ( Z as in tetris ) below the given point.
void Ball::drawZdown(Point p)
{
	p.moveLeft();
	p.draw();
	drawdownright(p);
	p.moveLeft();
	p.draw();
}


// This function controls the whole movement of the ball.
// pl = the top point of the left paddle.
// pr = the top point of the right paddle.
// hit= byref int that holds a value according to which paddle does the ball hit or if the ball hit the wall.
void Ball::executeballmovement(Point pl, Point pr, int *hit)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), state);
	if (!(state == RED))
		checkOnlimits(pl, pr);
	else BombLimitsManager();
	switch (movement)
	{
	case 0:moveball0();
		break;
	case 1:moveball1();
		break;
	case 2:moveball2();
		break;
	case 3:moveball3();
		break;
	}

	*hit = ballHitLeftPaddle(pl);
	if (*hit == 2)
		*hit = ballHitRightPaddle(pr);

	if ((state == YELLOW) && (*hit == 0 || *hit == 3)) // if the a "becoming a bomb" hit the left or right puddle.
	{
		state = GREEN;
	}

	if ((state == YELLOW) && (*hit == 1 || *hit == 4)) // if the "becoming a bomb" pass the puddle without hitting.
	{
		state = GREEN;
		*hit = 5;
	}
	Sleep(70);
}


// This function moves the ball on 0 ( movement 0 explained on the top of the file).
void Ball::moveball0()
{
	deleteZ(pmostup);
	drawZdown(ball_arr[0]);
	setedges();
}

// This function moves the ball on 1 ( movement 1 explained on the top of the file).
void Ball::moveball1()
{
	ballmoveZ();
	setedges();
}

// This function moves the ball on 2 ( movement 2 explained on the top of the file).
void Ball::moveball2()
{
	ballmoveS();
	setedges();
}

// This function moves the ball on 3 ( movement 3 explained on the top of the file).
void Ball::moveball3()
{
	deleteS(pmostup);
	drawSdown(ball_arr[1]);
	setedges();
}

// This function checks if the ball is between the paddles/boards.
bool Ball::IsBallBetweenBoards(Point pl, Point pr)
{
	if (pmostright.getX() <= pr.getX() && pmostleft.getX() >= pl.getX())
		return true;
	else return false;
}

// This function checks if the bomb hits the game limits.
bool Ball::IfBombHitLimit()
{
	if ((pmostright.getX() == Point::MAX_X) || (pmostleft.getX() == Point::MIN_X))
		return true;
	else return false;
}

// This function manages the bomb limits, just cares for the Y axis since bomb can across the paddles.
void Ball::BombLimitsManager()
{
	if (movement == 0)
	{
		if (pmostleft.isOn_Y_Edge() || (pmostdown.getY() + 1) > 24)
		{
			movement = 2;
		}
	}

	if (movement == 1)
	{
		if (pmostup.isOn_Y_Edge() || (pmostup.getY() - 1) < 4)
		{
			movement = 3;

		}
	}

	if (movement == 2)
	{
		if (pmostup.isOn_Y_Edge() || (pmostup.getY() - 1) < 4)
		{
			movement = 0;
		}
	}

	if (movement == 3)
	{
		if (pmostdown.isOn_Y_Edge() || (pmostdown.getY() + 1) > 24)
		{
			movement = 1;
		}
	}
}

// This function checks if the ball has reached the limits of the game and changes the direction.
void Ball::checkOnlimits(Point pl, Point pr)
{
	if (movement == 0)
	{
		if (pmostdown.isOn_X_Edge(pl))
		{
			movement = 3;
		}

		if (pmostleft.isOn_Y_Edge() || (pmostdown.getY() + 1) > 24)
		{
			movement = 2;
		}
	}


	if (movement == 1)
	{

		if (pmostright.isOn_X_Edge(pr))
		{
			movement = 2;
		}
		if (pmostup.isOn_Y_Edge() || (pmostup.getY() - 1) < 4)
		{
			movement = 3;

		}
	}

	if (movement == 2)
	{
		if (pmostleft.isOn_X_Edge(pl))
		{
			movement = 1;
		}
		if (pmostup.isOn_Y_Edge() || (pmostup.getY() - 1) < 4)
		{
			movement = 0;
		}
	}

	if (movement == 3)
	{
		if (pmostright.isOn_X_Edge(pr))
		{
			movement = 0;
		}

		if (pmostdown.isOn_Y_Edge() || (pmostdown.getY() + 1) > 24)
		{
			movement = 1;
		}
	}
}


// This function checks if the ball did hit the left paddle and return a value according to it.
// if 0 the ball did hit the left paddle.
// if 1 the ball passed the left paddle and didn't hit it.
// if 2 the ball didn't hit and didn't pass the paddle.
int Ball::ballHitLeftPaddle(Point p)
{
	Point paddlemid = p;
	int y = p.getY();
	paddlemid.setY(++y);

	Point paddledown = p;
	y = paddlemid.getY();
	paddledown.setY(++y);

	if (p == pmostleft) // there is 2 options: 0 or 2 and both send to 1.
	{


		movement = 1;
		pmostleft.draw('#');
		pmostleft.setCH('#');
		Sleep(70);
		return 0;
	}

	if (pmostleft == paddlemid)
	{
		pmostleft.draw('#');
		pmostleft.setCH('#');

		if (movement == 0)
			movement = 3;
		else movement = 1;

		Sleep(70);
		return 0;
	}

	if (pmostleft == paddledown)// there is 2 options: 0 or 2 and both send to 3.
	{
		movement = 3;
		pmostleft.draw('#');
		pmostleft.setCH('#');
		Sleep(70);
		return 0;
	}

	if (state == RED)// care for the edges while bomb.
	{
		Point pUpleft = pmostup;
		int pUpleftX = pmostup.getX();
		pUpleft.setX(--pUpleftX);
		if (pUpleft == paddledown)
			return 0;
		if (ball_arr[0] == p)
			return 0;
	}

	if (pmostleft.getX() == p.getX() && pmostleft.getY() != p.getY())
	{
		if ((pmostleft.getY() - p.getY()) == -1)
		{
			if (pmostup.getY() == 4)
			{
				movement = 3;
				pmostup.erase();
				pmostup.moveLeft();
				pmostup.erase();
				pmostleft.erase();
				pmostleft.moveRight();
				pmostleft.erase();
				Sleep(100);
				return 0;
			}
			else
			{
				movement = 1;
				pmostup.erase();
				pmostup.moveLeft();
				pmostup.erase();
				pmostright.erase();
				Sleep(100);
				return 0;

			}
		}

		if ((pmostleft.getY() - paddledown.getY()) == 1)
		{
			movement = 3;
			ball_arr[0].erase();
			pmostright.erase();
			ball_arr[1].erase();
			Sleep(100);
			return 0;
		}

		if (state != RED)
		{
			if (movement == 0)
			{
				movement = 3;
			}
			else
			{
				movement = 1;
			}
		}
		return 1;
	}
	return 2;
}


// This function checks if the ball did hit the right paddle and return a value according to it.
// if 3 the ball did hit the right paddle.
// if 4 the ball passed the right paddle and didn't hit it.
// if 2 the ball didn't hit and didn't pass the paddle.
int Ball::ballHitRightPaddle(Point p)
{
	Point paddlemid = p;
	int y = p.getY();
	paddlemid.setY(++y);

	Point paddledown = p;
	y = paddlemid.getY();
	paddledown.setY(++y);

	if (p == pmostright) // there is 2 options: 1 or 3 and both send to 2.
	{
		movement = 2;
		pmostright.draw('#');
		pmostright.setCH('#');
		Sleep(70);
		return 3;
	}

	if (pmostright == paddlemid)
	{
		pmostright.draw('#');
		pmostright.setCH('#');

		if (movement == 1)
			movement = 2;
		else movement = 0;

		Sleep(70);
		return 3;
	}

	if (pmostright == paddledown)// there is 2 options: 0 or 2 and both send to 0.
	{
		movement = 0;
		pmostright.draw('#');
		pmostright.setCH('#');
		Sleep(70);
		return 3;
	}

	if (state == RED)     // care for the edges while bomb.
	{
		if (pmostup == paddledown)
			return 3;
		if (ball_arr[1] == p)
			return 3;
	}

	if (pmostright.getX() == p.getX() && (pmostright.getY() != p.getY()))
	{

		if (pmostright.getY() - p.getY() == -1)
		{
			movement = 2;
			pmostup.erase();
			pmostleft.erase();
			pmostleft.moveUpRight();
			pmostleft.erase();
			return 3;
		}

		if (pmostright.getY() - paddledown.getY() == 1)
		{
			movement = 0;
			ball_arr[0].erase();
			ball_arr[1].erase();
			pmostleft.erase();
			return 3;
		}

		if (state != RED)
		{
			if (movement == 3)
			{
				movement = 0;
			}
			else
			{
				movement = 2;
			}
		}
		return 4;
	}

	return 2;
}

