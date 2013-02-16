#ifndef BASEOBJECT_H
#define BASEOBJECT_H
#include "stdafx.h"
#include "BaseApplication.h"
#include"Physics.h"

using namespace Ogre;

class BaseObject
{
protected:
public:
	virtual void Update() = 0;
};
#endif