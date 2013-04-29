#ifndef Create_H
#define Create_H

#include "stdafx.h"
#include "DynamicObject.h"

class Create : public DynamicObject
{
private:
public:
	Create(Ogre::Vector3 Pos, Ogre::SceneManager* manager, Physics* physicsManager);
	virtual ~Create();
	virtual void Update();
	virtual void OnDeath();
};
#endif