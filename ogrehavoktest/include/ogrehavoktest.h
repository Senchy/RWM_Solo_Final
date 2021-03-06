/*
-----------------------------------------------------------------------------
Filename:    ogrehavoktest.h
-----------------------------------------------------------------------------


This source file is generated by the
   ___                   _              __    __ _                  _ 
  /___\__ _ _ __ ___    /_\  _ __  _ __/ / /\ \ (_)______ _ _ __ __| |
 //  // _` | '__/ _ \  //_\\| '_ \| '_ \ \/  \/ / |_  / _` | '__/ _` |
/ \_// (_| | | |  __/ /  _  \ |_) | |_) \  /\  /| |/ / (_| | | | (_| |
\___/ \__, |_|  \___| \_/ \_/ .__/| .__/ \/  \/ |_/___\__,_|_|  \__,_|
      |___/                 |_|   |_|                                 
      Ogre 1.7.x Application Wizard for VC9 (August 2010)
      http://code.google.com/p/ogreappwizards/
-----------------------------------------------------------------------------
*/
#ifndef __ogrehavoktest_h_
#define __ogrehavoktest_h_

#include "BaseObject.h"
#include "Physics.h"
#include "Player.h"
#include "StaticObject.h"
#include "DynamicObject.h"
#include "InteractiveFloor.h"
#include "InteractiveWall.h"
#include "NoneInteractiveFloor.h"
#include "NoneInteractiveWall.h"
#include "Create.h"
#include "LaserManager.h"
#include "TestC.h"
#include "Turret.h"
#include "Door.h"
#include "Catapult.h"
#include <vector>

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif


using namespace Ogre;

class ogrehavoktest : public BaseApplication
{
public:
	Physics physics;
    ogrehavoktest(void);
    virtual ~ogrehavoktest(void);
	bool shutdown;

protected:
	std::vector<LaserManager* >		mLasers;
	std::vector<DynamicObject*>		mDynamicObjects;
	std::vector<StaticObject*>		mStaticObjects;
	std::vector<Turret*>			mTurrets;
	std::vector<Door*>				mDoors;
	std::vector<Catapult*>			mCatapult;
	Player*							mPlayer;
	Portal*							mPortals[2]; 
    virtual void createScene(void);
	virtual void destroyScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent&);
};
#endif // #ifndef __ogrehavoktest_h_
