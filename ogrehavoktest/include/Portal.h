#ifndef PORTAL_H
#define PORTAL_H

#include "stdafx.h"
#include "StaticObject.h"

class Portal : public StaticObject
{
private:
	bool					mActive;
	Portal*					mOtherPortal;
	Ogre::Vector3			mDirection;
	hkReal					mRadius;
public:
	Portal(Ogre::Vector3 Pos, Physics * physics, Ogre::SceneManager * manager);
	void SetPosition(Ogre::Vector3 Pos, Ogre::Vector3 WallNormal);
	bool SetPlayerOnContact(Ogre::Vector3 &Pos, Ogre::Vector3 &Velocity);
	bool Transport(Ogre::Vector3 &Pos, Ogre::Vector3 &Velocity);
	void SetOtherPortal(Portal* portal);
	void SetColor(std::string meshname);
	~Portal();
};
#endif