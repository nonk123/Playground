#include "Program.hpp"

#include <ctime>
#include <algorithm>

#include "btBulletDynamicsCommon.h"
#include "irrlicht.h"

#include "Math.hpp"

#include "config.hpp"

using namespace Playground;

btScalar impulse() {
    static const int limit = 16;

    btScalar val = static_cast<btScalar>(std::rand() % limit) / 10;
    return std::rand() % 2 ? val : -val;
}

void Program::acceptInput(EventReceiver& receiver, ShapeCreator& shapes) {
    if (receiver.down[irr::KEY_KEY_Q])
        running = false;

    static ShapePair box = shapes.box(ShapeInfo(), {1, 1, 1});
    static ShapePair capsule = shapes.capsule(ShapeInfo(), 0.5, 1.5);
    static ShapePair sphere = shapes.sphere(ShapeInfo(), 0.5);

    ShapePair* shape = nullptr;

    if (receiver.down[irr::KEY_KEY_1])
        shape = &box;

    if (receiver.down[irr::KEY_KEY_2])
        shape = &capsule;

    if (receiver.down[irr::KEY_KEY_3])
        shape = &sphere;

    if (shape) {
        Game::Entity* entity = new Game::Entity(*shape, {0, 7.5, 0});
        entity->applyImpulse({impulse(), impulse(), impulse()});
        world->add(entity);
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
        cameraDistance = std::max(cameraDistance - increment, irr::f32(0.2));
        rotateCameraBy(0, 0);
    }

    if (receiver.down[irr::KEY_KEY_F]) {
        cameraDistance = std::min(cameraDistance + increment, irr::f32(50));
        rotateCameraBy(0, 0);
    }
}

void Program::rotateCameraBy(irr::f32 pitchDelta, irr::f32 yawDelta) {
    static const irr::core::vector3df origin;
    static irr::core::quaternion rotation;

    static const irr::f32 low = Utils::pi<irr::f32> / 16,
                          high = Utils::pi<irr::f32> / 2.1;

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

    gui->addStaticText(L"q to quit, 1-3 to add more shapes\nwasd rf to control camera",
                       {0, 0, 200, 20});

    this->world = std::make_unique<World>(*sceneManager);

    ShapeCreator shapes(sceneManager->getGeometryCreator());

    ShapePair groundShape = shapes.box(ShapeInfo(0), {10, 0.1, 10});
    world->add(new Entity(groundShape, {0, 0, 0}));

    this->camera = sceneManager->addCameraSceneNode(nullptr, {}, {});
    rotateCameraBy(0.8, 0.8);

    const float timestep = 1.0f / 60;

    while (running && device->run()) {
        acceptInput(eventReceiver, shapes);
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
