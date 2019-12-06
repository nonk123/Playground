#ifndef IRR_PTR_HPP
#define IRR_PTR_HPP

#include <memory>

namespace Playground::Utils {
    template<typename T>
    struct IrrDelete {
        void operator()(T* t) {
            t->drop();
        }
    };

    template <typename T>
    using IrrPtr = std::unique_ptr<T, IrrDelete<T>>;
} // namespace Playground::Utils

#endif
