#include "Program.hpp"

#include <ctime>
#include <algorithm>

#include "btBulletDynamicsCommon.h"
#include "irrlicht.h"

#include "Math.hpp"

#include "config.hpp"

using namespace Playground;

btScalar velocity() {
    static const int limit = 31;

    btScalar val = static_cast<btScalar>(std::rand() % limit) / 10;
    return std::rand() % 2 ? val : -val;
}

void Program::acceptInput(EventReceiver& receiver) {
    if (receiver.down[irr::KEY_KEY_Q])
        running = false;

    if (receiver.down[irr::KEY_KEY_C]) {
         world->add(new Game::Entity(defaultCube,
                                     0.5f,
                                     {0, 7.5, 0},
                                     {velocity(), velocity(), velocity()}));
         receiver.down[irr::KEY_KEY_C] = false;
    }

    static const irr::f32 delta = Utils::pi<irr::f32> / 32;

    if (receiver.down[irr::KEY_KEY_W])
        rotateCameraBy(delta, 0);

    if (receiver.down[irr::KEY_KEY_S])
        rotateCameraBy(-delta, 0);

    if (receiver.down[irr::KEY_KEY_A])
        rotateCameraBy(0, delta);

    if (receiver.down[irr::KEY_KEY_D])
        rotateCameraBy(0, -delta);

    static const irr::f32 increment = 0.375;

    if (receiver.down[irr::KEY_KEY_R]) {
        cameraDistance -= increment;
        rotateCameraBy(0, 0);
    }

    if (receiver.down[irr::KEY_KEY_F]) {
        cameraDistance += increment;
        rotateCameraBy(0, 0);
    }
}

void Program::rotateCameraBy(irr::f32 pitchDelta, irr::f32 yawDelta) {
    static const irr::core::vector3df origin;
    static irr::core::quaternion rotation;

    static const irr::f32 low = Utils::pi<irr::f32> / 16,
                          high = Utils::pi<irr::f32> / 3;

    rotation.Y += yawDelta;
    rotation.Z =  std::clamp(rotation.Z + pitchDelta, low, high);

    irr::core::vector3df position;
    position.X = cameraDistance * std::sin(rotation.Y);
    position.Y = cameraDistance * std::sin(rotation.Z);
    position.Z = cameraDistance * std::cos(rotation.Y);
    position += origin;

    camera->setPosition(position);
    camera->setTarget(origin);
}

int Program::run() {
    std::srand(std::time(nullptr));

    using namespace irr;
    using namespace video;
    using namespace scene;
    using namespace gui;
    using namespace core;

    using namespace Game;

    E_DRIVER_TYPE driverType = PLAYGROUND_DRIVER;

    EventReceiver eventReceiver;

    IrrlichtDevice* device = createDevice(driverType,
            dimension2du(800, 600), 32, false, false, false, &eventReceiver);

    if (!device)
        return 1;

    device->setWindowCaption(L"Playground");

    ISceneManager* sceneManager = device->getSceneManager();
    IVideoDriver* driver = device->getVideoDriver();
    IGUIEnvironment* gui = device->getGUIEnvironment();

    gui->addStaticText(L"q to quit, c to add more cubes\nwasdrf to control camera",
                       {0, 0, 200, 40});

    this->world = std::make_unique<World>(*sceneManager);

    this->defaultCube = new btBoxShape(btVector3(1, 1, 1));

    world->add(new Entity(new btBoxShape({10, 0.05, 10}), 0, {0, 0, 0}, {0, 0, 0}));

    this->camera = sceneManager->addCameraSceneNode(nullptr, {}, {});
    rotateCameraBy(0.8, 0.8);

    const float timestep = 1.0f / 60;

    while (running && device->run()) {
        acceptInput(eventReceiver);
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
