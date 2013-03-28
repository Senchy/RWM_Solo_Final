#include "stdafx.h"
#include "DynamicObject.h"

DynamicObject::DynamicObject(Ogre::Vector3 position, std::string Mesh,  Ogre::Vector3 size, Ogre::Quaternion orintation, Ogre::SceneManager* manager, Physics* physicsManager)
	: BaseObject(position, size, orintation, manager, physicsManager)
{
	////INIT Ogre Scene Names
	mStream << ObjectNumber;
	ObjectNumber++;
	std::string SceneName = "DynamicObject";
	std::string EntityName = "DynamicObjectEntity";
	SceneName += mStream.str();
	EntityName += mStream.str();

	////INIT Ogre Scene Object

	ObjectEnt = mManager->createEntity(EntityName, Mesh);
	ObjectEnt->setCastShadows(false);
	ObjectNode = mManager->getRootSceneNode()->createChildSceneNode(SceneName);
	ObjectNode->setPosition(mPosition);
	ObjectNode->setOrientation(orintation);
	ObjectNode->attachObject(ObjectEnt);
}

DynamicObject::~DynamicObject()
{
	Body->removeReference();
	mManager->destroyEntity(ObjectEnt);
	mManager->destroySceneNode(ObjectNode);
}

void DynamicObject::Update()
{
	ObjectNode->setPosition(Ogre::Vector3(Body->getPosition()(0), Body->getPosition()(1),Body->getPosition()(2)));
	hkQuaternion GetBodyAngle = Body->getRotation();
	hkVector4 GetrotationAxis(0,0,0);
	if(GetBodyAngle.hasValidAxis())
	{
		GetBodyAngle.getAxis(GetrotationAxis);
	}
	Ogre::Quaternion UpdateOrintation(Ogre::Radian(GetBodyAngle.getAngle()), Ogre::Vector3(GetrotationAxis(0),GetrotationAxis(1),GetrotationAxis(2)));
	ObjectNode->setOrientation(UpdateOrintation);
}

void DynamicObject::OnDeath()
{
}
