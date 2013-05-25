#ifndef TESTC_H
#define TESTC_H

#include "stdafx.h"
#include "DynamicObject.h"
#include <Physics/Collide/Shape/Convex/Cylinder/hkpCylinderShape.h>

class TestC : public DynamicObject
{
private:
public:
	TestC(Ogre::Vector3 Pos, Ogre::SceneManager* manager, Physics* physicsManager);
	virtual ~TestC();
	virtual void Update();
	virtual void OnDeath();
};
#endif