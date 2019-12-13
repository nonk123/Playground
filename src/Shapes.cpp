#include "Shapes.hpp"

#include "IrrlichtUtils.hpp"

using namespace Playground;

ShapePair::ShapePair(btCollisionShape* shape, irr::scene::IMesh* mesh, ShapeInfo info)
    : shape(shape), mesh(mesh, Utils::IrrDeleter<irr::scene::IMesh>), info(info) {
}

btRigidBody* ShapePair::makeBody(btMotionState* motionState) const {
    btVector3 inertia;
    shape->calculateLocalInertia(info.mass, inertia);
    return new btRigidBody(info.mass, motionState, shape.get(), inertia);
}

ShapePair ShapeCreator::box(const ShapeInfo& info, btVector3 size) const {
    return ShapePair(new btBoxShape(size / 2),
                     gCreator->createCubeMesh(Utils::toIrrlicht(size)),
                     info);
}

irr::core::array<irr::video::S3DVertex> toVertexArray(irr::scene::IMeshBuffer* buffer) {
    irr::core::array<irr::video::S3DVertex> array;
    array.reallocate(buffer->getVertexCount());

    auto type = buffer->getVertexType();

    if (type == irr::video::EVT_STANDARD) {
        irr::video::S3DVertex* vertices
            = static_cast<irr::video::S3DVertex*>(buffer->getVertices());

        for (int i = 0; i < array.allocated_size(); i++)
            array.push_back(vertices[i]);
    }

    return array;
}

irr::core::array<irr::u16> toIndexArray(irr::scene::IMeshBuffer* buffer) {
    irr::core::array<irr::u16> array;
    array.reallocate(buffer->getIndexCount());

    for (int i = 0; i < buffer->getIndexCount(); i++)
        array.push_back(buffer->getIndices()[i]);

    return array;
}

irr::scene::SMeshBuffer* toSMeshBuffer(irr::scene::IMeshBuffer* other) {
    irr::scene::SMeshBuffer* buffer = new irr::scene::SMeshBuffer();
    buffer->Vertices = toVertexArray(other);
    buffer->Indices = toIndexArray(other);
    buffer->Material = other->getMaterial();
    return buffer;
}

void translate(irr::scene::SMeshBuffer* buffer, irr::core::vector3df by) {
    for (int i = 0; i < buffer->Vertices.size(); i++)
        buffer->Vertices[i].Pos += by;

    buffer->recalculateBoundingBox();
}

ShapePair ShapeCreator::capsule(const ShapeInfo& info, btScalar r, btScalar a) const {
    static const irr::u32 tesselation = 16;

    irr::scene::SMesh* mesh = new irr::scene::SMesh();

    irr::scene::IMesh* top = gCreator->createSphereMesh(r);
    irr::scene::IMesh* mid = gCreator->createCylinderMesh(r, a, tesselation);
    irr::scene::IMesh* bot = gCreator->createSphereMesh(r);

    irr::scene::SMeshBuffer* topBuffer = toSMeshBuffer(top->getMeshBuffer(0));
    irr::scene::SMeshBuffer* midBuffer = toSMeshBuffer(mid->getMeshBuffer(0));
    irr::scene::SMeshBuffer* botBuffer = toSMeshBuffer(bot->getMeshBuffer(0));

    top->drop();
    top = nullptr;

    mid->drop();
    mid = nullptr;

    bot->drop();
    bot = nullptr;

    translate(topBuffer, {0, a - r, 0});
    translate(midBuffer, {0, -r, 0});
    translate(botBuffer, {0, -r, 0});

    mesh->addMeshBuffer(topBuffer);
    mesh->addMeshBuffer(midBuffer);
    mesh->addMeshBuffer(botBuffer);

    mesh->setDirty();
    mesh->recalculateBoundingBox();

    return ShapePair(new btCapsuleShape(r, a), mesh, info);
}

ShapePair ShapeCreator::sphere(const ShapeInfo& info, btScalar r) const {
    return ShapePair(new btSphereShape(r), gCreator->createSphereMesh(r), info);
}
