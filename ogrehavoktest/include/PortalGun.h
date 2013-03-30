#ifndef PORTALGUN_H
#define PORTALGUN_H

#include "stdafx.h"
#include "BaseObject.h"
#include "Portal.h"
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastInput.h>         
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>    
#include <Physics/Collide/Query/Collector/RayCollector/hkpAllRayHitCollector.h>

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