#ifndef FLOOR_H
#define FLOOR_H

#include "stdafx.h"
#include "StaticObject.h"

class Floor : public StaticObject
{
private:
public:
	Floor(Ogre::Vector3 Pos, Ogre::Vector3 size,Physics * physics, Ogre::SceneManager * manager);
	~Floor();
};
#endif