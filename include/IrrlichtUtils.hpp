#ifndef IRRLICHT_UTILS_HPP
#define IRRLICHT_UTILS_HPP

#include "btBulletDynamicsCommon.h"
#include "irrlicht.h"

#include <memory>

namespace Playground::Utils {
    template<class T>
    auto IrrDeleter = [](T* t) { t->drop(); };

    btVector3 toBullet(irr::core::vector3df irrlicht) {
        return {irrlicht.X, irrlicht.Y, irrlicht.Z};
    }

    irr::core::vector3df toIrrlicht(btVector3 bullet) {
        return {bullet.getX(), bullet.getY(), bullet.getZ()};
    }
}

#endif
