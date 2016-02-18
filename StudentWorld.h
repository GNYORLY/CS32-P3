#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <sstream>
#include "Actor.h"
using namespace std;

class Actor;
class FrackMan;
class dirt;

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
	{
	}

	virtual int init()
	{
		for (int r = 0; r != 60; r++)
			for (int c = 0; c != 64; c++)
			{
				if (c >= 30 && c <= 33 && r >= 4)
					m_dirt[r][c] = nullptr;
				else
					m_dirt[r][c] = new dirt(c, r);
			}
		insert('B');
		insert('G');
		insert('L');
		m_frck = new FrackMan;
		return GWSTATUS_CONTINUE_GAME;
	}

	virtual int move()
	{
		setDisplayText(); // update the score/lives/level text at screen top

					 // The term “Actors” refers to all Protesters, the player, Goodies,
					 // Boulders, Barrels of oil, Holes, Squirts, the Exit, etc.
					 // Give each Actor a chance to do something
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
		}

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

	virtual void cleanUp()
	{
	}

	void removeDirt()
	{ 
		int x = m_frck->posX();
		int y = m_frck->posY();
		for (int i = 0; i < 4; i++, x++)
		{
			int b = y;
			for (int j = 0; j < 4; j++, b++)
				if (m_dirt[b][x] != nullptr)
				{
					delete m_dirt[b][x];
					m_dirt[b][x] = nullptr;
				}
		}
	}

	GameWorld* getGetWorld()
	{
		return m_gw;
	}

	void setDisplayText()
	{
		int score = getScore();
		int level = getLevel();
		int lives = getLives();
		int health = (m_frck->health()/10)*100;
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
		
	string organize(int sc, int lvl, int liv, int hp, int wtr, int au, int snr, int oil)
	{ 
		stringstream ss;
		ss << setw(8) << setfill('0') << sc;
		string s = ss.str();
		return "Scr: " + s + "  Lvl : " + to_string(lvl) + "  Lives : " + to_string(liv) + "  Hlth : " + to_string(hp) + "%  Water : " + to_string(wtr) + "  Gld : " + to_string(au) + "  Sonar : " + to_string(snr) + "  Oil Left : " + to_string(oil);
	}

	void insert(char goody)
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
				m_vec.push_back(new rock(x, y));
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
				m_vec.push_back(new gold(x, y));

			}
			break;
		case 'L':
			objects = min(signed(2 + getLevel()), 20);
			for (int i = 0; i != objects; i++)
			{
				int x = 0;
				int y = 0;
				checkValid(x, y);
				m_vec.push_back(new oil(x, y));
			}
			m_oil = objects;
			break;
		}
	}

	void checkValid(int& a, int& b) //in dirt and outside radius 6 of another object
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

	int random(int min, int max)
	{
		return (rand() % (((max-min)+1) + min));
	}

	double distance(int a, int b)
	{
		return sqrt((a*a) + (b*b));
	}
	
	bool radius(int a, int b, double rad)
	{
		for (p = m_vec.begin(); p != m_vec.end(); p++)
		{
			if (distance(a - (*p)->posX(), b - (*p)->posY()) <= rad)       ////checks if there's something within rad distance inclusive
				return true;
		}
		return false;
	}

	void removeOil()
	{
		m_oil--;
	}
private:
	vector<Actor*> m_vec;
	vector<Actor*>::iterator p;
	FrackMan* m_frck;
	dirt* m_dirt[60][64];
	GameWorld* m_gw;
	int m_oil;
};

#endif // STUDENTWORLD_H_
