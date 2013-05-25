#include "stdafx.h"
#include "TestC.h"

TestC::TestC(Ogre::Vector3 Pos, Ogre::SceneManager* manager, Physics* physicsManager)
	:	DynamicObject( Pos,
						"barrel.mesh",
						Ogre::Vector3(20.0,20.0,20.0),
						Ogre::Quaternion( Ogre::Radian(0), Ogre::Vector3(0,1,0)),
						manager,
						physicsManager )
{
	hkpCylinderShape* Hbox =						new hkpCylinderShape(hkVector4(0,5,0),hkVector4(0,-5,0),10);
	Hbox->setRadius(0.0f);

	hkpRigidBodyCinfo						CreateInfo;
	CreateInfo.m_mass =						100.0f;
	hkMassProperties massProperties;
	hkpInertiaTensorComputer::computeCylinderVolumeMassProperties(
		hkVector4(0,5,0),hkVector4(0,-5,0),10, CreateInfo.m_mass, massProperties);
	CreateInfo.m_mass =						massProperties.m_mass;
	CreateInfo.m_centerOfMass =				massProperties.m_centerOfMass;
	CreateInfo.m_inertiaTensor =			massProperties.m_inertiaTensor;
	CreateInfo.m_solverDeactivation =		CreateInfo.SOLVER_DEACTIVATION_MEDIUM;
	CreateInfo.m_shape =					Hbox;
	CreateInfo.m_restitution =				0.0f;
	CreateInfo.m_qualityType =				HK_COLLIDABLE_QUALITY_MOVING;
	CreateInfo.m_motionType =				hkpMotion::MOTION_BOX_INERTIA;
	CreateInfo.m_rotation =					hkQuaternion(mOrintation.x, mOrintation.y, mOrintation.z, mOrintation.w);
	CreateInfo.m_position = 				hkVector4(mPosition.x,mPosition.y,mPosition.z);
	Body =									new hkpRigidBody(CreateInfo);
	Body->setUserData(hkUlong(this));
	mPhysicsManager->GetPhysicsWorld()->addEntity(Body);
	ObjectNode->setScale(mSize.x / ObjectEnt->getBoundingBox().getSize().x,
		mSize.y / ObjectEnt->getBoundingBox().getSize().y, mSize.z / ObjectEnt->getBoundingBox().getSize().z);
	ObjectNode->setPosition(Ogre::Vector3(Body->getPosition()(0), Body->getPosition()(1),Body->getPosition()(2)));
}
TestC::~TestC()
{
}
void TestC::Update()
{
	DynamicObject::Update();
}

void TestC::OnDeath()
{
}