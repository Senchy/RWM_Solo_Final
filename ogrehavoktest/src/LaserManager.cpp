#include "stdafx.h"
#include "LaserManager.h"


LaserManager::LaserManager(Ogre::Vector3 StartPos, Ogre::Vector3 dir, 
	Ogre::Vector3 RecptorPos, Ogre::Vector3 Recptordir,
	Ogre::SceneManager* manager, Physics* physicsManager, Door* thedoor) 
	:
	 mManger(manager)
	,mPhysicsManager(physicsManager)
	,mDoor(thedoor)
	,mShutdown(false)
{
	mLaser.push_back(new Laser(StartPos, dir, manager, physicsManager));
	mReceptor = new LaserReceptor(RecptorPos, Recptordir, manager, physicsManager);
}
LaserManager::~LaserManager()
{
}
void LaserManager::Update()
{
	next++;
	if(next % 3)
	{
		int removaleNode = mLaser.size();
		for(int i = 1; i < removaleNode; i++)
		{
			Laser* distructionlaser = mLaser.at(mLaser.size() - 1);
			distructionlaser->~Laser();
			mLaser.pop_back();
		}
	}
	for(int i = 0; i < mLaser.size();i++)
	{
		hkpWorldRayCastOutput output;
		Ogre::Vector3 HitPos;
		mLaser[i]->getOutPut(output,HitPos);
		mLaser[i]->Update();
		if(output.hasHit())
		{
			const hkpCollidable* col = output.m_rootCollidable;
			hkpRigidBody* body = hkpGetRigidBody(col);
			Ogre::Vector3 NextLaserCreation = HitPos;
			Ogre::Vector3 NextDirCreation = Ogre::Vector3( output.m_normal(0),output.m_normal(1),output.m_normal(2));
			bool CreateNew = false;
			Create* mCrate = 0;
			mCrate = dynamic_cast<Create*> ((BaseObject *)body->getUserData());
			
			Portal* mPortal = 0;
			mPortal = dynamic_cast<Portal*> ((BaseObject *)body->getUserData());

			LaserReceptor* LR = 0;
			LR = dynamic_cast<LaserReceptor*> ((BaseObject *)body->getUserData());

			Player* thePlayer = 0;
			thePlayer = dynamic_cast<Player*> ((BaseObject *)body->getUserData());
				

			if(mCrate != 0)
			{
				CreateNew = mCrate->HitByLaser(NextLaserCreation,NextDirCreation);
			}
			else if(mPortal != 0)
			{
				CreateNew = mPortal->HitByLaser(NextLaserCreation,NextDirCreation);
			}
			else if(LR != 0)
			{
				LR->Hit();
			}
			else if(thePlayer != 0)
			{
				mShutdown = true;
			}
			if(CreateNew == true)
			{
				if(i == (mLaser.size() - 1))
				{
					mLaser.push_back(new Laser(NextLaserCreation,NextDirCreation,mManger,mPhysicsManager));
				}
				else
				{
					if(mLaser[i + 1]->GetPos() != NextLaserCreation || mLaser[i + 1]->GetDir() != NextDirCreation)
					{
						mLaser[i+1]->SetDir(NextDirCreation);
						mLaser[i+1]->SetPos(NextDirCreation);
					}
				}
			}
		}
	}

	if(mReceptor->IsHit())
	{
		mDoor->OpenDoor();
	}
}