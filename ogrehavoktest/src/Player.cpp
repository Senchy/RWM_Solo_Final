#include "stdafx.h"
#include "Player.h"

Player::Player(Ogre::Vector3 position, Ogre::SceneManager* manager, Physics* physicsManager, OIS::Keyboard * Keyboard, Ogre::Camera* camera, OIS::Mouse* Mouse )
	:	DynamicObject(	position, 
						"sphere.mesh", 
						Ogre::Vector3(2.0,2.0,2.0),
						Ogre::Quaternion( Ogre::Radian(0), Ogre::Vector3(0,1,0)),
						manager, 
						physicsManager),
		mKeyboard(Keyboard), 
		mMouse(Mouse),
		mCamera(camera),
		mJumpForce(1000.0f),
		mCameraOffset(40),
		mFireTimeOut(200),
		mMoveTimeOut(30),
		mPickUpTimeOut(30),
		mSpeed(20),
		mBOX(NULL),
		IsOnGround(true),
		HoldingObject(false)
{
	mGun = new PortalGun(mManager,mPhysicsManager,mCamera);
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
	Body->setUserData(0);
	ObjectInfo.m_shape->removeReference();

	mPhysicsManager->GetPhysicsWorld()->addEntity( Body );
	ObjectNode->setScale(Ogre::Vector3(1.8 * radius / ObjectEnt->getBoundingRadius(),
						1.8 * radius / ObjectEnt->getBoundingRadius(), 1.8 * radius / ObjectEnt->getBoundingRadius()));

	PlayerCollision* CollisionListener =	new PlayerCollision();
	Body->addContactListener(CollisionListener);
}
void Player::INITPortalGun(Portal* portals[])
{
	mGun->SetPortals(portals);
}
Player::~Player()
{
}
void Player::Update()
{
	DynamicObject::Update();
	mGun->Update();
	CheckIfOnGround();
	Ogre::Vector3 MoveDir = mCamera->getDirection();
	MoveDir = Ogre::Vector3(MoveDir.x,0, MoveDir.z);
	MoveDir = MoveDir.normalisedCopy();
	if(IsOnGround == true)
	{
		if (mKeyboard->isKeyDown(OIS::KC_W))
		{
			Body->setLinearVelocity(hkVector4(MoveDir.x * mSpeed, Body->getLinearVelocity()(1), MoveDir.z * mSpeed));
		}
		else if (mKeyboard->isKeyDown(OIS::KC_S))
		{	
			Body->setLinearVelocity(hkVector4(-MoveDir.x * mSpeed, Body->getLinearVelocity()(1), -MoveDir.z * mSpeed));
		}
		if (mKeyboard->isKeyDown(OIS::KC_A))
		{	
			Body->setLinearVelocity(hkVector4( MoveDir.z * mSpeed, Body->getLinearVelocity()(1),-MoveDir.x * mSpeed));
		}
		else if (mKeyboard->isKeyDown(OIS::KC_D))
		{	
			Body->setLinearVelocity(hkVector4(- MoveDir.z * mSpeed, Body->getLinearVelocity()(1),MoveDir.x * mSpeed));
		}
		if (!mKeyboard->isKeyDown(OIS::KC_W) && !mKeyboard->isKeyDown(OIS::KC_S) 
		 && !mKeyboard->isKeyDown(OIS::KC_A) && !mKeyboard->isKeyDown(OIS::KC_D))
		{	
			Body->setLinearVelocity( hkVector4(0, Body->getLinearVelocity()(1), 0));
		}
		if (mKeyboard->isKeyDown(OIS::KC_SPACE))
		{
			Body->applyForce(0.3, hkVector4(0, mJumpForce, 0));
			IsOnGround = false;
		}
	}
	else
	{
		if(mMoveTimeOut > 10)
		{
			if (mKeyboard->isKeyDown(OIS::KC_W))
			{
				Body->applyLinearImpulse(hkVector4(MoveDir.x * 18, 0, MoveDir.z * 18));
			}
			else if (mKeyboard->isKeyDown(OIS::KC_S))
			{	
				Body->applyLinearImpulse(hkVector4(-MoveDir.x * 18,0, -MoveDir.z * 18));
			}
			if (mKeyboard->isKeyDown(OIS::KC_A))
			{	
				Body->applyLinearImpulse(hkVector4( MoveDir.z * 18,0,-MoveDir.x * 18));
			}
			else if (mKeyboard->isKeyDown(OIS::KC_D))
			{	
				Body->applyLinearImpulse(hkVector4(- MoveDir.z * 18, 0,MoveDir.x * 18));
			}
		}
	}
	if(mKeyboard->isKeyDown(OIS::KC_RSHIFT) || mKeyboard->isKeyDown(OIS::KC_LSHIFT))
	{
		mSpeed = 36;
	}
	else
	{
		mSpeed = 24;
	}
	if(HoldingObject == true)
	{
		if(mPickUpTimeOut > 30)
		{
			if(mKeyboard->isKeyDown(OIS::KC_E))
			{
				HoldingObject = false;
				mPickUpTimeOut = 0;
			}
		}
	}
	else
	{
		if(mPickUpTimeOut > 30)
		{
			if(mKeyboard->isKeyDown(OIS::KC_E))
			{
				HoldingObject = CheckIfPickUpOBject();
				if(HoldingObject){ mPickUpTimeOut = 0; }
			}
		}
	}
	if(HoldingObject)
	{
		mBOX->setPosition(hkVector4(mCamera->getPosition().x + mCamera->getDirection().x * 60,
									mCamera->getPosition().y + mCamera->getDirection().y * 60,
									mCamera->getPosition().z + mCamera->getDirection().z * 60));
	}
	if(mMouse->getMouseState().buttonDown(OIS::MB_Left))
	{
		if(mFireTimeOut > 60)
		{
			mGun->ShootGun(1);
			mFireTimeOut = 0;
		}
	}
	if(mMouse->getMouseState().buttonDown(OIS::MB_Right))
	{
		if(mFireTimeOut > 60)
		{
			mGun->ShootGun(0);
			mFireTimeOut = 0;
		}
	}
	mCamera->setPosition(Ogre::Vector3(ObjectNode->getPosition().x, ObjectNode->getPosition().y + mCameraOffset, ObjectNode->getPosition().z));
	mMoveTimeOut++;
	mFireTimeOut++;
	mPickUpTimeOut++;
}
void Player::CheckIfOnGround()
{
	hkpWorldRayCastInput ray;
	ray.m_from = hkVector4(ObjectNode->getPosition().x,ObjectNode->getPosition().y- 5,ObjectNode->getPosition().z);
    ray.m_to = hkVector4(ObjectNode->getPosition().x,ObjectNode->getPosition().y - 12,ObjectNode->getPosition().z);
	hkpWorldRayCastOutput OutPut;
	mPhysicsManager->GetPhysicsWorld()->castRay(ray,OutPut);
	if(OutPut.m_hitFraction < 1.0f)
	{
		IsOnGround = true;
	}
	else
	{
		IsOnGround = false;
	}

}
bool Player::CheckIfPickUpOBject()
{
	hkpWorldRayCastInput ray;
	ray.m_from = hkVector4(mCamera->getPosition().x + mCamera->getDirection().x * 10,
							mCamera->getPosition().y + mCamera->getDirection().y * 10,
							mCamera->getPosition().z + mCamera->getDirection().z * 10);
    ray.m_to = hkVector4(mCamera->getPosition().x + mCamera->getDirection().x * 100,
						mCamera->getPosition().y + mCamera->getDirection().y  * 100,
						mCamera->getPosition().z + mCamera->getDirection().z * 100);
	hkpWorldRayCastOutput OutPut;
	mPhysicsManager->GetPhysicsWorld()->castRay(ray,OutPut);
	if(OutPut.hasHit())
	{
		const hkpCollidable* col = OutPut.m_rootCollidable;
		hkpRigidBody* body = hkpGetRigidBody(col);

		if(body->getUserData() == 3)
		{
			mBOX = body;
			return true;
		}

	}
	return false;
}
void Player::OnDeath()
{
}