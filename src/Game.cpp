#include "Game.hpp"

#include <iostream>

#include "btBulletDynamicsCommon.h"
#include "irrlicht.h"

#include "EventReceiver.hpp"
#include "IrrPtr.hpp"

#include "config.hpp"

using namespace Playground;

int Game::run() {
    using namespace irr;
    using namespace video;
    using namespace scene;
    using namespace gui;
    using namespace core;

    E_DRIVER_TYPE driverType = PLAYGROUND_DRIVER;

    EventReceiver eventReceiver(*this);

    Utils::IrrPtr<irr::IrrlichtDevice> device(createDevice(driverType,
            dimension2du(800, 600), 32, false, false, false, &eventReceiver));

    if (!device)
        return 1;

    device->setWindowCaption(L"Playground");

    ISceneManager* sceneManager = device->getSceneManager();
    IVideoDriver* driver = device->getVideoDriver();
    IGUIEnvironment* guiEnv = device->getGUIEnvironment();

    auto text = guiEnv->addStaticText(L"Test", {0, 0, 100, 20}, true, false);

    while (running && device->run()) {
        text->setText(eventReceiver.key.c_str());

        driver->beginScene(true, true, {255, 127, 127, 127});
        {
            sceneManager->drawAll();
            guiEnv->drawAll();
        }
        driver->endScene();

        device->yield();
    }

    std::cout << std::endl;

    return 0;
}
