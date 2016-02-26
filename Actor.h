#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

class Actor : public GraphObject
{
public:
	Actor(StudentWorld* sw, int image, int startx, int starty, Direction facing, float size, int depth) : GraphObject(image, startx, starty, facing, size, depth)
	{
		setVisible(true);
		m_sw = sw;
	}

	~Actor() {}

	virtual void doSomething() 
	{}
	
	void setDead() { m_dead = true; }

	//accessors
	bool isDead() const { return m_dead; }

	StudentWorld* getWorld() const { return m_sw; }

private:
	bool m_dead = false;
	StudentWorld* m_sw;
};

class ppl : public Actor
{
public:
	ppl(StudentWorld* sw, int image, int x, int y, Direction dir, int health) : Actor(sw, image, x, y, dir, 1.0, 0)
	{
		setVisible(true);
		m_health = health;
	}
	virtual void getAnnoyed()  //eh
	{ 
		m_health -= 2;
		if (m_health <= 0)
			setDead();
	}
	int health() const
	{
		return m_health;
	}
	void itemGet()
	{}
private:
	int m_health;
};

class FrackMan : public ppl  
{
public:		
	FrackMan(StudentWorld* sw) : ppl(sw, IID_PLAYER, 30, 60, right, 10)
	{ setVisible(true); }

	~FrackMan() {}

	//mutators
	void doSomething();

	void addWater() { m_water += 5; }
	void addGold() { m_gold++; }
	void addSonar() { m_sonar += 2; }

	//accessors
	unsigned int water() const { return m_water; }
	unsigned int gold() const { return m_gold; }
	unsigned int sonar() const { return m_sonar; }
	
private:
	int m_water = 5;
	int m_gold = 0;
	int m_sonar = 1;
};

class dirt : public Actor 
{
public: 
	dirt(StudentWorld* sw, int x, int y) : Actor(sw, IID_DIRT, x, y, right, .25, 3)
	{ setVisible(true); }
	
	~dirt()
	{ setVisible(false); }
};

//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////UNDER CONSTRUCTION/////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

class stuff : public Actor
{
public:
	stuff(StudentWorld* sw, int image, int x, int y, Direction dir = right, float size = 1.0, int depth = 2) : Actor(sw, image, x, y, dir, size, depth)
	{}

};

class activeStuff : public stuff
{
public:
	activeStuff(StudentWorld* sw, int image, int x, int y, int points, int sound = SOUND_GOT_GOODIE, bool visible = true) : stuff(sw, image, x, y, right, 1.0, 2)
	{
		setVisible(visible);
		m_sound = sound;
		m_points = points;
		m_visible = visible;
	}

	virtual void doSomething();

private:
	int m_sound;
	int m_points;
	bool m_visible;
	virtual void changeAmount() = 0;
};

class Protester : public Actor //can be annoyed, set dead, and pick up gold
{
public: //protestor image, face left, decide how many squares numSquaresToMoveInCurrentDirection. it will decide to move left before possibly switching its direction.
	    //This value must be : 8 <= numSquaresToMoveInCurrentDirection <= 60, 5 health, not in a leave-oil-field state, depth 0, size 1, setVisible(true)
	//int ticksToWaitBetweenMoves = max(0, 3 – current_level_number / 4) ////every "tick" for a protester is several actual ticks according to this formula
	/*
		doSomething()
		{
			if (dead)
				return;
			if (in a rest state)
				update resting tick count
				return;
			else if (in a leave-the-field state) 
				if (reg protester is at (60,60))
					set dead
				else
					move one square closer to the exit (60,60) using a queue based maze algorithm (cannot move through dirt and rocks(within 3 units))
					////hint: find a way to make a single data structure that can find the optimal path no matter where the protester is
					return;
			else if (within 4 units of frackman && facing frackmans direction && protester hasn't shouted within its last non-resting 15 ticks)
				play protester yell sound
				tell frackman that he was annoyed (-2 health)
				update some variable that prevents protester from shouting again for 15 non-resting ticks
				return;
			else if (there is a straight line toward frackman && frackman is > 4 units away && there is no dirt or rocks blocking the straight path)
				change direction toward frackman 
				take one step in that direction
				set numSquaresToMoveInCurrentDirection value to zero
				return;
			else if (numSquaresToMoveInCurrentDirection <= 0)
				pick a random direction to move
				if (space in front of that direction is blocked by dirt or rocks)
					select a different direction and check again until one works
				change into this direction
				pick a new value for numSquaresToMoveInCurrentDirection (8 <= numSquaresToMoveInCurrentDirection <= 60) to move over the same number of ticks
				continue with step 8****
			else if (at an intersection where it can turn 90deg and move at least one square without being blocked by dirt or rocks && hasn't turned 90deg in the last 200 non-resting ticks)
				determine which two perpendicular directions are viable(not blocked)
				pick a viable direction (if both are, pick one randomly)
				set direction to the chosen one 
				Pick a new value for numSquaresToMoveInCurrentDirection
				make sure it doesn’t make another perpendicular turn for at least 200 more non-resting ticks
				continue with step 8****
			8.take one step in the current direction
			if it cannot take a step(blocked)
				set numSquaresToMoveInCurrentDirection to 0 (do nothing during the current tick)
		}

		annoy()
		{
			if (in a leave-the-field state)
				cannot be annoyed
			if (annoyed)
				-2 health on protester
				if (still not completely annoyed)
					play protester annoyed sound
					stun protester to a resting state for N = max(50, 100 – current_level_number * 10) resting ticks
				else //(completely annoyed)
					transition into a leave-the-field state
					play protester give up sound
					set resting tick count to 0
					if (the annoyance was due to a rock)
						increase player score by 500
					else if (annoyance was due to squirt)
						increase player score by 100
		}

		goldGet() ////gold will notify the protester when it is picked up
		{
			play protester found gold sound
			increase player score by 25 
			transition into a leave-the-field state
		}
	*/
};

class HardcoreProtester : public Protester //can be annoyed, set dead, and pick up gold
{
public: //hardcore protestor image, face left, decide how many squares numSquaresToMoveInCurrentDirection. it will decide to move left before possibly switching its direction.
	    //This value must be : 8 <= numSquaresToMoveInCurrentDirection <= 60, 20 health, not in a leave-oil-field state, depth 0, size 1, setVisible(true)
	    //int ticksToWaitBetweenMoves = max(0, 3 – current_level_number / 4) ////every "tick" for a protester is several actual ticks according to this formula
		//the protester must rest for this many ticks between actions
	/*doSomething()
	{
		if (dead)
			return;
		if (in a rest state)
			update resting tick count
			return;
		else if (in a leave - the - field state)
			if (reg protester is at(60, 60))
				set dead
			else
				move one square closer to the exit(60, 60) using a queue based maze algorithm(cannot move through dirt and rocks(within 3 units))
				////hint: find a way to make a single data structure that can find the optimal path no matter where the protester is
				return;
		else if (within 4 units of frackman && facing frackmans direction && protester hasn't shouted within its last non-resting 15 ticks)
			play protester yell sound
			tell frackman that he was annoyed(-2 health)
			update some variable that prevents protester from shouting again for 15 non - resting ticks
			return;
		else if (frackman is > 4 units away)
			Compute a value M, such that M = 16 + current_level_number * 2
			if ( <= M legal vertical or horizontal moves away from frackman using the queue based algorithm)
				determine which direction to take that goes on the path one step closer to frackman
				change direction to the chosen one
				take one step in that direction
				return;
		else if (there is a straight line toward frackman && frackman is > 4 units away && there is no dirt or rocks blocking the straight path)
			change direction toward frackman
			take one step in that direction
			set numSquaresToMoveInCurrentDirection value to zero
			return;
		else if (numSquaresToMoveInCurrentDirection <= 0)
			pick a random direction to move
			if (space in front of that direction is blocked by dirt or rocks)
				select a different direction and check again until one works
				change into this direction
				pick a new value for numSquaresToMoveInCurrentDirection(8 <= numSquaresToMoveInCurrentDirection <= 60) to move over the same number of ticks
				continue with step 8 * ***
			else if (at an intersection where it can turn 90deg and move at least one square without being blocked by dirt or rocks && hasn't turned 90deg in the last 200 non-resting ticks)
				determine which two perpendicular directions are viable(not blocked)
				pick a viable direction(if both are, pick one randomly)
				set direction to the chosen one
				Pick a new value for numSquaresToMoveInCurrentDirection
				make sure it doesn’t make another perpendicular turn for at least 200 more non - resting ticks
				continue with step 8 * ***
			8.take one step in the current direction
				if it cannot take a step(blocked)
					set numSquaresToMoveInCurrentDirection to 0 (do nothing during the current tick)
	}
	
	annoy()
	{
	if (in a leave-the-field state)
		cannot be annoyed
	if (annoyed)
		-2 health on protester
	if (still not completely annoyed)
		play protester annoyed sound
		stun protester to a resting state for N = max(50, 100 – current_level_number * 10) resting ticks
	else //(completely annoyed)
		transition into a leave-the-field state
		play protester give up sound
		set resting tick count to 0
		if (the annoyance was due to a rock)
			increase player score by 500
		else if (annoyance was due to squirt)
			increase player score by 250
	}
	
	goldGet() ////gold will notify the protester when it is picked up
	{
		play protester found gold sound
		increase player score by 50
		put into resting state for ticks_to_stare = max(50, 100 – current_level_number * 10)
		after done staring, continue with the normal algorithm
	}
	*/
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

class oil : public activeStuff
{
public: 
	oil(StudentWorld* sw, int x, int y) : activeStuff(sw, IID_BARREL, x, y, 1000, SOUND_FOUND_OIL, false)
	{}

private:
	virtual void changeAmount();
};

class rock : public stuff//can be set dead but not annoyed
{
public: //rock image, (x,y) location specified by studentworld, start out in a stable state, face down, depth 1, size 1.0, setVisible(true)
	rock(StudentWorld* sw, int x, int y) : stuff(sw, IID_BOULDER, x, y, down, 1.0, 1)
	{
		setVisible(true);
	}
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

class gold : public activeStuff //can be set dead but not annoyed
{
public:  
	gold(StudentWorld* sw, int x, int y) : activeStuff(sw, IID_GOLD, x, y, 10, SOUND_GOT_GOODIE, false)
	{}

private:
	virtual void changeAmount();
};

class goldDrop : public activeStuff
{
public:
	goldDrop(StudentWorld* sw, int x, int y) : activeStuff(sw, IID_GOLD, x, y, 10, SOUND_GOT_GOODIE)
	{}
	/*   100 gameticks lifetime!!!
else if (gold can be picked up by protesters && a protester is <= a radius of 3 units away) ////only one protester can be bribed per gold!!!
			set dead
			play protester found gold sound
			increase player score by 25 (done by either protester or gold class)
			tell protester that he got a gold nugget (for bribery)
		if (gold is in a temporary state)
			if (lifetime has elapsed)
				set dead;
				*/
	virtual void doSomething()
	{}

private:
	virtual void changeAmount() {}
};

class tempGoodie : public activeStuff//cannot be annoyed
{
public: // sonar image, location specified, facing right, setVisible(true), only frackman can pick up, always start in a temporary state 
	    //for T = max(100, 300 – 10*current_level_number) ticks, depth 2, size 1
	tempGoodie(StudentWorld* sw, int image, int x, int y, int points);
		
	virtual void doSomething();
	
private:
	int m_lifeTime;
};

class sonar : public tempGoodie//cannot be annoyed
{
public: // sonar image, location specified, facing right, setVisible(true), only frackman can pick up, always start in a temporary state 
		//for T = max(100, 300 – 10*current_level_number) ticks, depth 2, size 1
	sonar(StudentWorld* sw) : tempGoodie(sw, IID_SONAR, 0, 60, 75)
	{}

private:
	virtual void changeAmount();
};

class water : public tempGoodie //cannot be annoyed
{
public: // water pool image, location specified, facing right, setVisible(true), only frackman can pick up, always start in a temporary state 
	    //for T = max(100, 300 – 10*current_level_number) ticks, depth 2, size 1
	water(StudentWorld* sw, int x, int y) : tempGoodie(sw, IID_WATER_POOL, x, y, 100)
	{}

private:
	virtual void changeAmount();
};

#endif // ACTOR_H_
