#ifndef SENSOR_H
#define SENSOR_H


#include "stdafx.h"
#include "BaseApplication.h"
#include "Physics.h"
#include "Physics/Dynamics/Phantom/hkpAabbPhantom.h"

class Sensor : public hkpAabbPhantom
{
	
public:
	static int sensorCount;
	Sensor(const hkAabb& aabb, Ogre::SceneManager* pSceneMgr, hkUint32 collisionFilterInfo = 0);
	Sensor();
	~Sensor();

	// Callback implementation
	virtual void addOverlappingCollidable( hkpCollidable* handle );

	// Callback implementation 
	virtual void removeOverlappingCollidable( hkpCollidable* handle );

};

#endif