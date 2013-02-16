#ifndef MINE_H
#define MINE_H
#include "stdafx.h"
#include "BaseObject.h"
#include <sstream>

class Mine: public BaseObject
{
public:
	Mine( Ogre::Vector3 position, Ogre::SceneManager* manager, Physics* physicsManager );
	~Mine();
	virtual void Update();
private:

	Ogre::Vector3 mPosition;
	Ogre::SceneManager* mManager;
	Physics* mPhysicsManager;
	hkpRigidBody* Body;
	Ogre::SceneNode* mineNode;
	Ogre::Entity* mineEnt;
};
#endif