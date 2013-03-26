#include "stdafx.h"
#include "InteractiveFloor.h"


InteractiveFloor::InteractiveFloor(Ogre::Vector3 Pos, Ogre::Vector3 size, Physics * physics, Ogre::SceneManager * manager)
	:Floor(Pos,
		size,
		physics,
		manager)
{
}
InteractiveFloor::~InteractiveFloor()
{
}