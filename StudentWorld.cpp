#include "StudentWorld.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

StudentWorld::~StudentWorld()
{
	for (p = m_vec.begin(); p != m_vec.end(); p++)
		delete *p;
	m_vec.clear();
	delete m_frck;
	for (int r = 0; r != 60; r++)
		for (int c = 0; c != 64; c++)
		{
			delete m_dirt[r][c];
		}
}

int StudentWorld::init()
{
	for (int r = 0; r != 64; r++)
		for (int c = 0; c != 64; c++)
		{
			if (r >= 60)
				m_dirt[r][c] = nullptr;
			else if (c >= 30 && c <= 33 && r >= 4)
				m_dirt[r][c] = nullptr;
			else
				m_dirt[r][c] = new dirt(this, c, r);
		}
	insert('B');
	insert('G');
	insert('L');
	m_frck = new FrackMan(this);
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	setDisplayText();
	m_frck->doSomething();
	for (p = m_vec.begin(); p != m_vec.end(); p++)
	{
		if (!(*p)->isDead())
		{
			(*p)->doSomething();
			if (m_frck->isDead())
				return GWSTATUS_PLAYER_DIED;
			if (m_oil <= 0)
			{
				playSound(SOUND_PROTESTER_GIVE_UP);
				return GWSTATUS_FINISHED_LEVEL;
			}
		}
		else
			delete *p;

		/*if (m_frck->isDead())
		//return GWSTATUS_PLAYER_DIED;

		if (m_oil <= 0)
		{
		playSound(SOUND_PROTESTER_GIVE_UP);
		return GWSTATUS_FINISHED_LEVEL;
		}

		// Remove newly-dead actors after each tick
		removeDeadGameObjects(); // delete dead game objects
		// return the proper result
		if (theplayerDiedDuringThisTick() == true)
		return GWSTATUS_PLAYER_DIED;
		// If the player has collected all of the Barrels on the level, then
		// return the result that the player finished the level
		if (theplayerCompletedTheCurrentLevel() == true)
		{
		playSound(SOUND_PROTESTER_GIVE_UP);
		return GWSTATUS_FINISHED_LEVEL;
		}
		// the player hasn’t completed the current level and hasn’t died
		// let them continue playing the current level
		*/
		return GWSTATUS_CONTINUE_GAME;
	}
}

void StudentWorld::cleanUp()
{
	for (p = m_vec.begin(); p != m_vec.end(); p++)
		delete *p;
	m_vec.clear();
	delete m_frck;
	for (int r = 0; r != 60; r++)
		for (int c = 0; c != 64; c++)
		{
			delete m_dirt[r][c];
		}
}

void StudentWorld::removeDirt()
{
	int x = m_frck->getX();
	int y = m_frck->getY();
	for (int i = 0; i < 4; i++, x++)
	{
		int b = y;
		for (int j = 0; j < 4; j++, b++)
			if (m_dirt[b][x] != nullptr)
			{
				delete m_dirt[b][x];
				m_dirt[b][x] = nullptr;
				playSound(SOUND_DIG);
			}
	}
}

void StudentWorld::setDisplayText()
{
	int score = getScore();
	int level = getLevel();
	int lives = getLives();
	int health = (m_frck->health() / 10) * 100;
	int squirts = m_frck->water();
	int gold = m_frck->gold();
	int sonar = m_frck->sonar();
	int barrelsLeft = m_oil;
	// Next, create a string from your statistics, of the form: // “Scr: 0321000 Lvl: 52 Lives: 3 Hlth: 80% Water: 20 Gld: 3 Sonar: 1 Oil Left: 2”
	string s = organize(score, level, lives, health, squirts, gold, sonar, barrelsLeft);
	// Finally, update the display text at the top of the screen with your
	// newly created stats
	setGameStatText(s); // calls our provided GameWorld::setGameStatText
}

string StudentWorld::organize(int sc, int lvl, int liv, int hp, int wtr, int au, int snr, int oil)
{
	stringstream ss;
	ss << setw(8) << setfill('0') << sc;
	string s = ss.str();
	return "Scr: " + s + " Lvl : " + to_string(lvl) + " Lives : " + to_string(liv) + " Hlth : " + to_string(hp) + "%  Water : " + to_string(wtr) + " Gld : " + to_string(au) + " Sonar : " + to_string(snr) + " Oil Left : " + to_string(oil);
}

void StudentWorld::insert(char goody)
{
	int objects;
	switch (goody)
	{
	case 'B':
		objects = min(signed((getLevel() / 2) + 2), 6);
		for (int i = 0; i != objects; i++)
		{
			int x = 0;
			int y = 0;
			checkValid(x, y);
			m_vec.push_back(new rock(this, x, y));
			int a = x;
			for (int i = 0; i < 4; i++, a++)
			{
				int b = y;
				for (int j = 0; j < 4; j++, b++)
				{
					delete m_dirt[b][a];
					m_dirt[b][a] = nullptr;
				}
			}

		}
		break;
	case 'G':
		objects = max(signed(5 - (getLevel() / 2)), 2);
		for (int i = 0; i != objects; i++)
		{
			int x = 0;
			int y = 0;
			checkValid(x, y);
			m_vec.push_back(new gold(this, x, y));

		}
		break;
	case 'L':
		objects = min(signed(2 + getLevel()), 20);
		for (int i = 0; i != objects; i++)
		{
			int x = 0;
			int y = 0;
			checkValid(x, y);
			m_vec.push_back(new oil(this, x, y));
		}
		m_oil = objects;
		break;
	}
}

void StudentWorld::checkValid(int& a, int& b)
{

	while (true)
	{
		int i = 0;
		a = random(0, 60);
		b = random(20, 56);
		int x = a;
		int y = b;
		if (radius(a, b, 6.0))
			continue;
		if (x + 3 >= 30 && x + 3 <= 33 && y > 0)
			continue;
		else if (x >= 30 && x <= 33 && y > 0)
			continue;
		else
			return;
	}
}

int StudentWorld::random(int min, int max)
{
	return (rand() % (((max - min) + 1) + min));
}

double StudentWorld::distance(int a, int b)
{
	return sqrt((a*a) + (b*b));
}

bool StudentWorld::radius(int a, int b, double rad) 
{
	for (p = m_vec.begin(); p != m_vec.end(); p++)
	{
		if (distance(a - (*p)->getX(), b - (*p)->getY()) <= rad)
			return true;
	}
	return false;
}

