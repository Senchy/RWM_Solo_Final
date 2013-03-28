#include "stdafx.h"
#include "Portal.h"


Portal::Portal(Ogre::Vector3 Pos,Physics * physics, Ogre::SceneManager * manager)
	: StaticObject( Pos, Ogre::Vector3(1,1,1), "barrel.mesh", physics, manager),
		mActive(false),
		mOtherPortal(NULL)
{
	const hkReal radius =					10.0f;
	const hkReal sphereMass =				200.0f;
	hkpRigidBodyCinfo						ObjectInfo;
	hkMassProperties						massProperties;
	hkpInertiaTensorComputer::computeSphereVolumeMassProperties(
		radius, sphereMass, massProperties);

	ObjectInfo.m_mass =						massProperties.m_mass;
	ObjectInfo.m_centerOfMass  =			massProperties.m_centerOfMass;
	ObjectInfo.m_inertiaTensor =			massProperties.m_inertiaTensor;
	ObjectInfo.m_shape =					new hkpSphereShape( radius );
	hkVector4 Hposition(mPosition.x,mPosition.y,mPosition.z);
	ObjectInfo.m_position =					Hposition;
	ObjectInfo.m_motionType  =				hkpMotion::MOTION_SPHERE_INERTIA;
	ObjectInfo.m_restitution =				0.1;
	ObjectInfo.m_qualityType =				HK_COLLIDABLE_QUALITY_BULLET;//for fast objects
	Body =									new hkpRigidBody( ObjectInfo );

	ObjectInfo.m_shape->removeReference();
	ObjectNode->setScale(Ogre::Vector3(1.8 * radius / ObjectEnt->getBoundingRadius(),
						0.4, 1.8 * radius / ObjectEnt->getBoundingRadius()));
	mPhysicsManager->GetPhysicsWorld()->addEntity( Body );
}

void Portal::SetOtherPortal(Portal* portal)
{
	mOtherPortal = portal;
}
Ogre::Vector3 Portal::Transport(Ogre::Vector3 Pos, Ogre::Vector3 Velocity, float Size)
{
	if(mOtherPortal != NULL)
	{
		if(Velocity.normalisedCopy().directionEquals(-mDirection, Ogre::Degree(20)))
		{
			return mOtherPortal->SetPlayerOnContact(Pos, Velocity, Size);
		}
	}
	return Ogre::Vector3(-1000,-1000,-1000);
}

void Portal::SetPosition(Ogre::Vector3 Pos, Ogre::Vector3 WallNormal)
{
	ObjectNode->setPosition(Pos);
	ObjectNode->setDirection(WallNormal);
	mDirection = ObjectNode->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
	mActive = true;
}
Ogre::Vector3 Portal::SetPlayerOnContact(Ogre::Vector3 Pos, Ogre::Vector3 Velocity, float Size)
{
	if(Velocity.length() > 3)
	{
		return(mPosition + (mDirection * Size));
	}
	return Ogre::Vector3(-1000,-1000,-1000);
}
Portal::~Portal()
{
}