#ifndef BOX_H
#define BOX_H

#include "stdafx.h"
#include "DynamicObject.h"

class Box : public DynamicObject
{
private:
public:
	Box(Ogre::Vector3 Pos);
	~Box();
};
#endif