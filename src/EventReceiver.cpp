#include "EventReceiver.hpp"

using namespace Playground;

EventReceiver::EventReceiver() {
    for (irr::u32 code = 0; code < irr::KEY_KEY_CODES_COUNT; code++)
        down[code] = false;
}

bool EventReceiver::OnEvent(const irr::SEvent &event) {
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        down[event.KeyInput.Key] = event.KeyInput.PressedDown;

    return false;
}
