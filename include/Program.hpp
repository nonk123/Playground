#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <memory>

#include "btBulletDynamicsCommon.h"

#include "World.hpp"
#include "Entity.hpp"

const int fps = 60;

namespace Playground {
    class Program {
        friend class EventReceiver;

      private:
        bool running;
        std::unique_ptr<Game::World> world;
        btCollisionShape* defaultCube;

      public:
        Program() : running(true) {
        }

        int run();

        ~Program() {
            delete defaultCube;
        }
    };
}

#endif
