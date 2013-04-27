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
	if(WallNormal.y == -1)
	{
		mDirection.y *=-1;
	}
	mActive = true;
}
bool Portal::SetPlayerOnContact(Ogre::Vector3 &Pos, Ogre::Vector3 &Velocity, Ogre::Quaternion &Direction)
{
	Ogre::Vector3 Distance = mPosition - Pos;
	if(Distance.length() < 1.5 * mRadius)
	{
		if(mOtherPortal != NULL)
		{
			if(Velocity.normalisedCopy().directionEquals(-mDirection, Ogre::Degree(30)))
			{
				return mOtherPortal->Transport(Pos,Velocity,Direction);
			}
			else if(mDirection.y > 0.7)
			{
				return mOtherPortal->Transport(Pos,Ogre::Vector3(0,0.2,0),Direction);
			}
		}
	}
	return false;
}
bool Portal::Transport(Ogre::Vector3 &Pos, Ogre::Vector3 &Velocity, Ogre::Quaternion &Direction)
{
	
	if(Velocity.length() > 0.2)
	{
		Pos = mPosition + (mDirection * (1.6 * mRadius));
		Velocity = mDirection * Velocity.length();
		return true;
	}
	return false;
}
Portal::~Portal()
{
}
