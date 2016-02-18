#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "Actor.h"
#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
using namespace std;

class Actor;
class FrackMan;
class dirt;

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
	{}

	~StudentWorld();

	virtual int init();

	virtual int move();

	virtual void cleanUp();

	
	void removeDirt();

	void setDisplayText();
		
	
	string organize(int sc, int lvl, int liv, int hp, int wtr, int au, int snr, int oil);

	void insert(char goody);
	
	void checkValid(int& a, int& b);

	int random(int min, int max);

	double distance(int a, int b);
	
	bool radius(int a, int b, double rad);  ////checks if there's something within rad distance inclusive

	void removeOil() { m_oil--; }

private:
	vector<Actor*> m_vec;
	vector<Actor*>::iterator p;
	FrackMan* m_frck;
	dirt* m_dirt[64][64];
	int m_oil;
};

#endif // STUDENTWORLD_H_
