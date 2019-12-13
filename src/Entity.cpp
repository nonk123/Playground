#include "Entity.hpp"

#include <memory>

#include "World.hpp"
#include "Math.hpp"

using namespace Playground::Game;

Entity::Entity(ShapePair shape, btVector3 origin = {0, 0, 0}) {
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(origin);

    this->motionState = std::make_unique<btDefaultMotionState>(transform);
    this->shape = shape.shape;

    this->body = std::unique_ptr<btRigidBody>(shape.makeBody(motionState.get()));
    body->setRestitution(shape.info.restitution);
    body->setFriction(shape.info.friction);

    this->mesh = shape.mesh;
}

void Entity::update() {
    if (!sceneNode)
        return;

    btVector3 pos = body->getWorldTransform().getOrigin();
    sceneNode->setPosition({pos.getX(), pos.getY(), pos.getZ()});

    btQuaternion o = body->getWorldTransform().getRotation();
    irr::core::quaternion q(o.getX(), o.getY(), o.getZ(), o.getW());

    irr::core::vector3df euler;
    q.toEuler(euler);

    euler *= Utils::radToDeg<irr::f32>;

    sceneNode->setRotation(euler);
}
