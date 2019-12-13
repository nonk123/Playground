#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <memory>

#include "btBulletDynamicsCommon.h"

#include "World.hpp"
#include "Entity.hpp"
#include "EventReceiver.hpp"
#include "Shapes.hpp"

const int fps = 60;

namespace Playground {
    class Program {
        friend class EventReceiver;

      private:
        bool running;

        std::unique_ptr<Game::World> world;

        irr::scene::ICameraSceneNode* camera;
        irr::f32 cameraDistance = 15;

      public:
        Program() : running(true) {
        }

        void acceptInput(EventReceiver&, ShapeCreator&);

        void rotateCameraBy(irr::f32, irr::f32);

        int run();

        ~Program() {
        }
    };
}

#endif
