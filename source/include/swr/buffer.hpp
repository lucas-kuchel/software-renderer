#pragma once

#include <cstdlib>

namespace swr {
    class Allocation;

    struct Buffer {
        Allocation* allocation = nullptr;

        std::size_t offset = 0;
        std::size_t size = 0;
    };
}