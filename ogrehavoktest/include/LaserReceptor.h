#ifndef LASERRECEPTOR_H
#define LASERRECEPTOR_H

#include "stdafx.h"
#include "StaticObject.h"
#include "Laser.h"

class LaserReceptor : StaticObject
{
private:
	Laser *						mLaser;
public:
	LaserReceptor(Ogre::Vector3 PosStart,Ogre::Vector3 direction,Ogre::SceneManager* manager, Physics* physicsManager);
	~LaserReceptor();
};
#endif