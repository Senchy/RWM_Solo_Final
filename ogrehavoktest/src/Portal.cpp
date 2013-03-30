#include "stdafx.h"
#include "Portal.h"


Portal::Portal(Ogre::Vector3 Pos,Physics * physics, Ogre::SceneManager * manager)
	: StaticObject( Pos, Ogre::Vector3(1,1,1), "barrel.mesh", physics, manager),
		mActive(false),
		mOtherPortal(NULL),
		mRadius(22.0f)
{
	
	ObjectEnt->setMaterialName("Examples/WaterStream");
	ObjectNode->setScale(Ogre::Vector3(2.6 * mRadius / ObjectEnt->getBoundingRadius(),
						0.6, 1.8 * mRadius / ObjectEnt->getBoundingRadius()));
	
}

void Portal::SetOtherPortal(Portal* portal)
{
	mOtherPortal = portal;
}
void Portal::SetColor(std::string meshname)
{
	ObjectEnt->setMaterialName(meshname);
}
void Portal::SetPosition(Ogre::Vector3 Pos, Ogre::Vector3 WallNormal)
{
	mPosition = Pos;
	ObjectNode->setPosition(Pos);
	ObjectNode->setOrientation(1,WallNormal.z,WallNormal.y,-WallNormal.x);
	mDirection = ObjectNode->getOrientation() * Ogre::Vector3::UNIT_Y;
	mActive = true;
}
bool Portal::SetPlayerOnContact(Ogre::Vector3 &Pos, Ogre::Vector3 &Velocity)
{
	Ogre::Vector3 Distance = mPosition - Pos;
	if(Distance.length() < 2 * mRadius)
	{
		if(mOtherPortal != NULL)
		{
			if(Velocity.normalisedCopy().directionEquals(-mDirection, Ogre::Degree(10)))
			{
				return mOtherPortal->Transport(Pos,Velocity);
			}
		}
	}
	return false;
}
bool Portal::Transport(Ogre::Vector3 &Pos, Ogre::Vector3 &Velocity)
{
	
	if(Velocity.length() > 3)
	{
		Pos = mPosition + (mDirection * (2 * mRadius));
		Velocity = mDirection * Velocity.length();
		return true;
	}
	return false;
}
Portal::~Portal()
{
}
