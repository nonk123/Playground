#ifndef EVENT_RECEIVER_HPP
#define EVENT_RECEIVER_HPP

#include "Game.hpp"

#include <string>

#include "irrlicht.h"

namespace Playground {
    class EventReceiver : public irr::IEventReceiver {
      private:
        Game& game;

      public:
        std::wstring key = L" ";

        EventReceiver(Game& game) : game(game) {
        }

        bool OnEvent(const irr::SEvent& event);
    };
} // namespace Playground

#endif
