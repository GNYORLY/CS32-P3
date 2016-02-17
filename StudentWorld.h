#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <vector>
using namespace std;

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
	{
	}

	virtual int init()
	{
		//fill field with dirt appropriately
		//put int B = min(current_level_number / 2 + 2, 6) boulders
		//int G = max(5-current_level_number / 2, 2) gold (start out pickuppable by frackman in a permanent state but invisible)
		//and int L = min(2 + current_level_number, 20) oil into the field (invisible)
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
		return GWSTATUS_PLAYER_DIED;
	}

	virtual void cleanUp()
	{
	}

	void updateDisplayText()
	{
		m_gw->setGameStatText("hello");
	}
private:
	std::vector<Actor> m_vec;
	FrackMan* m_frck;
	dirt* m_dirt[60][60];
	GameWorld* m_gw;
};

#endif // STUDENTWORLD_H_
