#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <memory>

#include "btBulletDynamicsCommon.h"

#include "World.hpp"
#include "Entity.hpp"
#include "EventReceiver.hpp"

const int fps = 60;

namespace Playground {
    class Program {
        friend class EventReceiver;

      private:
        bool running;
        std::unique_ptr<Game::World> world;
        btCollisionShape* defaultCube;
        irr::scene::ICameraSceneNode* camera;
        irr::f32 cameraDistance = 15;

      public:
        Program() : running(true) {
        }

        void acceptInput(EventReceiver&);

        void rotateCameraBy(irr::f32, irr::f32);

        int run();

        ~Program() {
            delete defaultCube;
        }
    };
}

#endif
