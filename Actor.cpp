#include "Actor.h"
#include "StudentWorld.h"


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
			moveTo(getX() - 1, getY());
			break;
		case KEY_PRESS_RIGHT:
			moveTo(getX() + 1, getY());
			break;
		case KEY_PRESS_UP:
			moveTo(getX(), getY() + 1);
			break;
		case KEY_PRESS_DOWN:
			moveTo(getX(), getY() - 1);
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
	if (z or Z && frackman has at least 1 sonar)
	use sonar to illuminate within a radius of 12 around him (includes 11.99)
	decrease sonar count by 1
	setVisible() all hidden game objects within a radius of 12
	if (tab && frackman has at least 1 gold)
	add gold object to the current x,y location
	reduce gold count by 1
	////////the gold nugget will start out visible but only live for 100 ticks, it can only be picked up by protesters/////////
	*/
}
