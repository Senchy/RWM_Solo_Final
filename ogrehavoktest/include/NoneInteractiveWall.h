#ifndef NONEINTERACTIVEWALL_H
#define NONEINTERACTIVEWALL_H

#include "stdafx.h"
#include "Wall.h"

class NoneInteractiveWall : public Wall
{
private:
public:
	NoneInteractiveWall(Ogre::Vector3 Pos, Ogre::Vector3 size,Physics * physics, Ogre::SceneManager * manager, float rotation);
	~NoneInteractiveWall();
};
#endif