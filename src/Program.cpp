#include "Program.hpp"

#include <iostream>
#include <ctime>

#include "btBulletDynamicsCommon.h"
#include "irrlicht.h"

#include "EventReceiver.hpp"

#include "config.hpp"

using namespace Playground;

int Program::run() {
    std::srand(std::time(nullptr));

    using namespace irr;
    using namespace video;
    using namespace scene;
    using namespace gui;
    using namespace core;

    using namespace Game;

    E_DRIVER_TYPE driverType = PLAYGROUND_DRIVER;

    EventReceiver eventReceiver(*this);

    IrrlichtDevice* device = createDevice(driverType,
            dimension2du(800, 600), 32, false, false, false, &eventReceiver);

    if (!device)
        return 1;

    device->setWindowCaption(L"Playground");

    ISceneManager* sceneManager = device->getSceneManager();
    IVideoDriver* driver = device->getVideoDriver();
    IGUIEnvironment* gui = device->getGUIEnvironment();

    gui->addStaticText(L"q to quit, c to add more cubes", {0, 0, 200, 20}, true);

    this->world = std::make_unique<World>(*sceneManager);

    this->defaultCube = new btBoxShape(btVector3(1, 1, 1));

    world->add(new Entity(new btBoxShape({10, 0.05, 10}), 0, {0, 0, 0}, {0, 0, 0}));

    sceneManager->addCameraSceneNode(nullptr, {1.25, 1.25, 15}, {0, 0, 0});

    const float timestep = 1.0f / 60;

    while (running && device->run()) {
        world->update(timestep);

        driver->beginScene(true, true, {255, 127, 127, 127});
        {
            sceneManager->drawAll();
            gui->drawAll();
        }
        driver->endScene();

        device->yield();
    }

    device->drop();

    return 0;
}
