#include"pcPaddle.h"

// This function manage the pc paddle movement, it's a virtual function.
void pcPaddle::move()
{
	keyBomb = false;
	int probability = 0,delay=0;
	switch (paddLevel)
	{
		case BEST:
			break;
		case GOOD:
			probability = 40;
			break;
		case NOVICE:
			probability = 10;
			break;
	}
	if (rand() % 50==49)
	{
		keyBomb = true;
	}
	if (probability != 0 && rand()%probability == probability - 1)
	{
		delay = 1;
	}
	if (probability == 0 && bomb && abs(ballX - getHeadX()) < 2)
	{
		delay = 1;
	}
	if (ballHeight + delay < getHeadY() && checkYLim(paddSize*-1))
	{
		paddleCHangeDir(UP);
	}
	if (ballHeight - delay > getHeadY() && checkYLim(paddSize))
	{
		paddleCHangeDir(DOWN);
	}
	if (ballX == getHeadX())
	{
		bomb = false;
	}
}

void pcPaddle::setPcPaddle(int x, int y)
{
	setPadd(x, y);
}
