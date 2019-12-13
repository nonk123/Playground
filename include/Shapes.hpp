#ifndef SHAPES_HPP
#define SHAPES_HPP

#include "btBulletDynamicsCommon.h"
#include "irrlicht.h"

#include <memory>

namespace Playground {
    struct ShapeInfo {
        btScalar mass = btScalar(0.5);
        btScalar friction = btScalar(0.5);
        btScalar restitution = btScalar(0.5);

        ShapeInfo() {
        }

        ShapeInfo(btScalar mass) : mass(mass) {
        }
    };

    struct ShapePair {
        std::shared_ptr<btCollisionShape> shape;
        std::shared_ptr<irr::scene::IMesh> mesh;

        ShapeInfo info;

        ShapePair(btCollisionShape*, irr::scene::IMesh*, ShapeInfo);

        btRigidBody* makeBody(btMotionState*) const;
    };

    class ShapeCreator {
      private:
        const irr::scene::IGeometryCreator* gCreator;

      public:
        ShapeCreator(const irr::scene::IGeometryCreator* gCreator) : gCreator(gCreator) {
        }

        ShapePair box(const ShapeInfo&, btVector3) const;
        ShapePair capsule(const ShapeInfo&, btScalar, btScalar) const;
        ShapePair sphere(const ShapeInfo&, btScalar) const;
    };
}

#endif
