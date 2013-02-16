#include "stdafx.h"
#include "Mine.h"

Mine::Mine( Ogre::Vector3 position, Ogre::SceneManager* manager, Physics* physicsManager ) :
mPosition(position), mManager(manager), mPhysicsManager(physicsManager)
{
	std::string SceneName = "Mine";
	std::string EntityName = "MineEntity";

	const hkReal radius = 2.0f;
	const hkReal sphereMass = 100.0f;

	
	//set up physics properties of havok object
	hkpRigidBodyCinfo Mineinfo;//rigidbody class info; sets propertires of rigid body
	hkMassProperties massProperties;
	hkpInertiaTensorComputer::computeSphereVolumeMassProperties(
		radius, sphereMass, massProperties);

	hkpInertiaTensorComputer::computeSphereVolumeMassProperties( radius, sphereMass, massProperties );

	Mineinfo.m_mass = massProperties.m_mass;
	Mineinfo.m_centerOfMass  = massProperties.m_centerOfMass;
	Mineinfo.m_inertiaTensor = massProperties.m_inertiaTensor;
	Mineinfo.m_shape = new hkpSphereShape( radius );
	hkVector4 Hposition(mPosition.x,mPosition.y,mPosition.z);
	Mineinfo.m_position = Hposition;
	Mineinfo.m_motionType  = hkpMotion::MOTION_SPHERE_INERTIA;

	Mineinfo.m_qualityType = HK_COLLIDABLE_QUALITY_BULLET;//for fast objects

	Body = new hkpRigidBody( Mineinfo );
	
	Mineinfo.m_shape->removeReference();


	mPhysicsManager->GetPhysicsWorld()->addEntity( Body );

	// create corresponding ogre object (Head)
	mineEnt = mManager->createEntity(EntityName, "BallonMine.mesh");
	
	float r = mineEnt->getBoundingRadius();
	float scalefactor = 1.5 * radius/ r; //scale by desired radius, divide by actual radius

	mineEnt->setCastShadows(true);
	mineNode = 
		mManager->getRootSceneNode()->createChildSceneNode(SceneName);
    
	mineNode->setPosition(Hposition(0),Hposition(1),Hposition(2));
	mineNode->setScale(scalefactor,scalefactor,scalefactor);
	mineNode->attachObject(mineEnt);
}
void Mine::Update(){

	hkVector4 NewPosition;
	hkQuaternion NewAngle;

	NewPosition = Body->getPosition();

	Ogre::Vector3 pos(NewPosition(0),NewPosition(1),NewPosition(2));
	mineNode->setPosition(pos);

	NewAngle = Body->getRotation();

	Ogre::Radian angleRot(NewAngle.getAngle());
	hkVector4 axis(0,0,0);
	if(NewAngle.hasValidAxis())
		NewAngle.getAxis(axis); //get axis of rotaion from quaternion 

	Ogre::Vector3 axisRot(axis(0),axis(1),axis(2));
	Ogre::Quaternion newOgRot(angleRot,axisRot);

	mineNode->setOrientation(newOgRot); //rotate

}
Mine::~Mine(){
	Body->removeReference();
	mManager->destroyEntity(mineEnt);
	mManager->destroySceneNode(mineNode);
}