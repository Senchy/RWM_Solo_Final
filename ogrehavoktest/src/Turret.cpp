#include "stdafx.h"
#include "Turret.h"

Turret::Turret(Ogre::Vector3 Pos, Ogre::SceneManager* manager, Physics* physicsManager)
		:	DynamicObject( Pos,
						"cube.mesh",
						Ogre::Vector3(20.0,50.0,20.0),
						Ogre::Quaternion( Ogre::Radian(0), Ogre::Vector3(0,1,0)),
						manager,
						physicsManager )
				,mRotateValue(0)
				,mChangeInRotation(0.001)
				,mKillTimer(0)
				,mShutdown(false)
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
	
	bool PlayerInRoom = false;
	DynamicObject::Update();
	hkpWorldRayCastOutput	OutPut;
	hkpWorldRayCastInput	Ray;
	Player* theplayer = 0;
	Ogre::Vector3 RayDirection = (mPlayerPos - mPosition).normalisedCopy();
	Ray.m_from = hkVector4(mPosition.x + (RayDirection.x * 25)
						,mPosition.y + (RayDirection.y * 25)
						,mPosition.z + (RayDirection.z * 25));
    Ray.m_to = hkVector4(mPlayerPos.x, mPlayerPos.y, mPlayerPos.z);
	mPhysicsManager->GetPhysicsWorld()->castRay(Ray,OutPut);
	if(OutPut.hasHit())
	{
		const hkpCollidable* col = OutPut.m_rootCollidable;
		hkpRigidBody* body = hkpGetRigidBody(col);
		theplayer = dynamic_cast<Player*> ((BaseObject *)body->getUserData());
		if(theplayer != 0)
		{
			PlayerInRoom = true;
		}
		else
		{
			mPlayerInSight = false;
			mKillTimer = 0;
		}
	}
	Ogre::Vector3 NewDir = Ogre::Vector3(RayDirection.x,0,RayDirection.z);
	NewDir.normalise();
	Ogre::Radian angle = NewDir.angleBetween(ObjectNode->getOrientation() * Ogre::Vector3::UNIT_X);
	if(PlayerInRoom || !mPlayerInSight)
	{
		if(angle.valueDegrees() < 20 || angle.valueDegrees() > -20)
		{
			mPlayerInSight = true;
		}
	}
	if(mPlayerInSight)
	{
		mRotateValue += angle.valueRadians();
		Body->setRotation(hkQuaternion(hkVector4(0,1,0),mRotateValue));
		mKillTimer++;
		if(mKillTimer > 100)
		{
			mShutdown = true;
			//theplayer->OnDeath();
		}
	}
	else
	{
		if(mRotateValue < -2)
		{
			mChangeInRotation = 0.001;
		}
		else if (mRotateValue > 2)
		{
			mChangeInRotation = -0.001;
		}
		mRotateValue += mChangeInRotation;
		Body->setRotation(hkQuaternion(hkVector4(0,1,0),mRotateValue));
	}
}
void Turret::SetPlayerPos(Ogre::Vector3 PlayerPos)
{
	mPlayerPos = PlayerPos;
}
void Turret::OnDeath()
{
}