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
	mPlayer = new Player(Ogre::Vector3(0,20,0),mSceneMgr,&physics,mKeyboard,mCamera);
	mPortals[0] = new Portal(Ogre::Vector3(100,100,100),&physics, mSceneMgr);
	mPortals[1] = new Portal(Ogre::Vector3(100,100,100),&physics, mSceneMgr);
	mPlayer->INITPortalGun(mPortals);
	mDynamicObjects.push_back(mPlayer);
	mStaticObjects.push_back(mPortals[0]);
	mStaticObjects.push_back(mPortals[1]);
	mStaticObjects.push_back( new Floor(Ogre::Vector3(0,0,0), Ogre::Vector3(1000,0,600),&physics, mSceneMgr));
	mStaticObjects.push_back(new Wall(Ogre::Vector3(0,50,300), Ogre::Vector3(1000,100,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new Wall(Ogre::Vector3(0,50,-300), Ogre::Vector3(1000,100,0),&physics, mSceneMgr, 0));
	mStaticObjects.push_back(new Wall(Ogre::Vector3(500,50,0), Ogre::Vector3(600,100,0),&physics, mSceneMgr, 90));
	mStaticObjects.push_back(new Wall(Ogre::Vector3(-500,50,0), Ogre::Vector3(600,100,0),&physics, mSceneMgr, 90));

	mSceneMgr->setSkyDome(true, "Examples/CloudySky",5,8);
	
}

void ogrehavoktest::destroyScene(void){

	BaseApplication::destroyScene();
}

bool ogrehavoktest::frameRenderingQueued(const Ogre::FrameEvent& evt){
	for(int i = 0; i < mDynamicObjects.size(); i++)
	{
		mDynamicObjects[i]->Update();
		Vector3 Pos = mDynamicObjects[i]->ObjectNode->getPosition();
		Vector3 Vel = Vector3(mDynamicObjects[i]->Body->getLinearVelocity()(0),
			mDynamicObjects[i]->Body->getLinearVelocity()(1),
			mDynamicObjects[i]->Body->getLinearVelocity()(2));
		if(mPortals[0]->SetPlayerOnContact(Pos,Vel))
		{
			mDynamicObjects[i]->Body->setPosition(hkVector4(Pos.x, Pos.y, Pos.z));
			mDynamicObjects[i]->Body->setLinearVelocity(hkVector4(Vel.x, Vel.y, Vel.z));
		}
		else if(mPortals[1]->SetPlayerOnContact(Pos,Vel))
		{
			mDynamicObjects[i]->Body->setPosition(hkVector4(Pos.x, Pos.y, Pos.z));
			mDynamicObjects[i]->Body->setLinearVelocity(hkVector4(Vel.x, Vel.y, Vel.z));
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
