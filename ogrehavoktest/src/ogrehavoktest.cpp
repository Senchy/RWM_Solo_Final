/*
-----------------------------------------------------------------------------
Filename:    ogrehavoktest.cpp
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
#include "stdafx.h"
#include "BaseApplication.h"
#include "ogrehavoktest.h"

//-------------------------------------------------------------------------------------

const int NUM_BOXES=20;

ogrehavoktest::ogrehavoktest(void)
{
}
//-------------------------------------------------------------------------------------
ogrehavoktest::~ogrehavoktest(void)
{
	physics.TidyUp();
}

//-------------------------------------------------------------------------------------


void ogrehavoktest::createScene(void)
{	
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	// Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    // Create a light
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(20,500,50);

	physics.SetUp(); //perform havok initialisation stuff
	mPlayer = new Player(Ogre::Vector3(10,50,1470.5),mSceneMgr,&physics,mKeyboard,mCamera,mMouse);
	mPortals[0] = new Portal(Ogre::Vector3(-1000,-1000,-1000),&physics, mSceneMgr);
	mPortals[1] = new Portal(Ogre::Vector3(-1000,-1000,-1000),&physics, mSceneMgr);
	mPlayer->INITPortalGun(mPortals);

	mDynamicObjects.push_back(mPlayer);


	mStaticObjects.push_back(mPortals[0]);
	mStaticObjects.push_back(mPortals[1]);
	
	Door* newDoors = new Door(Ogre::Vector3(0,40,493),&physics, mSceneMgr, 0);
	mDoors.push_back(newDoors);
	mStaticObjects.push_back(newDoors);

	mStaticObjects.push_back(new NoneInteractiveWall(Ogre::Vector3(-100,80,0), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));
	mStaticObjects.push_back( new NoneInteractiveFloor(Ogre::Vector3(0,0,0), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new NoneInteractiveWall(Ogre::Vector3(0,80,-100), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new NoneInteractiveWall(Ogre::Vector3(0,80,100), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));

	
	mStaticObjects.push_back(new NoneInteractiveWall(Ogre::Vector3(196.5,80,-100), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new NoneInteractiveWall(Ogre::Vector3(196.5,80,100), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new NoneInteractiveWall(Ogre::Vector3(196.5,-78,-100), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new NoneInteractiveWall(Ogre::Vector3(196.5,-78,100), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new NoneInteractiveWall(Ogre::Vector3(96.5,-78,0), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));
	mStaticObjects.push_back(new NoneInteractiveWall(Ogre::Vector3(293,-78,0), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(196.5,-150,0), Ogre::Vector3(200,0,200),&physics, mSceneMgr));

	mStaticObjects.push_back( new NoneInteractiveFloor(Ogre::Vector3(393,0,0), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new NoneInteractiveWall(Ogre::Vector3(393,80,-100), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new NoneInteractiveWall(Ogre::Vector3(393,80,100), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));

	mStaticObjects.push_back( new NoneInteractiveFloor(Ogre::Vector3(589.5,0,0), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new NoneInteractiveWall(Ogre::Vector3(589.5,80,-100), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new NoneInteractiveWall(Ogre::Vector3(589.5,80,100), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));

	mStaticObjects.push_back( new NoneInteractiveFloor(Ogre::Vector3(786,0,0), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new NoneInteractiveWall(Ogre::Vector3(786,80,-100), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));

	mStaticObjects.push_back( new NoneInteractiveFloor(Ogre::Vector3(982.5,0,0), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new NoneInteractiveWall(Ogre::Vector3(982.5,80,-100), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));

	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(1179,-150,0), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(1279,80,0), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));
	mStaticObjects.push_back(new NoneInteractiveWall(Ogre::Vector3(1179,80,-100), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new NoneInteractiveWall(Ogre::Vector3(1179,80,100), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new NoneInteractiveWall(Ogre::Vector3(1179,-78,-100), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new NoneInteractiveWall(Ogre::Vector3(1179,-78,100), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(1079,-78,0), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(1279,-78,0), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));



	
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(-100,80,196.5), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));
	mLasers.push_back(new LaserManager(Ogre::Vector3(-90,20,330), Ogre::Vector3(1,0,0),Ogre::Vector3(393,30,110), Ogre::Vector3(0,0,0),mSceneMgr,&physics,mDoors[0]));
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(0,0,196.5), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(196.5,0,196.5), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(393,0,196.5), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(589.5,0,196.5), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back( new NoneInteractiveFloor(Ogre::Vector3(786,0,196.5), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mDynamicObjects.push_back(new Create(Ogre::Vector3(786,50,210),mSceneMgr,&physics));
	mStaticObjects.push_back( new NoneInteractiveFloor(Ogre::Vector3(982.5,0,196.5), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new NoneInteractiveWall(Ogre::Vector3(1079,80,196.5), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));
	


	
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(-100,80,393), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(0,0,393), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	

	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(-64,80,493), Ogre::Vector3(72,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(64,80,493), Ogre::Vector3(72,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(0,120,493), Ogre::Vector3(60,90,0),&physics, mSceneMgr, 0));

	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(196.5,0,393), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(196.5,80,493), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));

	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(393,0,393), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(393,80,493), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));

	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(589.5,0,393), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(589.5,80,493), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));

	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(786,0,393), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(786,80,493), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));

	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(982.5,0,393), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(982.5,80,493), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(1079,80,393), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));

	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(800,160,695), Ogre::Vector3(2000,0,1600),&physics, mSceneMgr));



	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(-100,80,588), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(0,0,588), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(0,80,688), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));

	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(196.5,0,588), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(196.5,80,688), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));

	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(393,0,588), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(589.5,0,588), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(786,0,588), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(982.5,0,588), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(1079,80,588), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));



	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(293,80,784.5), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(982.5,0,784.5), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(1079,80,784.5), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));




	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(293,80,981), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(589.5,0,981), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	Turret* newTurret = new Turret(Ogre::Vector3(589.5,80,981),mSceneMgr,&physics);
	mTurrets.push_back(newTurret);
	mDynamicObjects.push_back(newTurret);
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(982.5,0,981), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(1079,80,981), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));



	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(293,80,1177.5), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(982.5,0,1177.5), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(1079,80,1177.5), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));



	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(-100,80,1374), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(0,0,1374), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(0,80,1274), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(196.5,0,1374), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(196.5,80,1274), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(393,0,1374), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(589.5,0,1374), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(786,0,1374), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(982.5,0,1374), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(1079,80,1374), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));


	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(-100,80,1570.5), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(100,240,1570.5), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));
	Catapult* newCatapult = new Catapult(Ogre::Vector3(0,0,1570.5),&physics, mSceneMgr);
	mCatapult.push_back(newCatapult);
	mStaticObjects.push_back(newCatapult);
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(0,0,1570.5), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(0,160,1570.5), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(0,80,1670.5), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));

	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(196.5,0,1570.5), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(196.5,80,1470.5), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(196.5,80,1670.5), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));

	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(393,0,1570.5), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(393,80,1470.5), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(393,80,1670.5), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(786,80,1470.5), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(982.5,80,1470.5), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(1079,80,1470.5), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));

	mStaticObjects.push_back( new InteractiveFloor(Ogre::Vector3(589.5,130,1570.5), Ogre::Vector3(200,0,200),&physics, mSceneMgr));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(589.5,80,1470.5), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(589.5,80,1670.5), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new InteractiveWall(Ogre::Vector3(489.5,50,1570.5), Ogre::Vector3(200,160,0),&physics, mSceneMgr, 90));


	mSceneMgr->setSkyDome(true, "Examples/CloudySky",5,8);
	
}

void ogrehavoktest::destroyScene(void){

	BaseApplication::destroyScene();
}

bool ogrehavoktest::frameRenderingQueued(const Ogre::FrameEvent& evt){
	for(int i = 0; i < mDynamicObjects.size(); i++)
	{
		mDynamicObjects[i]->Update();
	}
	for(int i = 0; i < mTurrets.size(); i++)
	{
		mTurrets[i]->SetPlayerPos(Ogre::Vector3(mPlayer->Body->getPosition()(0),
												mPlayer->Body->getPosition()(1),
												mPlayer->Body->getPosition()(2)));
		if(mTurrets[i]->mShutdown == true)
		{	
			BaseApplication::Shutdown();
		}
	}
	for(int i = 0; i < mDoors.size(); i++)
	{
		mDoors[i]->Update();
	}
	for(int i = 0; i < mCatapult.size();i++)
	{
		mCatapult[i]->Update();
	}
	for(int i = 0; i < mLasers.size();i++)
	{
		mLasers[i]->Update();
		if(mLasers[i]->mShutdown == true)
		{	
			BaseApplication::Shutdown();
		}
	}
	physics.Simulate(evt.timeSinceLastFrame*3);
	return BaseApplication::frameRenderingQueued(evt); 
}




#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        ogrehavoktest app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
