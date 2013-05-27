#include "stdafx.h"
#include "Catapult.h"

Catapult::Catapult(Ogre::Vector3 Pos, Physics * physics, Ogre::SceneManager * manager)
	:StaticObject(Pos,
					Ogre::Vector3(1, 1, 1),
					"barrel.mesh",
					physics,
					manager)
					,mRadius(30.0f)
					,mLaunchPlayer(false)
					,reset(false)
{
	hkpCylinderShape* BodyShape = new hkpCylinderShape(hkVector4(0,-5,0),hkVector4(0,5,0),mRadius);
	hkpRigidBodyCinfo						CatapultInfo;
	CatapultInfo.m_mass =						100.0f;
	hkMassProperties massProperties;
	hkpInertiaTensorComputer::computeCylinderVolumeMassProperties( hkVector4(0,-5,0),
																	hkVector4(0,5,0),
																	mRadius,
																	CatapultInfo.m_mass,
																	massProperties );
	CatapultInfo.m_mass =					massProperties.m_mass;
	CatapultInfo.m_centerOfMass =			massProperties.m_centerOfMass;
	CatapultInfo.m_inertiaTensor =			massProperties.m_inertiaTensor;
	CatapultInfo.m_solverDeactivation =		CatapultInfo.SOLVER_DEACTIVATION_MEDIUM;
	CatapultInfo.m_shape =					BodyShape;
	CatapultInfo.m_restitution =			0.0f;
	CatapultInfo.m_qualityType =			HK_COLLIDABLE_QUALITY_FIXED;
	CatapultInfo.m_motionType =				hkpMotion::MOTION_FIXED;
	CatapultInfo.m_rotation =				hkQuaternion(mOrintation.x, mOrintation.y, mOrintation.z, mOrintation.w);
	CatapultInfo.m_position = 				hkVector4(mPosition.x,mPosition.y,mPosition.z);
	Body =									new hkpRigidBody(CatapultInfo);
	Body->setUserData(hkUlong(this));
	mPhysicsManager->GetPhysicsWorld()->addEntity(Body);
	ObjectNode->setScale(Ogre::Vector3(1.8 * mRadius / ObjectEnt->getBoundingRadius(),
						1.5, 1.8 * mRadius / ObjectEnt->getBoundingRadius()));
		//Setup sensor
	hkAabb infoAABB;
	hkReal halfWidth = 5;
	hkReal boxHeight = 30;
	infoAABB.m_min.set( -halfWidth + Body->getPosition()(0), Body->getPosition()(1), -halfWidth + Body->getPosition()(2) );
	infoAABB.m_max.set( halfWidth + Body->getPosition()(0), Body->getPosition()(1) + boxHeight, halfWidth + Body->getPosition()(2) );
	mSensor = new Sensor( infoAABB, mManager );
	mPhysicsManager->GetPhysicsWorld()->addPhantom( mSensor );
}
void Catapult::Update()
{
	for (int i = 0; i < mSensor->getOverlappingCollidables().getSize(); i++ )
	{
		hkpRigidBody* body = hkpGetRigidBody(mSensor->getOverlappingCollidables()[i]);
		Player * thePlayer = (Player *)body->getUserData();

		 if(thePlayer != 0)
		 {
			thePlayer->Body->applyLinearImpulse(hkVector4(0.0f, 1000.0f, 0.0f));
			mLaunchPlayer =true;
		 }
	}
	if(mLaunchPlayer == true)
	{
		ObjectNode->setPosition(ObjectNode->getPosition().x,ObjectNode->getPosition().y + 1 ,ObjectNode->getPosition().z);
	}
	if(ObjectNode->getPosition().y > Body->getPosition()(1) + 10)
	{
		reset = true;
		mLaunchPlayer = false;
	}
	if(reset == true)
	{
		ObjectNode->setPosition(ObjectNode->getPosition().x,ObjectNode->getPosition().y - 0.5 ,ObjectNode->getPosition().z);
	}
	if(ObjectNode->getPosition().y < Body->getPosition()(1))
	{
		reset = false;
		ObjectNode->setPosition(Body->getPosition()(0),Body->getPosition()(1) ,Body->getPosition()(2));
	}
}
Catapult::~Catapult()
{
}