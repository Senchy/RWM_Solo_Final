#ifndef Create_H
#define Create_H

#include "stdafx.h"
#include "DynamicObject.h"

class Create : public DynamicObject
{
private:
public:
	Create(Ogre::Vector3 Pos, Ogre::SceneManager* manager, Physics* physicsManager);
	void HitByLaser(Ogre::Vector3 &InHitPos_OutStartPos,Ogre::Vector3 &inPlaneNormal_OutLaserDir);
	virtual ~Create();
	virtual void Update();
	virtual void OnDeath();
};
#endif