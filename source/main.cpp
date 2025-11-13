#include <swr/allocation.hpp>

#include <cstring>
#include <print>

int main() {
    swr::Allocation allocation;
    swr::Result result = swr::Result::SUCCESS;

    result = allocation.allocate(sizeof(float) * 4);

    if (result == swr::Result::ERROR_MEMORY_ALLOCATED) {
        std::println("Error: allocation failed: memory already allocated");

        return 1;
    }
    else if (result == swr::Result::ERROR_ALLOCATION_FAILED) {
        std::println("Error: allocation failed: failed to allocate memory");

        return 1;
    }
    else if (result == swr::Result::ERROR_INVALID_ARGUMENT) {
        std::println("Error: allocation failed: invalid size provided");

        return 1;
    }

    swr::ReturnInfo returnInfo = allocation.map();

    if (returnInfo.result == swr::Result::ERROR_MEMORY_FREED) {
        std::println("Error: allocation mapping failed: memory was freed");

        return 1;
    }

    float values[4] = {
        521.62,
        234.75,
        320.54,
        923.23,
    };

    std::memcpy(returnInfo.value, values, sizeof(float) * 4);

    for (std::size_t i = 0; i < allocation.size() / sizeof(float); i++) {
        std::size_t byte = i * sizeof(float);

        float value = *reinterpret_cast<float*>(returnInfo.value + byte);

        std::println("value at byte {}: {}", byte, value);
    }

    result = allocation.free();

    if (result == swr::Result::ERROR_MEMORY_FREED) {
        std::println("Error: allocation free failed: memory was already freed");

        return 1;
    }

    return 0;
}