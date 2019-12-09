#include "World.hpp"

using namespace Playground;
using namespace Playground::Game;

World::World(irr::scene::ISceneManager& sceneManager)
    : dispatcher(&collisionConfiguration),
      world(&dispatcher, &broadphase, &solver, &collisionConfiguration),
      sceneManager(sceneManager) {
    world.setGravity(btVector3(0, btScalar(-9.8), 0));
}

void World::update(const float timestep) {
    world.stepSimulation(timestep, 5);

    for (auto& entity : entities)
        entity.second->update();
}

ID World::add(Entity* entity) {
    return add(entity, lastID++);
}

ID World::add(Entity* entity, ID id) {
    using namespace irr;
    using namespace core;
    using namespace scene;
    using namespace video;

    if (id > lastID)
        lastID = id;

    irr::core::vector3df size;

    btTransform t;
    t.setIdentity();

    btVector3 min, max;

    entity->body->getCollisionShape()->getAabb(t, min, max);

    size.X = max.getX() - min.getX();
    size.Y = max.getY() - min.getY();
    size.Z = max.getZ() - min.getZ();

    IMesh* mesh = sceneManager.getGeometryCreator()->createCubeMesh(size);

    ISceneNode* sceneNode = sceneManager.addMeshSceneNode(mesh);
    entity->sceneNode = sceneNode;

    ITexture* solid = sceneManager.getVideoDriver()->addRenderTargetTexture({1, 1});

    u32 r = std::rand() % 256, g = std::rand() % 256, b = std::rand() % 256;

    s32* data = static_cast<irr::s32*>(solid->lock());
    data[0] = SColor(255, r, g, b).color;
    solid->unlock();

    sceneNode->setMaterialType(EMT_SOLID);
    sceneNode->setMaterialTexture(0, solid);
    sceneNode->setMaterialFlag(EMF_LIGHTING, false);

    entity->update();
    entity->world = this;
    world.addRigidBody(entity->body.get());
    entities.insert(std::make_pair(id, std::unique_ptr<Entity>(entity)));

    return id;
}

void World::remove(Entity* entity) {
    for (auto& pair : entities)
        if (pair.second.get() == entity)
            entities.erase(pair.first);
}

void World::remove(ID id) {
    entities.erase(id);
}
