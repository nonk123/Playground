#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "btBulletDynamicsCommon.h"
#include "irrlicht.h"

#include <memory>

#include "Shapes.hpp"
#include "World.hpp"

namespace Playground::Game {
    class Entity {
        friend World;

      protected:
        World* world;
        std::unique_ptr<btMotionState> motionState;
        std::shared_ptr<btCollisionShape> shape;
        std::unique_ptr<btRigidBody> body;

        std::shared_ptr<irr::scene::IMesh> mesh;
        irr::scene::ISceneNode* sceneNode;

      public:
        Entity(ShapePair, btVector3);

        void applyImpulse(btVector3 impulse) {
            body->applyCentralImpulse(impulse);
        }

        virtual void update();

        virtual ~Entity() {
        }
    };
}

#endif
