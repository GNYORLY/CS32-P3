#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
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
					continue;
				else
					m_dirt[r][c] = new dirt(c, r);
			}
		
		int B = min(signed((getLevel() / 2) + 2), 6);
		for (int i = 0; i != B; i++)
		{ 
			int x = 0;
			int y = 0;
			checkDirt(x, y);
			m_vec.push_back(new rock(x, y));
		}
															//put int B = min(current_level_number / 2 + 2, 6) boulders
		int G = max(signed (5 - (getLevel() / 2)), 2);
		for (int i = 0; i != G; i++)
		{
			int x = 0;
			int y = 0;
			checkDirt(x, y);
			m_vec.push_back(new gold(x, y));
		}												//gold (start out pickuppable by frackman in a permanent state but invisible)

		int L = min(signed (2 + getLevel()), 20);		 //oil into the field (invisible)
		for (int i = 0; i != L; i++)
		{
			int x = 0;
			int y = 0;
			checkDirt(x, y);
			m_vec.push_back(new oil(x, y));
		}
														//no object can be within a radius of 6 from each other
												                                            //all objects must be completely overlapped with dirt (its actually behind them but they're invisible)
													                                        //rocks cannot overlap any dirt
		return GWSTATUS_CONTINUE_GAME;
	}

	virtual int move()
	{
		//updateDisplayText(); // update the score/lives/level text at screen top
							 
					 // The term “Actors” refers to all Protesters, the player, Goodies,
					 // Boulders, Barrels of oil, Holes, Squirts, the Exit, etc.
					 // Give each Actor a chance to do something
		/*m_vec.push_back(1);
		std::vector<Actor>::iterator p;
		for (p = m_vec.begin(); p != m_vec.end(); p++)
		{
			cout << *p << endl;
		}*/
		/*	if (p->health() > 0)
			{
				// ask each actor to do something (e.g. move)
				doSomething(p);
				if (p->health() <= 0)
					return GWSTATUS_PLAYER_DIED;
				if (theplayerCompletedTheCurrentLevel() == true)
				{
					return GWSTATUS_FINISHED_LEVEL;
				}
			}
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
			m_gw->playSound(SOUND_PROTESTER_GIVE_UP);
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

	GameWorld* getGetWorld()
	{
		return m_gw;
	}

	void updateDisplayText()
	{
		m_gw->setGameStatText("hello");
	}

	void checkDirt(int& a, int& b)
	{
			do
			{
				a = random(0, 60);
				b = random(20, 56);
			} while (m_dirt[b][a] == nullptr || m_dirt[b - 3][a + 3] == nullptr);
			
	}

	int random(int min, int max)
	{
		return (rand() % (((max-min)+1) + min));
	}

	void removeOil()
	{
		m_oil--;
		if (m_oil <= 0)
			advanceToNextLevel();
	}
private:
	std::vector<Actor*> m_vec;
	FrackMan* m_frck;
	dirt* m_dirt[60][64];
	GameWorld* m_gw;
	int m_oil;
};

#endif // STUDENTWORLD_H_
