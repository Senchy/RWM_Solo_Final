#ifndef WALL_H
#define WALL_H

#include "stdafx.h"
#include "StaticObject.h"


class Wall : public StaticObject
{
private:
public:
	Wall(Ogre::Vector3 Pos, Ogre::Vector3 size,Physics * physics, Ogre::SceneManager * manager, float rotation);
	~Wall();
};
#endif