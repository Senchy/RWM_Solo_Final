#include "stdafx.h"
#include "Portal.h"


Portal::Portal(Ogre::Vector3 Pos,Physics * physics, Ogre::SceneManager * manager)
	: StaticObject( Pos, Ogre::Vector3(1,1,1), "barrel.mesh", physics, manager),
		mActive(false),
		mOtherPortal(NULL)
{
	const hkReal radius =					20.0f;
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
	ObjectInfo.m_motionType  =				hkpMotion::MOTION_FIXED;
	ObjectInfo.m_restitution =				0.1;
	ObjectInfo.m_qualityType =				HK_COLLIDABLE_QUALITY_FIXED;//for fast objects
	Body =									new hkpRigidBody( ObjectInfo );
	
	ObjectEnt->setMaterialName("Examples/WaterStream");
	ObjectInfo.m_shape->removeReference();
	ObjectNode->setScale(Ogre::Vector3(2.6 * radius / ObjectEnt->getBoundingRadius(),
						0.6, 1.8 * radius / ObjectEnt->getBoundingRadius()));
	mPhysicsManager->GetPhysicsWorld()->addEntity( Body );
}

void Portal::SetOtherPortal(Portal* portal)
{
	mOtherPortal = portal;
}
void Portal::Transport(Ogre::Vector3 &Pos, Ogre::Vector3 &Velocity, float Size)
{
	if(mOtherPortal != NULL)
	{
		if(Velocity.normalisedCopy().directionEquals(-mDirection, Ogre::Degree(20)))
		{
			mOtherPortal->SetPlayerOnContact(Pos, Velocity, Size);
		}
	}
	Pos = Ogre::Vector3(-1000,-1000,-1000);
}
void Portal::SetColor(std::string meshname)
{
	ObjectEnt->setMaterialName(meshname);
}
void Portal::SetPosition(Ogre::Vector3 Pos, Ogre::Vector3 WallNormal)
{
	Body->setPosition(hkVector4(Pos.x,Pos.y, Pos.z));
	ObjectNode->setPosition(Ogre::Vector3(Body->getPosition()(0), Body->getPosition()(1),Body->getPosition()(2)));
	ObjectNode->setOrientation(1,WallNormal.z,WallNormal.y,-WallNormal.x);
	mDirection = ObjectNode->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
	mActive = true;
}
void Portal::SetPlayerOnContact(Ogre::Vector3 &Pos, Ogre::Vector3 &Velocity, float Size)
{
	if(Velocity.length() > 3)
	{
		Pos = mPosition + (mDirection * Size);
		Velocity = mDirection * Velocity.length();
	}
	Pos = Ogre::Vector3(-1000,-1000,-1000);
}
Portal::~Portal()
{
}