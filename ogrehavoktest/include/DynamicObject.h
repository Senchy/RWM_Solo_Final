#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H

#include "stdafx.h"
#include "BaseObject.h"

class DynamicObject : public BaseObject
{
protected:
	Ogre::Vector3				mVelocity;
public:
	DynamicObject(Ogre::Vector3 position,std::string Mesh, Ogre::Vector3 size, Ogre::Quaternion orintation, Ogre::SceneManager* manager, Physics* physicsManager);
	virtual ~DynamicObject();
	virtual void Update();
	virtual void OnDeath();
};

#endif