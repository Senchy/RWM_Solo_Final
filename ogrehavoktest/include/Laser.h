#ifndef LASER_H
#define LASER_H

#include "stdafx.h"
#include "DynamicObject.h"

class Laser : DynamicObject
{
private:
	Ogre::Vector3				mDirection;
	float						mScaleOffset;
	hkpWorldRayCastInput		mRay;
	hkpWorldRayCastOutput		OutPut;
public:
	Laser(Ogre::Vector3 Pos, Ogre::Vector3 Direction,Ogre::SceneManager* manager, Physics* physicsManager);
	virtual ~Laser();
	void Update();
	Ogre::Vector3 GetPos();
	Ogre::Vector3 GetDir();
	void SetDir(Ogre::Vector3 Pos);
	void SetPos(Ogre::Vector3 Dir);
	void getOutPut(hkpWorldRayCastOutput &output, Ogre::Vector3 &HitPos);
};
#endif