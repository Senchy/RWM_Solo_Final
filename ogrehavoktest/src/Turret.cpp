#include "stdafx.h"
#include "Turret.h"

Turret::Turret(Ogre::Vector3 Pos, Ogre::SceneManager* manager, Physics* physicsManager)
		:	DynamicObject( Pos,
						"cube.mesh",
						Ogre::Vector3(20.0,50.0,20.0),
						Ogre::Quaternion( Ogre::Radian(0), Ogre::Vector3(0,1,0)),
						manager,
						physicsManager )
{
	hkVector4 HalfSize( mSize.x / 2.0, mSize.y / 2.0, mSize.z / 2.0);
	hkpBoxShape* Hbox =						new hkpBoxShape(HalfSize,0);
	Hbox->setRadius(0.0f);
	
	hkpRigidBodyCinfo						TurretInfo;
	TurretInfo.m_mass =						5000.0f;
	hkMassProperties massProperties;
	hkpInertiaTensorComputer::computeBoxVolumeMassProperties(
		HalfSize, TurretInfo.m_mass, massProperties);
	TurretInfo.m_mass =						massProperties.m_mass;
	TurretInfo.m_centerOfMass =				hkVector4(massProperties.m_centerOfMass(0),massProperties.m_centerOfMass(1) - 20,massProperties.m_centerOfMass(2));
	TurretInfo.m_inertiaTensor =			massProperties.m_inertiaTensor;
	TurretInfo.m_solverDeactivation =		TurretInfo.SOLVER_DEACTIVATION_MEDIUM;
	TurretInfo.m_shape =					Hbox;
	TurretInfo.m_restitution =				0.0f;
	TurretInfo.m_qualityType =				HK_COLLIDABLE_QUALITY_MOVING;
	TurretInfo.m_motionType =				hkpMotion::MOTION_BOX_INERTIA;
	TurretInfo.m_rotation =					hkQuaternion(mOrintation.x, mOrintation.y, mOrintation.z, mOrintation.w);
	TurretInfo.m_position = 				hkVector4(mPosition.x,mPosition.y,mPosition.z);
	Body =									new hkpRigidBody(TurretInfo);
	Body->setUserData(hkUlong(this));
	StaringDirection = mOrintation * Ogre::Vector3::UNIT_X;
	mPhysicsManager->GetPhysicsWorld()->addEntity(Body);
	ObjectNode->setScale(mSize.x / ObjectEnt->getBoundingBox().getSize().x,
		mSize.y / ObjectEnt->getBoundingBox().getSize().y, mSize.z / ObjectEnt->getBoundingBox().getSize().z);
	ObjectNode->setPosition(Ogre::Vector3(Body->getPosition()(0), Body->getPosition()(1),Body->getPosition()(2)));
}
Turret::~Turret()
{
}
void Turret::Update()
{
	DynamicObject::Update();
}
void Turret::OnDeath()
{
}