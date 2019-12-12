#ifndef EVENT_RECEIVER_HPP
#define EVENT_RECEIVER_HPP

#include "irrlicht.h"

namespace Playground {
    class EventReceiver : public irr::IEventReceiver {
      public:
        bool down[irr::KEY_KEY_CODES_COUNT];

        EventReceiver();

        bool OnEvent(const irr::SEvent&);
    };
} // namespace Playground

#endif
