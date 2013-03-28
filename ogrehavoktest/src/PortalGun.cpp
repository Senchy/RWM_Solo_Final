#include "stdafx.h"
#include "PortalGun.h"

PortalGun::PortalGun(Ogre::SceneManager* manager, Physics* physicsManager, Ogre::Camera* camera)
	:BaseObject(Ogre::Vector3(0,0,0),
					Ogre::Vector3(0.018,0.018,0.08),
					Ogre::Quaternion(Ogre::Degree(-70),Ogre::Vector3(1,0,0)),
					manager,
					physicsManager), 
				mCamera(camera)
{
	Portals[0] = new Portal(Ogre::Vector3(1000,1000,1000));
	Portals[1] = new Portal(Ogre::Vector3(1000,1000,1000));

	////INIT Ogre Scene Names
	mStream << ObjectNumber;
	ObjectNumber++;
	std::string SceneName = "PortalGunObject";
	std::string EntityName = "PortalGunEntity";
	SceneName += mStream.str();
	EntityName += mStream.str();
	
	//mPhysicsManager->GetPhysicsWorld()->castRay(
	////INIT Ogre Scene Object
	ObjectEnt = mManager->createEntity(EntityName, "cube.mesh");
	ObjectEnt->setCastShadows(false);
	ObjectNode = mManager->getRootSceneNode()->createChildSceneNode(SceneName);
	ObjectNode->setPosition(mPosition);
	ObjectNode->setOrientation(mOrintation);
	ObjectNode->setScale(mSize);
	ObjectNode->attachObject(ObjectEnt);
}
PortalGun::~PortalGun()
{
}
void PortalGun::Update()
{
	Ogre::Vector3 mGunOffset = mCamera->getDirection().normalisedCopy();/*
	Ogre::Radian SavedYaw = mCamera->getOrientation().getYaw();
	Ogre::Radian SavedPitch = mCamera->getOrientation().getPitch();*/
	mPosition = Ogre::Vector3(mCamera->getPosition().x + (mGunOffset.x * 12), mCamera->getPosition().y + (mGunOffset.y * 12) - 4, mCamera->getPosition().z + (mGunOffset.z * 12));
	ObjectNode->setOrientation(mCamera->getOrientation());
	//if(SavedPitch < Ogre::Radian(Ogre::Degree(-35)))
	//{
	//	mCamera->setOrientation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(-35)), Ogre::Vector3(1,0,0)));
	//	mCamera->yaw(SavedYaw);
	//}
	//else if(SavedPitch > Ogre::Radian(Ogre::Degree(45)))
	//{
	//	mCamera->setOrientation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(45)), Ogre::Vector3(1,0,0)));
	//	mCamera->yaw(SavedYaw);
	//}
	ObjectNode->setPosition(mPosition);
}