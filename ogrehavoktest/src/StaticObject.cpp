#include "stdafx.h"
#include "StaticObject.h"

StaticObject::StaticObject(Ogre::Vector3 Pos, Ogre::Vector3 size,  std::string meshname, Physics * physics, Ogre::SceneManager * manager)
	: BaseObject(Pos,
				size,
				Ogre::Quaternion(Ogre::Radian(0),Ogre::Vector3(0,1,0)),
				manager, 
				physics)
{
	////INIT Ogre Scene Names
	mStream << ObjectNumber;
	ObjectNumber++;
	std::string SceneName = "StaticObject";
	std::string EntityName = "StaticObjectEntity";
	SceneName += mStream.str();
	EntityName += mStream.str();
	
	////INIT Ogre Scene Object
	ObjectEnt = mManager->createEntity(EntityName, meshname);
	ObjectNode = mManager->getRootSceneNode()->createChildSceneNode(SceneName);
	ObjectNode->setPosition(mPosition);
	ObjectNode->setOrientation(mOrintation);
	ObjectNode->attachObject(ObjectEnt);
}

StaticObject::~StaticObject()
{
	Body->removeReference();
	mManager->destroyEntity(ObjectEnt);
	mManager->destroySceneNode(ObjectNode);
}