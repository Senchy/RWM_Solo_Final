#ifndef TURRET_H
#define TURRET_H

#include "stdafx.h"
#include "DynamicObject.h"

class Turret : public DynamicObject
{
private:
	Ogre::Vector3 StaringDirection;
public:
	Turret(Ogre::Vector3 Pos, Ogre::SceneManager* manager, Physics* physicsManager);
	~Turret();
	virtual void Update();
	virtual void OnDeath();
};
#endif