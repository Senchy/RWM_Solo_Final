#ifndef PLAYER_H
#define PLAYER_H

#include "stdafx.h"
#include "DynamicObject.h"
#include "Physics\Dynamics\Collide\ContactListener\hkpContactListener.h"

class Player :	public DynamicObject
{
private:
	Ogre::Camera*			mCamera;
	OIS::Keyboard *			mKeyboard;
	float					mSpeed;
	hkReal					mJumpForce;
	float					mCameraOffset;
public:
	bool					IsOnGround;
	Player(Ogre::Vector3 position, Ogre::SceneManager* manager, Physics* physicsManager,OIS::Keyboard * Keyboard, Ogre::Camera* camera );
	virtual ~Player();
	virtual void Update();
	virtual void OnDeath();
};
class PlayerCollision : public hkReferencedObject, public hkpContactListener
{
public:
	virtual void contactPointCallback( const hkpContactPointEvent& event )
	{
		BaseObject * CollisionObject = 0;
		Player * thePlayer = 0;

		thePlayer = dynamic_cast<Player*> ((BaseObject *)event.m_bodies[0]->getUserData());
		CollisionObject = dynamic_cast<BaseObject*> ((BaseObject *)event.m_bodies[1]->getUserData());
		if(CollisionObject == 0)
		{
			thePlayer = dynamic_cast<Player*> ((BaseObject *)event.m_bodies[1]->getUserData());
			CollisionObject = dynamic_cast<BaseObject*> ((BaseObject *)event.m_bodies[0]->getUserData());
		}
		if(thePlayer != 0)
		{
			thePlayer->IsOnGround = true;
		}
	}
};
#endif