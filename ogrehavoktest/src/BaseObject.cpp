#include "stdafx.h"
#include "BaseObject.h"

BaseObject::BaseObject(Ogre::Vector3 position, Ogre::Vector3 size, Ogre::Quaternion orintation, Ogre::SceneManager* manager, Physics* physicsManager)
	:	mPosition(position),
		mSize(size),
		mOrintation(orintation),
		mManager(manager),
		mPhysicsManager(physicsManager)
		,Body(0)
{
}
BaseObject::~BaseObject()
{
	if(Body != 0)
	{
		Body->removeReference();
	}
}