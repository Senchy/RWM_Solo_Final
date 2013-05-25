#ifndef PORTAL_H
#define PORTAL_H

#include "stdafx.h"
#include "StaticObject.h"
#include "DynamicObject.h"
#include <Physics/Collide/Shape/Convex/Cylinder/hkpCylinderShape.h>
#include "Physics\Dynamics\Collide\ContactListener\hkpContactListener.h"

class Portal : public StaticObject, public hkReferencedObject, public hkpContactListener
{
private:
	bool					mActive;
	Portal*					mOtherPortal;
	Ogre::Vector3			mDirection;
	hkReal					mRadius;
public:
	Portal(Ogre::Vector3 Pos, Physics * physics, Ogre::SceneManager * manager);
	void SetPosition(Ogre::Vector3 Pos, Ogre::Vector3 WallNormal);
	bool SetPlayerOnContact(Ogre::Vector3 &Pos, Ogre::Vector3 &Velocity, Ogre::Quaternion &Direction);
	bool Transport(Ogre::Vector3 &Pos, Ogre::Vector3 &Velocity, Ogre::Quaternion &Direction);
	void SetOtherPortal(Portal* portal);
	void SetColor(std::string meshname);
	~Portal();
};
class PortalCollision : public hkReferencedObject, public hkpContactListener
{
public:
	virtual void contactPointCallback( const hkpContactPointEvent& event )
	{
		DynamicObject* a = 0;
		DynamicObject* b = 0;
		a = dynamic_cast<DynamicObject*> ((BaseObject *)event.m_bodies[0]->getUserData());
		b = dynamic_cast<DynamicObject*> ((BaseObject *)event.m_bodies[1]->getUserData());
		Ogre::Quaternion cameradir;
		Ogre::Vector3 Pos;
		Ogre::Vector3 Vel;
		if(a != 0)
		{
			Pos = a->ObjectNode->getPosition();
			Vel = Ogre::Vector3(a->Body->getLinearVelocity()(0),
				a->Body->getLinearVelocity()(1),
				a->Body->getLinearVelocity()(2));
		}
		else if(b != 0)
		{
			Pos = b->ObjectNode->getPosition();
			Vel = Ogre::Vector3(b->Body->getLinearVelocity()(0),
				b->Body->getLinearVelocity()(1),
				b->Body->getLinearVelocity()(2));
		}
		if(a != 0)
		{
			Portal * portal = 0;
 			portal = dynamic_cast<Portal*> ((BaseObject *)event.m_bodies[1]->getUserData());
			if(portal != 0)
			{
				if(portal->SetPlayerOnContact(Pos, Vel, cameradir))
				{
					a->Body->setPosition(hkVector4(Pos.x, Pos.y, Pos.z));
					a->Body->setLinearVelocity(hkVector4(Vel.x, Vel.y, Vel.z));
				}
			}
		}
		else if(b != 0)
		{
			Portal * portal = 0;
			portal = dynamic_cast<Portal*> ((BaseObject *)event.m_bodies[0]->getUserData());
			if(portal != 0)
			{
				if(portal->SetPlayerOnContact(Pos, Vel, cameradir))
				{
					b->Body->setPosition(hkVector4(Pos.x, Pos.y, Pos.z));
					b->Body->setLinearVelocity(hkVector4(Vel.x, Vel.y, Vel.z));
				}
			}
		}
	}
};
static int PortalNumber = 0;
#endif