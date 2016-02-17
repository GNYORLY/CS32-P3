#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class ppl
{
	//things that can be annoyed
	//reg protester, hardcore protester, frackman
	void getAnnoyed() 
	{ 
		//decrease health by 2 
	}
	bool dead()
	{
		//this f() is prob not here
		//if frackman's health <= 0 : set frackman object state to dead(student world should respond accordingly), play player give up sound
	}
};

class Actor : public GraphObject
{
public:
	Actor(int image, int startx, int starty, Direction facing, int health, float size = 1.0, int depth = 0) : GraphObject(image, startx, starty, facing, size = 1.0, depth = 0)
	{
		m_health = health;
	}
private:
	int m_health;
};

class Protester : public Actor
{
public:
	Protester() : Actor(0, 30, 60, right, 100)
	{}
};

class HardcoreProtester : public Protester
{
public:

};

class FrackMan : public Actor  //one of frackmans base classes must have a pointer to studentworld via getWorld()(a f() from the base class that returns the pointer)
{
public:   //can get annoyed and set dead
	FrackMan() : Actor(0, 30, 60, right, 10) //5 water, 1 sonar, 0 gold
	{
		setVisible(true);
	}
	void doSomething() 
	{
		/*
		if (frackman is not alive)
			return;
		if (frackman overlaps dirt)
			call studentworld to:
			Remove/destroy the Dirt objects from the 4x4 area occupied by the FrackMan (from x, y to x+3,y+3 inclusive)
			Make a digging sound by playing the SOUND_DIG sound (see the StudentWorld section of this document for details on how to play a sound).
		else
			check if a key was pressed:
				char ch;
				if (getWorld()->getKey(ch) == true)
				{
				// user hit a key this tick!
				switch (ch)
				{
				case KEY_PRESS_LEFT:
				... move player to the left ...;
				break;
				case KEY_PRESS_RIGHT:
				... move player to the left ...;
				break;
				case KEY_PRESS_SPACE:
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
};

class squirt //can be set dead but not annoyed
{
public: //squirt image, (x,y) location specified by frackman, travel distance of 4 squares, depth 1, size 1.0, setVisible(true)
	/*
	doSomething()
	{
		if (squirt is within a radius of 3 (up to and including 3) of one or more protesters
			annoy protesters by two points then set dead (i think annoy() already does this) so it can be removed at the end of the tick
			if (squirt traveled its full distance)
				set dead
			else //squirt has not yet traveled its full distance
				if (one square further in its current direction is occupied by a dirt or a rock)
					set dead
		else
			squirt moves one square forward in its current direction
			return;
	}
	*/
};

class oil //cannot be annoyed, can be set dead
{
public: // barrel image, (x,y) location specified, facing right, start out invisible(frackman must walk close to become visible), depth 2, size 1
	/*
	doSomething()
	{
		if (dead)
			return;
		else if (currently invisible && frackman <= a radius of 4 units away)
			setVisible(true)
			return;
		else if ( frackman is <= a radius of 3 units away)
			set dead
			play found oil sound
			increase player score by 1000
			if necessary, inform studentworld that it has been picked up //once all barrels are picked up, the player moves on to the next level
	}
	///will not block squirts(squirts pass over them)
	*/
};

class rock//can be set dead but not annoyed
{
public: //rock image, (x,y) location specified by studentworld, start out in a stable state, face down, depth 1, size 1.0, setVisible(true)
	/*doSomething()
	{
		if (dead)
			return;
		if (stable)
			check if theres any dirt in the four spaces directly below it (e.g. if rock is at (20,30), check  (20,29), (21,29), (22,29) and (23,29))
			if (there is ANY dirt there)
				do nothing
			else ///no dirt there
				rock must transition into a waiting state for the next 30 ticks
				if (rock is in a waiting state and 30 ticks passed)
					transition rock to falling state
					play falling rock sound
					if (rock is in a falling state)
						move down one square each tick until it falls to the edge, on another rock, or on dirt
						set dead
	}
	*/
};

class gold //can be set dead but not annoyed
{
public:  //gold image, location specified, facing right, may start visible or invisible(only starts visible if dropped by frackman), may be pickuppable by frackman or protesters
		 //but not both (in the field-frackman, dropped by frackman-protesters), must start as permanent or temporary, depth 2, size 1
	/*
	doSomething()
	{
		if (dead)
			return;
		else if (currently invisible && frackman <= a radius of 4 units away)
			setVisible(true)
			return;
		else if (gold can be picked up by frackman && frackman is <= a radius of 3 units away)
			set dead
			play got goodie sound
			increase player score by 10 (done by either frackman or gold class)
			tell frackman that he got a gold nugget
		else if (gold can be picked up by protesters && a protester is <= a radius of 3 units away) ////only one protester can be bribed per gold!!!
			set dead
			play protester found gold sound
			increase player score by 25 (done by either protester or gold class)
			tell protester that he got a gold nugget (for bribery)
		if (gold is in a temporary state)
			if (lifetime has elapsed)
				set dead;
	*/
};

class sonar //cannot be annoyed
{
public: // sonar image, location specified, facing right, setVisible(true), only frackman can pick up, always start in a temporary state 
	    //for T = max(100, 300 – 10*current_level_number) ticks, depth 2, size 1
	/*
	doSomething()
	{
		if (dead)
			return;
		if (lifetime has elapsed)
			set dead;
		else if ( frackman is <= a radius of 3 units away)
			set dead
			play got goodie sound
			increase player score by 75 (by frackman or sonar class)
	}
	*/
};

class water
{
public:

};

class dirt //cannot be annoyed , no mention of dead
{
public: // image, (x,y) location passed by student world during construction of the whole field, facing right, depth 3, size .25(1x1), setVisible(true) ///size 1.0 is (4x4)
	//just sits in place really / doSomething() would do nothing
	//cannot be annoyed (not part of ppl class)
};

#endif // ACTOR_H_
