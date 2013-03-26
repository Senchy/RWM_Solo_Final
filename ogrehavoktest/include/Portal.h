#ifndef PORTAL_H
#define PORTAL_H

#include "stdafx.h"
#include "StaticObject.h"

class Portal : public StaticObject
{
private:
public:
	Portal(Ogre::Vector3 Pos);
	~Portal();
};
#endif