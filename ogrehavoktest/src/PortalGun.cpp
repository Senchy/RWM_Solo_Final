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
	////INIT Ogre Scene Names
	mStream << ObjectNumber;
	ObjectNumber++;
	std::string SceneName = "PortalGunObject";
	std::string EntityName = "PortalGunEntity";
	SceneName += mStream.str();
	EntityName += mStream.str();
	
	////INIT Ogre Scene Object
	ObjectEnt = mManager->createEntity(EntityName, "cube.mesh");
	ObjectEnt->setCastShadows(false);
	ObjectNode = mManager->getRootSceneNode()->createChildSceneNode(SceneName);
	ObjectNode->setPosition(mPosition);
	ObjectNode->setOrientation(mOrintation);
	ObjectNode->setScale(mSize);
	ObjectNode->attachObject(ObjectEnt);
}
void PortalGun::SetPortals(Portal* portals[])
{
	mPortals[0] = portals[0];
	mPortals[1] = portals[1];
	mPortals[0]->SetOtherPortal(mPortals[1]);
	mPortals[1]->SetOtherPortal(mPortals[0]);
}
PortalGun::~PortalGun()
{
}
void PortalGun::Update()
{
	Ogre::Vector3 GunOffset = mCamera->getDirection().normalisedCopy();
	Ogre::Vector3 DownOffset = mCamera->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Y;
	mPosition = Ogre::Vector3(mCamera->getPosition().x + (GunOffset.x * 10) + (DownOffset.x * 4), mCamera->getPosition().y + (GunOffset.y * 10)  + (DownOffset.y * 4), mCamera->getPosition().z + (GunOffset.z * 10) + (DownOffset.z * 4));
	ObjectNode->setOrientation(mCamera->getOrientation());
	ObjectNode->setPosition(mPosition);
}
bool PortalGun::ShootGun(int WhichPortal)
{
	hkpWorldRayCastInput ray;
	ray.m_from =  hkVector4(mCamera->getPosition().x + mCamera->getDirection().x * 50,
							mCamera->getPosition().y + mCamera->getDirection().y * 50, 
							mCamera->getPosition().z + mCamera->getDirection().z * 50);
    ray.m_to = hkVector4(mCamera->getPosition().x + mCamera->getDirection().x * 2050,
						mCamera->getPosition().y + mCamera->getDirection().y  * 2050,
						mCamera->getPosition().z + mCamera->getDirection().z * 2050);
	hkpWorldRayCastOutput OutPut;
	mPhysicsManager->GetPhysicsWorld()->castRay(ray,OutPut);
	if(OutPut.m_hitFraction < 1.0f)
	{
		const hkpCollidable* col = OutPut.m_rootCollidable;
		hkpRigidBody* body = hkpGetRigidBody(col);
		InteractiveWall* TryWall = 0;
		InteractiveFloor* TryFloor = 0;
		TryWall = dynamic_cast<InteractiveWall*> ((BaseObject *)body->getUserData());
		TryFloor = dynamic_cast<InteractiveFloor*> ((BaseObject *)body->getUserData());
		if(TryFloor !=0 || TryWall != 0)
		{
			mPortals[WhichPortal]->SetPosition(Ogre::Vector3(mCamera->getPosition().x + (mCamera->getDirection().x * 50) + (mCamera->getDirection().x *( 2000 * OutPut.m_hitFraction)) ,
													mCamera->getPosition().y + (mCamera->getDirection().y * 50) + (mCamera->getDirection().y *( 2000 * OutPut.m_hitFraction))  ,
													mCamera->getPosition().z + (mCamera->getDirection().z * 50) + (mCamera->getDirection().z *( 2000 * OutPut.m_hitFraction))),
										Ogre::Vector3(OutPut.m_normal(0),OutPut.m_normal(1),OutPut.m_normal(2)));
			return true;
		}
	}
	return false;
}