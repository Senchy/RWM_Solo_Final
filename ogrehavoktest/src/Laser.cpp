#include "stdafx.h"
#include "Laser.h"


Laser::Laser(Ogre::Vector3 Pos, Ogre::Vector3 Direction,Ogre::SceneManager* manager, Physics* physicsManager)
	:DynamicObject(Pos,
					"Barrel.mesh",  
					Ogre::Vector3(1,1,1),
					Ogre::Quaternion( Ogre::Radian(0), Ogre::Vector3(0,1,0)),
					manager,
					physicsManager),
					mDirection(Direction),
					mScaleOffset(4.066)
{
	
	
	Ogre::Vector3 src = ObjectNode->getOrientation() * Ogre::Vector3::UNIT_Y;
	Ogre::Quaternion quat = src.getRotationTo(mDirection);  
	ObjectNode->rotate(quat); 
	ObjectEnt->setMaterialName("Examples/WaterStream");
	mRay.m_from = hkVector4(mPosition.x,mPosition.y,mPosition.z);
    mRay.m_to = hkVector4(mPosition.x + (mDirection.x * 1000),
							mPosition.y + (mDirection.y * 1000),
							mPosition.z + (mDirection.z * 1000));
}
Laser::~Laser()
{
}
void Laser::Update()
{
	hkpWorldRayCastOutput OutPut;
	mPhysicsManager->GetPhysicsWorld()->castRay(mRay,OutPut);
	float hitScale = (OutPut.m_hitFraction * 1000.0/mScaleOffset);
	ObjectNode->setPosition(mPosition + (mDirection * hitScale));
	ObjectNode->setScale(0.2,hitScale,0.2);
}