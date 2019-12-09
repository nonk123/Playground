#ifndef EVENT_RECEIVER_HPP
#define EVENT_RECEIVER_HPP

#include "Program.hpp"

#include <string>

#include "irrlicht.h"

namespace Playground {
    class EventReceiver : public irr::IEventReceiver {
      private:
        Program& game;

      public:
        std::wstring key = L" ";

        EventReceiver(Program& game) : game(game) {
        }

        bool OnEvent(const irr::SEvent& event);
    };
} // namespace Playground

#endif
