#include "stdafx.h"
#include "LaserReceptor.h"

LaserReceptor::LaserReceptor(Ogre::Vector3 PosStart,Ogre::Vector3 direction,Ogre::SceneManager* manager, Physics* physicsManager)
	:StaticObject(PosStart, 
					Ogre::Vector3(1,1,1), 
					"cube.mesh", 
					physicsManager,
					manager)
{

}
LaserReceptor::~LaserReceptor()
{
}