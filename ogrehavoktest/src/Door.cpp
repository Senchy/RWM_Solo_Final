#include "stdafx.h"
#include "Door.h"

Door::Door(Ogre::Vector3 Pos,Physics * physics, Ogre::SceneManager * manager, float rotation)
	: StaticObject(Pos,
					Ogre::Vector3(60.0f, 80.0f, 10.0f),
					"cube.mesh",
					physics,
					manager)
					,mIter(0)
					,mOpen(true)
{
	mOrintation = Ogre::Quaternion(Ogre::Radian(Ogre::Degree(rotation)), Ogre::Vector3(0,1,0));
	hkVector4 HalfSize( mSize.x / 2.0, mSize.y / 2.0, mSize.z / 2.0);
	hkpBoxShape* Hbox =						new hkpBoxShape(HalfSize,0);
	Hbox->setRadius(0.0f);
	
	hkpRigidBodyCinfo						DoorInfo;
	DoorInfo.m_mass =						100.0f;
	hkMassProperties massProperties;
	hkpInertiaTensorComputer::computeBoxVolumeMassProperties(
		HalfSize, DoorInfo.m_mass, massProperties);
	DoorInfo.m_mass =						massProperties.m_mass;
	DoorInfo.m_centerOfMass =				massProperties.m_centerOfMass;
	DoorInfo.m_inertiaTensor =				massProperties.m_inertiaTensor;
	DoorInfo.m_solverDeactivation =			DoorInfo.SOLVER_DEACTIVATION_MEDIUM;
	DoorInfo.m_shape =						Hbox;
	DoorInfo.m_restitution =				0.0f;
	DoorInfo.m_qualityType =				HK_COLLIDABLE_QUALITY_FIXED;
	DoorInfo.m_motionType =					hkpMotion::MOTION_FIXED;
	DoorInfo.m_rotation =					hkQuaternion(mOrintation.x, mOrintation.y, mOrintation.z, mOrintation.w);
	DoorInfo.m_position = 					hkVector4(mPosition.x,mPosition.y,mPosition.z);
	Body =									new hkpRigidBody(DoorInfo);
	Body->setUserData(hkUlong(this));
	mPhysicsManager->GetPhysicsWorld()->addEntity(Body);
	ObjectNode->setScale(mSize.x / ObjectEnt->getBoundingBox().getSize().x,
		mSize.y / ObjectEnt->getBoundingBox().getSize().y, mSize.z / ObjectEnt->getBoundingBox().getSize().z);
	ObjectNode->setPosition(Ogre::Vector3(Body->getPosition()(0), Body->getPosition()(1),Body->getPosition()(2)));
	ObjectEnt->setMaterialName("Examples/RustySteel");
	hkQuaternion GetBodyAngle = Body->getRotation();
	hkVector4 GetrotationAxis(0,0,0);
	if(GetBodyAngle.hasValidAxis())
	{
		GetBodyAngle.getAxis(GetrotationAxis);
	}
	Ogre::Quaternion UpdateOrintation(Ogre::Radian(GetBodyAngle.getAngle()), Ogre::Vector3(GetrotationAxis(0),GetrotationAxis(1),GetrotationAxis(2)));
	ObjectNode->setOrientation(UpdateOrintation);
}
void Door::Update()
{
	if(mOpen)
	{
		if(mIter < 160)
		{
			Body->setPosition(hkVector4( Body->getPosition()(0), Body->getPosition()(1) + 0.5, Body->getPosition()(2)));
			ObjectNode->setPosition(Ogre::Vector3(Body->getPosition()(0), Body->getPosition()(1),Body->getPosition()(2)));
			mIter++;
		}
	}
}
void Door::OpenDoor()
{
	mOpen = true;
}
Door::~Door()
{
}