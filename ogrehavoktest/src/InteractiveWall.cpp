#include "stdafx.h"
#include "InteractiveWall.h"

InteractiveWall::InteractiveWall(Ogre::Vector3 Pos, Ogre::Vector3 size,Physics * physics, Ogre::SceneManager * manager, float rotation)
	: Wall(Pos,
			size,
			physics,
			manager,
			rotation)
{
}
InteractiveWall::~InteractiveWall()
{
}