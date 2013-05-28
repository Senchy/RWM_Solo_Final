#include "stdafx.h"
#include "LaserReceptor.h"

LaserReceptor::LaserReceptor(Ogre::Vector3 PosStart,Ogre::Vector3 direction,Ogre::SceneManager* manager, Physics* physicsManager)
	:StaticObject(PosStart, 
					Ogre::Vector3(20,20,20), 
					"cube.mesh", 
					physicsManager,
					manager),
			mHit(false)
{
	hkVector4 HalfSize( mSize.x / 2.0, mSize.y / 2.0, mSize.z / 2.0);
	hkpBoxShape* Hbox =						new hkpBoxShape(HalfSize,0);
	Hbox->setRadius(0.0f);

	hkpRigidBodyCinfo						FloorInfo;
	FloorInfo.m_mass =						100.0f;
	hkMassProperties massProperties;
	hkpInertiaTensorComputer::computeBoxVolumeMassProperties(
		HalfSize, FloorInfo.m_mass, massProperties);
	FloorInfo.m_mass =						massProperties.m_mass;
	FloorInfo.m_centerOfMass =				massProperties.m_centerOfMass;
	FloorInfo.m_inertiaTensor =				massProperties.m_inertiaTensor;
	FloorInfo.m_solverDeactivation =		FloorInfo.SOLVER_DEACTIVATION_MEDIUM;
	FloorInfo.m_shape =						Hbox;
	FloorInfo.m_restitution =				0.0f;
	FloorInfo.m_qualityType =				HK_COLLIDABLE_QUALITY_FIXED;
	FloorInfo.m_motionType =				hkpMotion::MOTION_FIXED;
	FloorInfo.m_rotation =					hkQuaternion(mOrintation.x, mOrintation.y, mOrintation.z, mOrintation.w);
	FloorInfo.m_position = 					hkVector4(mPosition.x,mPosition.y,mPosition.z);
	Body =									new hkpRigidBody(FloorInfo);
	Body->setUserData(hkUlong(this));
	mPhysicsManager->GetPhysicsWorld()->addEntity(Body);
	ObjectNode->setScale(mSize.x / ObjectEnt->getBoundingBox().getSize().x,
		mSize.y / ObjectEnt->getBoundingBox().getSize().y, mSize.z / ObjectEnt->getBoundingBox().getSize().z);
	ObjectEnt->setMaterialName("Examples/BeachStones");
	ObjectNode->setPosition(Ogre::Vector3(Body->getPosition()(0), Body->getPosition()(1),Body->getPosition()(2)));
	hkQuaternion GetBodyAngle = Body->getRotation();
	hkVector4 GetrotationAxis(0,0,0);
	if(GetBodyAngle.hasValidAxis())
	{
		GetBodyAngle.getAxis(GetrotationAxis);
	}
	Ogre::Quaternion UpdateOrintation(Ogre::Radian(GetBodyAngle.getAngle()), Ogre::Vector3(GetrotationAxis(0),GetrotationAxis(1),GetrotationAxis(2)));
}
bool LaserReceptor::IsHit()
{
	return mHit;
}
void LaserReceptor::Hit()
{
	mHit = true;
}
LaserReceptor::~LaserReceptor()
{
}