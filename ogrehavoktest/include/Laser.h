#ifndef LASER_H
#define LASER_H

#include "stdafx.h"
#include "DynamicObject.h"

class Laser : public DynamicObject
{
private:
public:
	Laser(Ogre::Vector3 Pos);
	~Laser();
};
#endif