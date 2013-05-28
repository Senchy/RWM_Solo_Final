#ifndef PLAYER_H
#define PLAYER_H

#include "stdafx.h"
#include "DynamicObject.h"
#include "PortalGun.h"
#include "Create.h"
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastInput.h>         
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>    
#include <Physics/Collide/Query/Collector/RayCollector/hkpAllRayHitCollector.h>


class Player :	public DynamicObject
{
private:
	int						mMoveTimeOut;
	int						mPickUpTimeOut;
	int						mFireTimeOut;
	Ogre::Camera*			mCamera;
	OIS::Mouse*				mMouse;
	OIS::Keyboard *			mKeyboard;
	float					mSpeed;
	hkReal					mJumpForce;
	float					mCameraOffset;
	PortalGun *				mGun;
	hkpRigidBody *			mBOX;
public:
	bool					HoldingObject;
	bool					IsOnGround;
	Player(Ogre::Vector3 position, Ogre::SceneManager* manager, Physics* physicsManager,OIS::Keyboard * Keyboard, Ogre::Camera* camera, OIS::Mouse* Mouse);
	bool CheckIfPickUpOBject();
	void INITPortalGun(Portal* portals[]);
	void CheckIfOnGround();
	virtual ~Player();
	virtual void Update();
	virtual void OnDeath();
};
#endif