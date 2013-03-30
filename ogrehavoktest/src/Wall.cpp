#include "stdafx.h"
#include "Wall.h"

Wall::Wall(Ogre::Vector3 Pos, Ogre::Vector3 size,Physics * physics, Ogre::SceneManager * manager, float rotation)
	: StaticObject(Pos,
					Ogre::Vector3(size.x, size.y, 20.0f),
					"cube.mesh",
					physics,
					manager)
{
	mOrintation = Ogre::Quaternion(Ogre::Radian(Ogre::Degree(rotation)), Ogre::Vector3(0,1,0));
	hkVector4 HalfSize( mSize.x / 2.0, mSize.y / 2.0, mSize.z / 2.0);
	hkpBoxShape* Hbox =						new hkpBoxShape(HalfSize,0);
	Hbox->setRadius(0.0f);
	
	hkpRigidBodyCinfo						WallInfo;
	WallInfo.m_mass =						100.0f;
	hkMassProperties massProperties;
	hkpInertiaTensorComputer::computeBoxVolumeMassProperties(
		HalfSize, WallInfo.m_mass, massProperties);
	WallInfo.m_mass =						massProperties.m_mass;
	WallInfo.m_centerOfMass =				massProperties.m_centerOfMass;
	WallInfo.m_inertiaTensor =				massProperties.m_inertiaTensor;
	WallInfo.m_solverDeactivation =			WallInfo.SOLVER_DEACTIVATION_MEDIUM;
	WallInfo.m_shape =						Hbox;
	WallInfo.m_restitution =				0.0f;
	WallInfo.m_qualityType =				HK_COLLIDABLE_QUALITY_FIXED;
	WallInfo.m_motionType =					hkpMotion::MOTION_FIXED;
	WallInfo.m_rotation =					hkQuaternion(mOrintation.x, mOrintation.y, mOrintation.z, mOrintation.w);
	WallInfo.m_position = 					hkVector4(mPosition.x,mPosition.y,mPosition.z);
	Body =									new hkpRigidBody(WallInfo);
	Body->setUserData(2);
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
Wall::~Wall()
{
}