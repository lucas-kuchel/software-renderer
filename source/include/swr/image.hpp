#pragma once

#include "types.hpp"

namespace swr {
    class Allocation;

    enum class ImageFormat {
        R8G8B8A8_UNORM,
        G8B8R8A8_UNORM,
    };

    struct ImageDescriptor {
        Allocation* allocation;
        ImageFormat format;
        Extent2D extent;
        Extent2D offset;
    };
}