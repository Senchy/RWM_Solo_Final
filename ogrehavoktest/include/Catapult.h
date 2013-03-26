#ifndef CATAPULT_H
#define CATAPULT_H

#include "stdafx.h"
#include "DynamicObject.h"

class Catapult : public DynamicObject
{
private:
public:
	Catapult(Ogre::Vector3 Pos);
	~Catapult();
};
#endif