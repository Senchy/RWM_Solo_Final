#ifndef CATAPULT_H
#define CATAPULT_H

#include "stdafx.h"
#include "StaticObject.h"
#include "Sensor.h"
#include "Player.h"
#include <Physics/Collide/Shape/Convex/Cylinder/hkpCylinderShape.h>

class Catapult : public StaticObject
{
private:
	Sensor* mSensor;
	bool mLaunchPlayer;
	bool reset;
	float mRadius;
public:
	Catapult(Ogre::Vector3 Pos, Physics * physics, Ogre::SceneManager * manager);
	~Catapult();
	void Update();
};
#endif