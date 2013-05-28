#include "stdafx.h"
#include "NoneInteractiveFloor.h"

NoneInteractiveFloor::NoneInteractiveFloor(Ogre::Vector3 Pos, Ogre::Vector3 size, Physics * physics, Ogre::SceneManager * manager)
	:Floor(Pos,
		size,
		physics,
		manager)
{
	Body->setUserData(hkUlong(this));
	ObjectEnt->setMaterialName("Examples/BeachStones");
}
NoneInteractiveFloor::~NoneInteractiveFloor()
{
}