#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

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
	FrackMan() : Actor(0, 30, 60, right, 5)
	{}

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
