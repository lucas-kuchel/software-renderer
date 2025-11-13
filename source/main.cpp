#include <cstdint>
#include <cstring>
#include <print>

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

int main() {
    Allocation allocation;
    Result result = Result::SUCCESS;

    result = allocation.allocate(sizeof(float) * 4);

    if (result == Result::ERROR_MEMORY_ALLOCATED) {
        std::println("Error: allocation failed: memory already allocated");

        return 1;
    }
    else if (result == Result::ERROR_ALLOCATION_FAILED) {
        std::println("Error: allocation failed: failed to allocate memory");

        return 1;
    }
    else if (result == Result::ERROR_INVALID_ARGUMENT) {
        std::println("Error: allocation failed: invalid size provided");

        return 1;
    }

    ReturnInfo returnInfo = allocation.map();

    if (returnInfo.result == Result::ERROR_MEMORY_FREED) {
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

    if (result == Result::ERROR_MEMORY_FREED) {
        std::println("Error: allocation free failed: memory was already freed");

        return 1;
    }

    return 0;
}