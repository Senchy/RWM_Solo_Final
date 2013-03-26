#ifndef NONEINTERACTIVEFLOOR_H
#define NONEINTERACTIVEFLOOR_H

#include "stdafx.h"
#include "Floor.h"

class NoneInteractiveFloor : public Floor
{
private:
public:
	NoneInteractiveFloor(Ogre::Vector3 Pos);
	~NoneInteractiveFloor();
};
#endif