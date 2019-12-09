#include "EventReceiver.hpp"

#include <functional>

using namespace Playground;

bool EventReceiver::OnEvent(const irr::SEvent &event) {
    if (event.EventType != irr::EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown)
        return false;

    if (event.KeyInput.Key == irr::KEY_KEY_Q)
        game.running = false;

    if (event.KeyInput.Key == irr::KEY_KEY_C) {
        static std::function<btScalar()> fun = []() {
            const int limit = 31;
            return static_cast<btScalar>(std::rand() % limit) / 10;
        };

        game.world->add(new Game::Entity(game.defaultCube, 0.5f,
                                         {0, 7.5, 0},
                                         {fun(), fun(), fun()}));
    }

    return true;
}
