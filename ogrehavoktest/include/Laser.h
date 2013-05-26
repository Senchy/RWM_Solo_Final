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
	~Laser();
	void Update();
	void getOutPut(hkpWorldRayCastOutput &output, Ogre::Vector3 &HitPos);
};
#endif