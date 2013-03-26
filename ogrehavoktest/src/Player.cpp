#include "stdafx.h"
#include "Player.h"

Player::Player(Ogre::Vector3 position, Ogre::SceneManager* manager, Physics* physicsManager, OIS::Keyboard * Keyboard, Ogre::Camera* camera )
	:	DynamicObject(	position, 
						"sphere.mesh", 
						Ogre::Vector3(2.0,2.0,2.0),
						Ogre::Quaternion( Ogre::Radian(0), Ogre::Vector3(0,1,0)),
						manager, 
						physicsManager),
		mKeyboard(Keyboard), 
		mCamera(camera),
		mJumpForce(1000.0f),
		mCameraOffset(40),
		IsOnGround(true)
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

	mPhysicsManager->GetPhysicsWorld()->addEntity( Body );
	ObjectNode->setScale(Ogre::Vector3(1.8 * radius / ObjectEnt->getBoundingRadius(),
						1.8 * radius / ObjectEnt->getBoundingRadius(), 1.8 * radius / ObjectEnt->getBoundingRadius()));

	PlayerCollision* CollisionListener =	new PlayerCollision();
	Body->addContactListener(CollisionListener);
}
Player::~Player()
{
}
void Player::Update()
{
	DynamicObject::Update();
	Ogre::Vector3 MoveDir = mCamera->getDirection();
	MoveDir = Ogre::Vector3(MoveDir.x,0, MoveDir.z);
	MoveDir = MoveDir.normalisedCopy();
	if (mKeyboard->isKeyDown(OIS::KC_W))
	{
		Body->setLinearVelocity(hkVector4(MoveDir.x * 50, Body->getLinearVelocity()(1), MoveDir.z * 50));
	}
	else if (mKeyboard->isKeyDown(OIS::KC_S))
	{	
		Body->setLinearVelocity(hkVector4(-MoveDir.x * 50, Body->getLinearVelocity()(1), -MoveDir.z * 50));
	}
	if (mKeyboard->isKeyDown(OIS::KC_A))
	{	
		Body->setLinearVelocity(hkVector4( MoveDir.z * 50, Body->getLinearVelocity()(1),-MoveDir.x * 50));
	}
	else if (mKeyboard->isKeyDown(OIS::KC_D))
	{	
		Body->setLinearVelocity(hkVector4(- MoveDir.z * 50, Body->getLinearVelocity()(1),MoveDir.x * 50));
	}
	if (!mKeyboard->isKeyDown(OIS::KC_W) && !mKeyboard->isKeyDown(OIS::KC_S) 
	 && !mKeyboard->isKeyDown(OIS::KC_A) && !mKeyboard->isKeyDown(OIS::KC_D))
	{	
		Body->setLinearVelocity( hkVector4(0, Body->getLinearVelocity()(1), 0));
	}
	if(IsOnGround == false)
	{
		if (mKeyboard->isKeyDown(OIS::KC_SPACE))
		{
			Body->applyForce(0.3, hkVector4(0, mJumpForce, 0));
			IsOnGround = false;
		}
	}
	mCamera->setPosition(Ogre::Vector3(ObjectNode->getPosition().x, ObjectNode->getPosition().y + mCameraOffset, ObjectNode->getPosition().z));
}
void Player::OnDeath()
{
}