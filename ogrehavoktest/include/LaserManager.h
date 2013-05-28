#ifndef LASERMANAGER_H
#define LASERMANAGER_H

#include "stdafx.h"
#include "BaseApplication.h"
#include "Physics.h"
#include "Laser.h"
#include "Create.h"
#include "Portal.h"
#include "Door.h"
#include "LaserReceptor.h"
#include "Player.h"
#include <vector>

class LaserManager
{

private:
	std::vector<Laser*>		mLaser;
	LaserReceptor*			mReceptor;
	Ogre::SceneManager*		mManger;
	Physics*				mPhysicsManager;
	Door*					mDoor;
	int						next;
public:
	bool					mShutdown;
	LaserManager(Ogre::Vector3 StartPos, Ogre::Vector3 dir, 
		Ogre::Vector3 RecptorPos,Ogre::Vector3 Recptordir,
		Ogre::SceneManager* manager, Physics* physicsManager, Door* thedoor);
	~LaserManager();
	void Update();
};
#endif