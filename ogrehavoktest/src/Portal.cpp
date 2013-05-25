#include "stdafx.h"
#include "Portal.h"


Portal::Portal(Ogre::Vector3 Pos,Physics * physics, Ogre::SceneManager * manager)
	: StaticObject( Pos, Ogre::Vector3(1,1,1), "barrel.mesh", physics, manager),
		mActive(false),
		mOtherPortal(NULL),
		mRadius(22.0f)
{
	if(PortalNumber == 1)
	{
		ObjectEnt->setMaterialName("Template/Red");
	}
	else
	{
		ObjectEnt->setMaterialName("Template/Red");
	}
	hkpCylinderShape* BodyShape = new hkpCylinderShape(hkVector4(0,-0.3,0),hkVector4(0,0.3,0),24.0f);
	hkpRigidBodyCinfo						PortalInfo;
	PortalInfo.m_mass =						100.0f;
	hkMassProperties massProperties;
	hkpInertiaTensorComputer::computeCylinderVolumeMassProperties( hkVector4(0,-0.3,0),
																	hkVector4(0,0.3,0),
																	24.0f,
																	PortalInfo.m_mass,
																	massProperties );
	PortalInfo.m_mass =						massProperties.m_mass;
	PortalInfo.m_centerOfMass =				massProperties.m_centerOfMass;
	PortalInfo.m_inertiaTensor =			massProperties.m_inertiaTensor;
	PortalInfo.m_solverDeactivation =		PortalInfo.SOLVER_DEACTIVATION_MEDIUM;
	PortalInfo.m_shape =					BodyShape;
	PortalInfo.m_restitution =				0.0f;
	PortalInfo.m_qualityType =				HK_COLLIDABLE_QUALITY_FIXED;
	PortalInfo.m_motionType =				hkpMotion::MOTION_FIXED;
	PortalInfo.m_rotation =					hkQuaternion(mOrintation.x, mOrintation.y, mOrintation.z, mOrintation.w);
	PortalInfo.m_position = 				hkVector4(mPosition.x,mPosition.y,mPosition.z);
	Body =									new hkpRigidBody(PortalInfo);
	Body->setUserData(hkUlong(this));
	mPhysicsManager->GetPhysicsWorld()->addEntity(Body);
	PortalNumber++;
	PortalCollision* colRes = new PortalCollision();
	Body->addContactListener(colRes);
	ObjectNode->setScale(Ogre::Vector3(2.6 * mRadius / ObjectEnt->getBoundingRadius(),
						0.6, 1.8 * mRadius / ObjectEnt->getBoundingRadius()));
}

void Portal::SetOtherPortal(Portal* portal)
{
	mOtherPortal = portal;
}
void Portal::SetColor(std::string meshname)
{
	ObjectEnt->setMaterialName(meshname);
}
void Portal::SetPosition(Ogre::Vector3 Pos, Ogre::Vector3 WallNormal)
{
	mPosition = Pos;
	ObjectNode->setPosition(Pos);
	ObjectNode->setOrientation(1,WallNormal.z,WallNormal.y,-WallNormal.x);
	mDirection = ObjectNode->getOrientation() * Ogre::Vector3::UNIT_Y;
	Body->setPosition(hkVector4(Pos.x, Pos.y, Pos.z));
	Body->setRotation(hkQuaternion(ObjectNode->getOrientation().x,	ObjectNode->getOrientation().y,
									ObjectNode->getOrientation().z,	ObjectNode->getOrientation().w	));
	if(WallNormal.y == -1)
	{
		mDirection.y *=-1;
	}
	mActive = true;
}
bool Portal::SetPlayerOnContact(Ogre::Vector3 &Pos, Ogre::Vector3 &Velocity, Ogre::Quaternion &Direction)
{
	Ogre::Vector3 Distance = mPosition - Pos;
	if(mOtherPortal != NULL)
	{
		if(Velocity.normalisedCopy().directionEquals(-mDirection, Ogre::Degree(30)))
		{
			return mOtherPortal->Transport(Pos,Velocity,Direction);
		}
		else if(mDirection.y > 0.7)
		{
			return mOtherPortal->Transport(Pos,Ogre::Vector3(0,0.2,0),Direction);
		}
	}
	return false;
}
bool Portal::Transport(Ogre::Vector3 &Pos, Ogre::Vector3 &Velocity, Ogre::Quaternion &Direction)
{
	
	if(Velocity.length() > 0.2)
	{
		if(mDirection.y < -0.7)
		{
			Pos = mPosition + (mDirection * (3 * mRadius));
		}
		else
		{
			Pos = mPosition + (mDirection * mRadius);
		}
		Velocity = mDirection * Velocity.length();
		return true;
	}
	return false;
}
Portal::~Portal()
{
}
