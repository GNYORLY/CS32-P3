#include "Actor.h"
#include "StudentWorld.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <sstream>

void FrackMan::doSomething()
{
	if (isDead())
		return;
	getWorld()->removeDirt();
	int button;
	if (getWorld()->getKey(button) == true)
	{
		switch (button)
		{
		case KEY_PRESS_LEFT:
			if (getDirection() == left && getX() > 0)
				moveTo(getX() - 1, getY());
			else
				setDirection(left);
			break;
		case KEY_PRESS_RIGHT:
			if (getDirection() == right && getX() < 60)
				moveTo(getX() + 1, getY());
			else
				setDirection(right);
			break;
		case KEY_PRESS_UP:
			if (getDirection() == up && getY() < 60)
				moveTo(getX(), getY() + 1);
			else
				setDirection(up);
			break;
		case KEY_PRESS_DOWN:
			if (getDirection() == down && getY() > 0)
				moveTo(getX(), getY() - 1);
			else
				setDirection(down);
			break;
		case 'Z':
		case 'z':
			if (m_sonar > 0)
			{
				getWorld()->useSonar();
				m_sonar--;
			}
			break;
		case KEY_PRESS_TAB:
			if (m_gold > 0)
			{
				getWorld()->placeGold();
				m_gold--;
			}
			break;
		}
	}
	/*	case KEY_PRESS_SPACE:
	... add a Squirt in front of the player...;
		break;
	// etc…
	if (escape was pressed)
	set frackman to completely annoyed(dead)--studentworld should respond accordingly to the dead frackman(replay lvl or end game when no lives left)
	if (spacebar was pressed)
	if (there is dirt at the squirt location(4 squares in front of frackman) or if the squirt is within a radius of 3.0 of a rock)
	do not fire a squirt
	else
	fire a squirt (create a squirt object 4 squares in front of frackman)
	reduce squirt count by one
	play sound player squirt
	////////both make sound and reduce squirt count, but only one actually squirts//////
	hint:have frackman create squirt then have studentworld manage the rest
	if (direction other than current direction)
	turn frackman to that direction, but do not move
	if (same direction && frackman is able to move in that direction(no rocks in the way and not out of the game area))
	use graphObject's moveTo() to move 1 square in that direction
	////////////valid positions are from 0-60 inclusive for both x and y, frackman cannot go <= radius of 3 from center of rock////////
	
	////////the gold nugget will start out visible but only live for 100 ticks, it can only be picked up by protesters/////////
	*/
}

void activeStuff::doSomething()
{
	if (isDead())
		return;

	if (m_visible == false && getWorld()->frckRadius(getX(), getY(), 4)) //cant use isVisible()
	{
		m_visible = true;
		setVisible(true);
		return;
	}
	else if (getWorld()->frckRadius(getX(), getY(), 3))
	{
		setDead();
		getWorld()->playSound(m_sound);
		getWorld()->increaseScore(m_points);
		changeAmount();
	}
}

void oil::changeAmount()
{
	getWorld()->removeOil();
}

void gold::changeAmount()
{
	getWorld()->giveGold();
}

tempGoodie::tempGoodie(StudentWorld* sw, int image, int x, int y, int points) : activeStuff(sw, image, x, y, points)
{
	m_lifeTime = max(100, signed(300 - 10 * getWorld()->getLevel()));
}

void tempGoodie::doSomething()
{
	if (m_lifeTime <= 0)
	{
		setDead();
	}
	else
		m_lifeTime--;
	
	activeStuff::doSomething();
}

void sonar::changeAmount()
{
	getWorld()->giveSonar();
}

void water::changeAmount()
{
	getWorld()->giveWater();
}

