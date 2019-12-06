#include "EventReceiver.hpp"

#include <iostream>

using namespace Playground;

bool EventReceiver::OnEvent(const irr::SEvent &event) {
    if (event.EventType != irr::EET_KEY_INPUT_EVENT && event.KeyInput.PressedDown)
        return false;

    if (event.KeyInput.Key == irr::KEY_KEY_Q)
        game.running = false;

    key = std::wstring(1, event.KeyInput.Char);

    std::wcout << key;
    std::wcout.flush();

    return true;
}
