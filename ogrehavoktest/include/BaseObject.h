#ifndef BASEOBJECT_H
#define BASEOBJECT_H
#include "stdafx.h"
#include "BaseApplication.h"
#include "Physics.h"
#include <sstream>

class BaseObject
{
protected:

	/// Object Variables
	Ogre::Vector3				mPosition;
	Ogre::Vector3				mSize;
	Ogre::Quaternion			mOrintation;

	/// World Variables
	Ogre::SceneManager*			mManager;
	Physics*					mPhysicsManager;


	/// Ogre Variables
	Ogre::Entity*				ObjectEnt;
	std::ostringstream			mStream;

public:
	hkpRigidBody*				Body;
	Ogre::SceneNode*			ObjectNode;
	BaseObject(Ogre::Vector3 position, Ogre::Vector3 size, Ogre::Quaternion orintation, Ogre::SceneManager* manager, Physics* physicsManager);
	virtual ~BaseObject();
};

static int ObjectNumber = 0;
#endif