#include "stdafx.h"
#include "LaserManager.h"


LaserManager::LaserManager(Ogre::Vector3 StartPos, Ogre::Vector3 dir, 
	Ogre::Vector3 RecptorPos, Ogre::Vector3 Recptordir,
	Ogre::SceneManager* manager, Physics* physicsManager)
{
	mLaser.push_back(new Laser(StartPos, dir, manager, physicsManager));
	mReceptor = new LaserReceptor(RecptorPos, Recptordir, manager, physicsManager);
}
LaserManager::~LaserManager()
{
}
void LaserManager::Update()
{
	for(int i = 0; i < mLaser.size();i++)
	{
		hkpWorldRayCastOutput output;
		Ogre::Vector3 HitPos;
		mLaser[i]->getOutPut(output,HitPos);
		if(output.hasHit())
		{
			const hkpCollidable* col = output.m_rootCollidable;
			hkpRigidBody* body = hkpGetRigidBody(col);
			Ogre::Vector3 NextLaserCreation = HitPos;
			Ogre::Vector3 NextDirCreation = Ogre::Vector3( output.m_normal(0),output.m_normal(1),output.m_normal(2));
			Create* mCrate = 0;
			mCrate = dynamic_cast<Create*> ((BaseObject *)body->getUserData());
			
			Portal* mPortal = 0;
			mPortal = dynamic_cast<Portal*> ((BaseObject *)body->getUserData());

			LaserReceptor* LR = 0;
			LR = dynamic_cast<LaserReceptor*> ((BaseObject *)body->getUserData());
			if(mCrate != 0)
			{
				mCrate->HitByLaser(NextLaserCreation,NextDirCreation);
			}
			else if(mPortal != 0)
			{
				mPortal->HitByLaser(NextLaserCreation,NextDirCreation);
			}
			else if(LR != 0)
			{
				LR->Hit();
			}
		}
	}
}