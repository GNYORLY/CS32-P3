#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class ppl
{
	//things that can be annoyed(people)/ things with health
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

class FrackMan : public Actor
{
public:
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

class thing : public Actor
{
public:

};

class squirt
{
public:

};

class oil
{
public:

};

class rock
{
public:

};

class gold 
{
public:

};

class sonar
{
public:

};

class water
{
public:

};

class dirt
{
public:

};

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
