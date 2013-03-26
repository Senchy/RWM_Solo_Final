#ifndef INTERACTIVEFLOOR_H
#define INTERACTIVEFLOOR_H

#include "stdafx.h"
#include "Floor.h"

class InteractiveFloor : public Floor
{
private:
public:
	InteractiveFloor(Ogre::Vector3 Pos, Ogre::Vector3 size, Physics * physics, Ogre::SceneManager * manager);
	~InteractiveFloor();
};
#endif