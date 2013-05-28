#include "stdafx.h"
#include "NoneInteractiveWall.h"

NoneInteractiveWall::NoneInteractiveWall(Ogre::Vector3 Pos, Ogre::Vector3 size,Physics * physics, Ogre::SceneManager * manager, float rotation)
	: Wall(Pos,
			size,
			physics,
			manager,
			rotation)
{
	Body->setUserData(hkUlong(this));
}
NoneInteractiveWall::~NoneInteractiveWall()
{
}