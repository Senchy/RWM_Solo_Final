#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include "stdafx.h"
#include "BaseObject.h"

class StaticObject : public BaseObject
{
protected:

public:
	StaticObject(Ogre::Vector3 Pos, Ogre::Vector3 size, std::string meshname, Physics * physics, Ogre::SceneManager * manager);
	virtual ~StaticObject();
};
#endif