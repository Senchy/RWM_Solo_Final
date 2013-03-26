#include "stdafx.h"
#include "PortalGun.h"

PortalGun::PortalGun(Ogre::Vector3 position, Ogre::Vector3 size, Ogre::Quaternion orintation, Ogre::SceneManager* manager, Physics* physicsManager, Ogre::Camera* camera)
	:BaseObject(position,
					size,
					orintation,
					manager,
					physicsManager), 
				mCamera(camera)
{
	Portals[0] = new Portal(position);
	Portals[1] = new Portal(position);

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
	ObjectNode = mManager->getRootSceneNode()->createChildSceneNode(SceneName);
	ObjectNode->setPosition(mPosition);
	ObjectNode->attachObject(ObjectEnt);
}
PortalGun::~PortalGun()
{
}
void PortalGun::Update()
{
}