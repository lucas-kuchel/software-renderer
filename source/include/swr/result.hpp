#pragma once

namespace swr {
    enum class Result {
        SUCCESS,
        ERROR_INVALID_ARGUMENT,
        ERROR_ALLOCATION_FAILED,
        ERROR_MEMORY_FREED,
        ERROR_MEMORY_ALLOCATED,
    };

    template <typename T>
    struct ReturnInfo {
        T value;
        Result result;
    };
}
