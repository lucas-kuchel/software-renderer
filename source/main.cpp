#include <swr/allocation.hpp>
#include <swr/image.hpp>

#include <cstring>
#include <print>

int main() {
    swr::Allocation allocation;
    swr::ImageDescriptor image = {
        .allocation = &allocation,
        .format = swr::ImageFormat::R8G8B8A8_UNORM,
        .extent = {800, 600},
        .offset = {0, 0},
    };

    swr::Result result = swr::Result::SUCCESS;

    result = allocation.allocate(image.extent.width * image.extent.height * 4);

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

    std::memset(returnInfo.value, 255, allocation.size());

    result = allocation.free();

    if (result == swr::Result::ERROR_MEMORY_FREED) {
        std::println("Error: allocation free failed: memory was already freed");

        return 1;
    }

    return 0;
}