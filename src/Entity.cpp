#include "Entity.hpp"

#include <memory>

#include "World.hpp"
#include "Math.hpp"

using namespace Playground::Game;

Entity::Entity(btCollisionShape* shape,
               btScalar mass = 0.5,
               btVector3 origin = {0, 0, 0},
               btVector3 impulse = {0, 0, 0}) {
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(origin);

    btVector3 localInertia;
    shape->calculateLocalInertia(mass, localInertia);

    this->motionState = std::make_unique<btDefaultMotionState>(transform);

    this->body = std::make_unique<btRigidBody>(mass, motionState.get(),
                                               shape, localInertia);
    body->setFriction(0.9);
    body->applyCentralImpulse(impulse);
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
