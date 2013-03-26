#ifndef PORTALGUN_H
#define PORTALGUN_H

#include "stdafx.h"
#include "BaseObject.h"
#include "Portal.h"

class PortalGun : public BaseObject
{
private:
	Ogre::Camera*			mCamera;
	Portal*					Portals [2]; 
public:
	PortalGun(Ogre::Vector3 position, Ogre::Vector3 size, Ogre::Quaternion orintation, Ogre::SceneManager* manager, Physics* physicsManager, Ogre::Camera* camera);
	~PortalGun();
	void Update();
};
#endif