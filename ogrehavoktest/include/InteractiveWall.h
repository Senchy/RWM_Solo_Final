#ifndef INTERACTIVEWALL_H
#define INTERACTIVEWALL_H

#include "stdafx.h"
#include "Wall.h"

class InteractiveWall : public Wall
{
private:
public:
	InteractiveWall(Ogre::Vector3 Pos, Ogre::Vector3 size,Physics * physics, Ogre::SceneManager * manager, float rotation);
	~InteractiveWall();
};
#endif