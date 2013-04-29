#include "stdafx.h"
#include "Create.h"

Create::Create(Ogre::Vector3 Pos, Ogre::SceneManager* manager, Physics* physicsManager)
	:	DynamicObject( Pos,
						"cube.mesh",
						Ogre::Vector3(20.0,20.0,20.0),
						Ogre::Quaternion( Ogre::Radian(0), Ogre::Vector3(0,1,0)),
						manager,
						physicsManager )
{
	hkVector4 HalfSize( mSize.x / 2.0, mSize.y / 2.0, mSize.z / 2.0);
	hkpBoxShape* Hbox =						new hkpBoxShape(HalfSize,0);
	Hbox->setRadius(0.0f);
	
	hkpRigidBodyCinfo						CreateInfo;
	CreateInfo.m_mass =						100.0f;
	hkMassProperties massProperties;
	hkpInertiaTensorComputer::computeBoxVolumeMassProperties(
		HalfSize, CreateInfo.m_mass, massProperties);
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
	Body->setUserData(3);
	mPhysicsManager->GetPhysicsWorld()->addEntity(Body);
	ObjectNode->setScale(mSize.x / ObjectEnt->getBoundingBox().getSize().x,
		mSize.y / ObjectEnt->getBoundingBox().getSize().y, mSize.z / ObjectEnt->getBoundingBox().getSize().z);
	ObjectNode->setPosition(Ogre::Vector3(Body->getPosition()(0), Body->getPosition()(1),Body->getPosition()(2)));
}
Create::~Create()
{
}
void Create::Update()
{
	DynamicObject::Update();
}

void Create::OnDeath()
{
}