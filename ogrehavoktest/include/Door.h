#ifndef DOOR_H
#define DOOR_H

#include "stdafx.h"
#include "StaticObject.h"


class Door : public StaticObject
{
private:
	int			mIter;
	bool		mOpen;
public:
	Door(Ogre::Vector3 Pos, Physics * physics, Ogre::SceneManager * manager, float rotation);
	~Door();
	void Update();
	void OpenDoor();
};
#endif