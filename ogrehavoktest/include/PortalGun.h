#ifndef PORTALGUN_H
#define PORTALGUN_H

#include "stdafx.h"
#include "BaseObject.h"
#include "Portal.h"

class PortalGun : public BaseObject
{
private:
	Ogre::Camera*			mCamera;
	bool					mPortalTracker;
	Portal*					mPortals [2]; 
public:
	PortalGun(Ogre::SceneManager* manager, Physics* physicsManager, Ogre::Camera* camera);
	~PortalGun();
	void Update();
	bool ShootGun();
};
#endif