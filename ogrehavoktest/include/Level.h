#ifndef LEVEL_H
#define LEVEL_H

#include "stdafx.h"
#include "BaseApplication.h"
#include "Physics.h"
#include "BaseObject.h"
#include <vector>

class Level
{
public:
	Level();
	~Level();
	void Init_Level_One();
	void Init_Level_Two();
	void Update();
private:
	Ogre::Vector3 mSpawnPoint;
	std::vector<BaseObject*> mAllObjects;
};
#endif