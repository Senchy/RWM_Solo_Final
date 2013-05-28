#ifndef TURRET_H
#define TURRET_H

#include "stdafx.h"
#include "DynamicObject.h"
#include "Player.h"

class Turret : public DynamicObject
{
private:
	Ogre::Vector3			mPlayerPos;
	hkReal					mRotateValue;
	hkReal					mChangeInRotation;
	bool					mPlayerInSight;
	int						mKillTimer;
public:
	bool					mShutdown;
	Turret(Ogre::Vector3 Pos, Ogre::SceneManager* manager, Physics* physicsManager);
	~Turret();
	void SetPlayerPos(Ogre::Vector3 PlayerPos);
	virtual void Update();
	virtual void OnDeath();
};
#endif