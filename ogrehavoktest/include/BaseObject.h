#ifndef BASEOBJECT_H
#define BASEOBJECT_H
#include "stdafx.h"
#include "BaseApplication.h"
#include "Physics.h"

class BaseObject
{
protected:
	bool Alive;
	Ogre::Vector3 mPosition;
public:
	BaseObject();
	~BaseObject();
	virtual void Update();
	virtual void OnDeath();
};
#endif