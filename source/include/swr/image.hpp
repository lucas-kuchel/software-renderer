#pragma once

#include "types.hpp"

namespace swr {
    class Allocation;

    enum class ImageFormat {
        R8G8B8A8_UNORM,
        G8B8R8A8_UNORM,
        R8G8B8_UNORM,
        G8B8R8_UNORM,
    };

    struct Image {
        Allocation* allocation = nullptr;
        ImageFormat format;
        Extent2D extent;

        std::size_t offset = 0;
        std::size_t size = 0;

        inline static std::uint32_t getTexelStride(const Image& image) noexcept {
            switch (image.format) {
                case ImageFormat::R8G8B8A8_UNORM:
                case ImageFormat::G8B8R8A8_UNORM:
                    return 4;

                case ImageFormat::R8G8B8_UNORM:
                case ImageFormat::G8B8R8_UNORM:
                    return 3;
            }
        }
    };
}