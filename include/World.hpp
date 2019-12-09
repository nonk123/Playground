#ifndef WORLD_HPP
#define WORLD_HPP

#include "btBulletDynamicsCommon.h"
#include "irrlicht.h"

#include <map>
#include <memory>

namespace Playground::Game {
    class World;
    class Entity;
}

#include "Entity.hpp"

namespace Playground::Game {
    typedef unsigned long ID;

    class World {
      private:
        btDefaultCollisionConfiguration collisionConfiguration;
        btCollisionDispatcher dispatcher;
        btDbvtBroadphase broadphase;
        btSequentialImpulseConstraintSolver solver;
        btDiscreteDynamicsWorld world;

        irr::scene::ISceneManager& sceneManager;

        ID lastID;
        std::map<ID, std::unique_ptr<Entity>> entities;

      public:
        World(irr::scene::ISceneManager&);

        void update(const float);

        ID add(Entity*);
        ID add(Entity*, ID);

        void remove(Entity*);
        void remove(ID);
    };
}

#endif
