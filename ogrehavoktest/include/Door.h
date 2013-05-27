#ifndef DOOR_H
#define DOOR_H

#include "stdafx.h"
#include "StaticObject.h"


class Door : public StaticObject
{
private:
	int			mIter;
public:
	Door(Ogre::Vector3 Pos, Physics * physics, Ogre::SceneManager * manager, float rotation);
	~Door();
	void OpenDoor();
};
#endif