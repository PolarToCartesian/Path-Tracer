#include "ProgressBar.hpp"

void PrintProgressBar(const float doneTotalRatio) noexcept {
    std::printf("\r"); // Go to the beginning of the line

    constexpr std::uint32_t barLength = 50u;
    const std::uint32_t done = std::ceil(doneTotalRatio * barLength);
    
    for (std::uint32_t i = 0u; i < done - 1; i++) std::putc('=', stdout);

    std::putc('>', stdout);
    
    for (std::uint32_t i = 0; i < barLength - done; i++) std::putc('-', stdout);

    std::fflush(stdout);
}