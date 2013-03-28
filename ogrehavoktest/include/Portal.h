#ifndef PORTAL_H
#define PORTAL_H

#include "stdafx.h"
#include "StaticObject.h"

class Portal : StaticObject
{
private:
	bool					mActive;
	Portal*					mOtherPortal;
	Ogre::Vector3			mDirection;
public:
	Portal(Ogre::Vector3 Pos, Physics * physics, Ogre::SceneManager * manager);
	void SetPosition(Ogre::Vector3 Pos, Ogre::Vector3 WallNormal);
	Ogre::Vector3 SetPlayerOnContact(Ogre::Vector3 Pos, Ogre::Vector3 Velocity, float Size);
	void SetOtherPortal(Portal* portal);
	Ogre::Vector3 Transport(Ogre::Vector3 Pos, Ogre::Vector3 Velocity, float Size);
	~Portal();
};
#endif