#pragma once

#include <cstdint>

#include "result.hpp"

namespace swr {
    class Allocation {
    public:
        Allocation() = default;

        ~Allocation() {
            if (memory_ != nullptr) {
                delete[] memory_;
                memory_ = nullptr;
                size_ = 0;
            }
        }

        Allocation(const Allocation& Allocation) = delete;
        Allocation(Allocation&& Allocation) noexcept = default;

        Allocation& operator=(const Allocation& Allocation) = delete;
        Allocation& operator=(Allocation&& Allocation) noexcept = default;

        [[nodiscard]] inline Result allocate(std::size_t size) noexcept {
            if (size == 0) {
                return Result::ERROR_INVALID_ARGUMENT;
            }

            if (memory_) {
                return Result::ERROR_MEMORY_ALLOCATED;
            }

            size_ = size;
            memory_ = new std::uint8_t[size_];

            if (memory_ == nullptr) {
                return Result::ERROR_ALLOCATION_FAILED;
            }

            return Result::SUCCESS;
        }

        [[nodiscard]] inline Result free() noexcept {
            if (memory_ == nullptr) {
                return Result::ERROR_MEMORY_FREED;
            }

            delete[] memory_;
            size_ = 0;
            memory_ = nullptr;

            return Result::SUCCESS;
        }

        [[nodiscard]] inline ReturnInfo<std::uint8_t*> map(std::size_t offset = 0) noexcept {
            if (memory_ == nullptr) {
                return {nullptr, Result::ERROR_MEMORY_FREED};
            }

            return {memory_ + offset, Result::SUCCESS};
        }

        [[nodiscard]] inline std::size_t size() const noexcept {
            return size_;
        }

        [[nodiscard]] inline bool empty() const noexcept {
            return size_ == 0;
        }

    private:
        std::uint8_t* memory_ = nullptr;
        std::size_t size_ = 0;
    };
}