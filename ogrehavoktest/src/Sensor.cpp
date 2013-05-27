#include "stdafx.h"
#include "Sensor.h"

int Sensor::sensorCount = 0;

Sensor::Sensor(const hkAabb& aabb, Ogre::SceneManager* pSceneMgr, hkUint32 collisionFilterInfo) 
: hkpAabbPhantom(aabb, collisionFilterInfo)
{
	Sensor::sensorCount++;
}

void Sensor::addOverlappingCollidable( hkpCollidable* c )
{
	hkpRigidBody* rb = hkpGetRigidBody(c);

	// Ignore other phantoms and fixed rigid bodies.
	if ( (rb != HK_NULL) && !rb->isFixed() )
	{
		hkpAabbPhantom::addOverlappingCollidable( c );
	} 
}

void Sensor::removeOverlappingCollidable( hkpCollidable* c )
{
	hkpRigidBody* rb = hkpGetRigidBody(c);

	// Ignore other phantoms and fixed rigid bodies.
	if ( (rb != HK_NULL) && !rb->isFixed() )
	{
		hkpAabbPhantom::removeOverlappingCollidable( c );
	}
}

Sensor::~Sensor() 
{

}