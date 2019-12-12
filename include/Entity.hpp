#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "btBulletDynamicsCommon.h"
#include "irrlicht.h"

#include <memory>

#include "World.hpp"

namespace Playground::Game {
    class Entity {
        friend World;

      protected:
        World* world;
        irr::scene::ISceneNode* sceneNode;
        std::unique_ptr<btMotionState> motionState;
        std::unique_ptr<btRigidBody> body;

      public:
        Entity(btCollisionShape*, btScalar, btVector3, btVector3);

        virtual void update();

        virtual ~Entity();
    };
}

#endif
