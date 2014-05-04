#pragma once
#include<vector>
#include<map>
#include<time.h>
#include"GameObject.h"
#include<boost\thread\thread.hpp>
#include<boost\thread\mutex.hpp>
using namespace std;



class GameEngine
{
	vector<Unit*> unitObj;
	boost::mutex* mut;

	//vector<Envirement*> envirementObj;
	//Map map;
public:
	GameEngine(void)
	{
		mut= new boost::mutex();
		srand((unsigned int)this);
		FactoryUnit fac("hello");
		fac.Load("cubeN.obj","grass.jpg");
		for(int i=0;i<1000;i++)
			unitObj.push_back(fac.GetUnit(0,rand()%100-rand()%100,rand()%100-rand()%100,rand()%180));
		
	}
	void operator()()
	{
		Loop();
	}
	bool SetUnitStatus(unsigned int id, State status)
	{
		GLuint len = unitObj.size();
			for(int i=0;i<len;i++)
				if(unitObj[i]->GetID() == id)
				{
					unitObj[i]->Interaction(status);
					return true;
				}
				return false;
	}
	Unit* GetUnit(GLuint id)
	{
		return unitObj[id];
	}
	vector<Unit*>* GetUnits()
	{
		return &unitObj;
	}
	void Loop()
	{
		
		int time = clock();
		while(true)
		{
			if((clock() - time) < 10)
				continue;

			time = clock();
		//	mut->lock();
			GLuint len = unitObj.size();
			for(int i=0;i<len;i++)
			{
				unitObj[i]->Do();
				unitObj[i]->Rotage(1);
			}
			//mut->unlock();
		}
	}
	vector<int> GetVisibleUnits();
	~GameEngine()
	{
		
	}
};

