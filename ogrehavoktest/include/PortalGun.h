#ifndef PORTALGUN_H
#define PORTALGUN_H

#include "stdafx.h"
#include "BaseObject.h"
#include "Portal.h"
#include "Wall.h"
#include "Floor.h"
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastInput.h>         
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>    
#include <Physics/Collide/Query/Collector/RayCollector/hkpAllRayHitCollector.h>

class PortalGun : public BaseObject
{
private:
	Ogre::Camera*			mCamera;
	Portal*					mPortals [2]; 
public:
	PortalGun(Ogre::SceneManager* manager, Physics* physicsManager, Ogre::Camera* camera);
	~PortalGun();
	void SetPortals(Portal* portals[]);
	void Update();
	bool ShootGun(int WhichPortal);
};
#endif