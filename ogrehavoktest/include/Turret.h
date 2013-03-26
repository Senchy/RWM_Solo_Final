#ifndef TURRET_H
#define TURRET_H

#include "stdafx.h"
#include "DynamicObject.h"

class Turret : public DynamicObject
{
private:
public:
	Turret(Ogre::Vector3 Pos);
	~Turret();
};
#endif